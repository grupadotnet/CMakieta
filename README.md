# CMakieta

Jest to pomoc do spotkania sekcji języka C z 19 grudnia 2022, na którym doprowadziliśmy do działania podstawową strukturę projektu w [CMake](https://cmake.org/), z podłączoną do tego projektu biblioteką [raylib](https://github.com/raysan5/raylib). Ale powinna się przydać na znacznie dłużej :)

Kopiując treść z repozytorium CMakiety i wprowadzając do niej drobne modyfikacje, możemy niewielkim wysiłkiem utworzyć podobną strukturę dla naszych własnych projektów, wykorzystujących do kontroli kompilacji środowisko CMake.

Ponadto repozytorium próbuje wprowadzić w prostej, praktycznej formie do wybranych technik eleganckiej kontroli repozytoriów w systemie kontroli wersji git.


## Budowanie

1. Sklonuj repozytorium do lokalnego katalogu komendą `git clone https://github.com/grupadotnet/CMakieta.git` i przejdź do niego: `cd CMakieta`

2. Komendą `git submodule update --init --depth 1` zaktualizuj submoduły - znajdujące się wewnątrz repozytorium inne repozytoria git (tutaj jest to biblioteka raylib), dopuszczając tych submodułów inicjalizację (pierwsze pobranie) i nie pobierając ich kompletnej historii.

3. Jeśli chcesz, parametry komendy `git submodule update --remote --merge` pozwalają zaktualizować submoduły do ich najnowszych zdalnych wersji, zamiast tych ustawionych przez to repozytorium. Rzecz jasna, jeżeli w międzyczasie w najnowszych wersjach submodułów zaszły niekompatybilne zmiany, to się zaczną problemy :)

4. Utwórz w głównym katalogu repozytorium katalog `build` i programem CMake wygeneruj w nim - bądź w dowolnym katalogu utworzonym hierarchicznie pod nim - pliki budowania, podając jako katalog z kodem źródłowym główny katalog repozytorium.
   
   W uniksowym shellu mogą to zrealizować następujące komendy:
   
   ```sh
   mkdir build
   cd build
   cmake ..
   ```
   
   (Katalog obecny staje się katalogiem budowania, a katalog źródłowy wskazać należy jawnie w wywołaniu komendy `cmake` - dwie kropki oznaczają katalog znajdujący się hierarchicznie o jeden stopień wyżej.)
   
   Przy użyciu CMake GUI wyglądać to może tak i wymagać jeszcze wciśnięcia Configure i ustawienia generatora, a następnie wciśnięcia Generate:
   
   <p align="center"><img src="https://user-images.githubusercontent.com/1766353/209276398-f2773842-c3b8-4f4c-ad22-4e9060bee7ac.png" alt="CMake GUI"/></p>
   
   Ponadto dzięki CMake GUI można szybko i intuicyjnie zmienić opcje, z jakimi projekt będzie budowany - wystarczy graficznie zmodyfikować listę opcji, a następnie ponownie wcisnąć Configure i Generate.
   
   **Uwaga:** Na platformie Windows domyślnie generowane są przez CMake pliki programu Visual Studio. Jeżeli chcesz na platformie Windows użyć bardziej uniwersalnego kompilatora GCC (polecam), należy podczas pierwszej konfiguracji projektu zmienić generator na Unix Makefiles, MinGW Makefiles, albo MSYS Makefiles, w zależności od wykorzystywanej dystrybucji GCC. W konsolowym interfejsie programu CMake realizuje to opcja `-G`, na przykład: `cmake -G "Unix Makefiles" ..`

5. O ile wszystko opisane powyżej się udało, pliki pozwalające na kompilację projektu powinny już być gotowe. Sposób uruchomienia kompilacji zależy od wybranego jawnie lub domyślnie w kroku 4 generatora: w zalecanym przypadku, gdy jest to generator uniksowy, wystarczy w katalogu budowania wywołać komendę `make`. Wywołanie tej komendy jest odtąd jedynym, co należy przeprowadzić, aby zbudować projekt ustawiony w krokach 1-4.
   
   **Uwaga:** MinGW na platformie Windows często zamiast `make` zapewnia ekwiwalentną komendę `mingw32-make`. Wówczas to jej można użyć do skompilowania projektu.
   
   Generalnie, budowa projektu po jego wygenerowaniu w poprzednim kroku powinna już być intuicyjna dla osoby obeznanej w obsłudze programu, dla którego nastąpiła generacja. Na przykład, generator Visual Studio utworzy plik rozwiązania projektu .sln, który można otworzyć w programie Visual Studio, aby pracować z projektem i kompilować go. To właśnie tego rodzaju uniwersalność, niewymagająca znaczących zmian w plikach projektu dla obsługi wielu narzędzi, uczyniła środowisko CMake tak popularnym :)


## Omówienie

Jeszcze będzie :)


## Licencja

W katalogu ext znajduje się raylib, więc rządzi się, i wszystko co do niego linkuje jest w jakiś sposób rządzone, jego licencją - [bez obaw, to licencja zlib, łagodna jest](https://github.com/raysan5/raylib/blob/master/LICENSE) :) A reszta w domenie publicznej!
