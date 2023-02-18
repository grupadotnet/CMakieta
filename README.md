# CMakieta

Jest to pomoc do spotkania sekcji języka C Koła Naukowego Programistów i Miłośników Informatyki na Politechnice Krakowskiej z dnia 19 grudnia 2022, na którym doprowadziliśmy do działania podstawową strukturę projektu w [CMake](https://cmake.org/), z podłączoną do tego projektu biblioteką [raylib](https://github.com/raysan5/raylib). Ale może się przydać na znacznie dłużej :)

Kopiując treść z repozytorium CMakiety i wprowadzając do niej drobne modyfikacje, możemy niewielkim wysiłkiem utworzyć podobną strukturę dla naszych własnych projektów, wykorzystujących do kontroli kompilacji środowisko CMake.

Ponadto repozytorium próbuje wprowadzić w prostej, praktycznej formie do wybranych technik eleganckiej kontroli repozytoriów w systemie kontroli wersji git.


## Budowanie

1. Sklonuj repozytorium na lokalny nośnik komendą `git clone https://github.com/grupadotnet/CMakieta.git` i przejdź do niego: `cd CMakieta`

2. Komendą `git submodule update --init --recursive --depth 1` zaktualizuj submoduły (znajdujące się wewnątrz repozytorium inne repozytoria git - tutaj jest to biblioteka raylib), dopuszczając tych submodułów inicjalizację (tylko wtedy będą pobrane), pobierając je rekursywnie (także submoduły submodułów itd.), i nie pobierając ich kompletnych historii, a tylko najnowsze wersje.

3. Jeśli chcesz, parametry komendy `git submodule update --recursive --remote --merge` pozwolą zaktualizować submoduły do ich najnowszych zdalnych wersji, zamiast tych ustawionych przez repozytorium. Rzecz jasna, jeżeli w międzyczasie w najnowszych wersjach submodułów zaszły niekompatybilne zmiany, to się mogą zacząć problemy :) A jeżeli chcesz tak zaktualizować tylko jeden submoduł, to podajesz na końcu lokalną ścieżkę do niego, np.: `git submodule update --recursive --remote --merge ext/raylib`

4. Utwórz w głównym katalogu repozytorium katalog `build`, i programem CMake wygeneruj w nim - bądź w dowolnym katalogu budowania utworzonym hierarchicznie pod nim - pliki budowania, podając jako katalog z kodem źródłowym główny katalog repozytorium.
	
	W uniksowym shellu mogą to zrealizować następujące komendy:
	
	```sh
	mkdir build
	cd build
	cmake ..
	```
	
	(Katalog `build` będzie w tym przykładzie katalogiem budowania, a katalog źródłowy wskazany jest jawnie w wywołaniu komendy `cmake` - dwie kropki oznaczają katalog znajdujący się hierarchicznie o jeden stopień wyżej, co tutaj prowadzi do katalogu głównego.)
	
	Przy użyciu CMake GUI wyglądać to może tak i wymagać jeszcze wciśnięcia Configure i ustawienia generatora, a następnie wciśnięcia Generate:
	
	<p align="center"><img src="https://user-images.githubusercontent.com/1766353/209276398-f2773842-c3b8-4f4c-ad22-4e9060bee7ac.png" alt="CMake GUI"/></p>
	
	Ponadto dzięki CMake GUI można szybko i intuicyjnie zmienić opcje, z jakimi projekt będzie budowany - wystarczy zmodyfikować listę opcji, a następnie ponownie wykonać konfigurację i generację, tak jak powyżej.
	
	**Uwaga:** Na platformie Windows domyślnie generowane są przez CMake pliki programu Visual Studio. Jeżeli chcesz na platformie Windows użyć bardziej uniwersalnego kompilatora GCC (co jest zalecane), należy podczas pierwszej konfiguracji projektu zmienić generator na Unix Makefiles, MinGW Makefiles, albo MSYS Makefiles, w zależności od wykorzystywanej dystrybucji GCC. W konsolowym interfejsie programu CMake realizuje to opcja `-G`, na przykład: `cmake -G "Unix Makefiles" ..`

5. O ile wszystko opisane powyżej się udało, pliki pozwalające na kompilację projektu powinny być gotowe. Sposób uruchomienia kompilacji zależy od wybranego jawnie lub domyślnie w kroku 4 generatora: w zalecanym przypadku, gdy jest to generator uniksowy, wystarczy w katalogu budowania wywołać komendę `make`. Wywołanie tej komendy jest odtąd jedynym, co należy zrobić, aby zbudować projekt ustawiony w krokach 1-4.
	
	**Uwaga:** MinGW na platformie Windows często zamiast `make` zapewnia ekwiwalentną komendę `mingw32-make`. Wówczas to jej można użyć do skompilowania projektu.
	
	Generalnie, budowa projektu po jego wygenerowaniu w kroku poprzedzającym powinna już być intuicyjna dla osoby obeznanej w obsłudze programu, pod który nastąpiła generacja. Na przykład, generator Visual Studio utworzy plik rozwiązania projektu .sln, który można otworzyć w programie Visual Studio, aby pracować z projektem i kompilować go. To właśnie tego rodzaju uniwersalność, niwelująca konieczność zmian w centralnym repozytorium projektu dla obsługi wielu narzędzi, uczyniła środowisko CMake tak popularnym :)

6. Rezultatem wykonania powyższych kroków powinno być pojawienie się gotowego programu w podkatalogu `bin` katalogu budowania...
	
	Który to program można uruchomić:
	
	<p align="center"><img src="https://user-images.githubusercontent.com/1766353/209360188-15b0607b-c7e9-45b4-a000-2b20fe26a89f.png" alt="Witaj, powiecie!"/></p>



## Omówienie

...ale bez obaw - od mało kogo oczekuje się tak drobiazgowej dokumentacji projektów :)

### [:file_folder: Katalog główny projektu CMakieta](/)

Jest to hierarchicznie najwyższy katalog, odpowiadający całemu repozytorium. Znajdują się w nim wszystkie pliki i katalogi opisane poniżej.

- #### [:page_facing_up: .gitignore](.gitignore)
	
	Plik ten zawiera sformatowany zbiór nazw plików i katalogów, które nie będą brane przez program git pod uwagę przy zarządzaniu repozytorium. Jeżeli są to katalogi, ich zawartość także nie będzie brana pod uwagę.
	
	**Zawartość**
	
	```ignore-list
	.DS_Store
	```
	Ignoruje pliki z parametrami wyświetlania katalogu tworzone przez system macOS. Taki zapis pomija wszystkie pliki i katalogi o wymienionej nazwie, także w podkatalogach repozytorium.
	
	```ignore-list
	/build
	```
	Ignoruje katalog o nazwie build tylko w katalogu głównym. Dzięki temu możemy w nim wykonywać kompilacje, bez zaśmiecania repozytorium.

- #### [:page_facing_up: .gitmodules](.gitmodules)
	
	Jest to plik zawierający informacje o submodułach repozytorium. Do jego obsługi i zmian stosować można komendy `git submodule`. [Nieco więcej o submodułach...](https://www.atlassian.com/git/tutorials/git-submodule)

- #### [:page_facing_up: CMakeLists.txt](CMakeLists.txt)
	
	W tym pliku znajduje się kod specjalizowanego języka skryptowego środowiska CMake dla ustawienia projektu. Plik o dokładnie takiej nazwie jest wykonywany (tzn. uruchamiany) przez CMake, gdy poda się mu zawierający go katalog źródłowy.
	
	**Zawartość**
	
	```cmake
	cmake_minimum_required(VERSION 3.13)
	```
	Ustawia minimalną wersję CMake potrzebną, aby zbudować projekt. Powinna to być pierwsza funkcja wywoływana w głównym skrypcie CMake. Wywołanie tej funkcji powoduje ustawienie zasad działania CMake na zgodne z wybraną wersją, dla zapewnienia kompatybilności wstecznej.
	
	```cmake
	project(NazwaProjektu)
	```
	Definiuje projekt o podanej nazwie. Nazwa ta jest później dostępna pod zmienną `${CMAKE_PROJECT_NAME}`.
	
	```cmake
	include(ExternalProject)
	```
	Ładuje moduł ExternalProject, który może być wykorzystywany, aby konfigurować łączenie z projektem bibliotek niewykorzystujących CMake. Chociaż żadna taka biblioteka nie jest wykorzystywana w tym projekcie, to nic nie szkodzi, aby ten moduł był ładowany - przypominał, że można go zastosować, gdy się jakaś przytrafi :)
	
	```cmake
	if(DEFINED CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE)
		set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE Release)
	endif()
	```
	Ustawia domyślne budowanie produkcyjnej wersji kodu (Release), wykorzystującej domyślnie parametry kompilatora `-O3 -DNDEBUG`, jeżeli przy konfiguracji użytkownik nie ustawi inaczej. Do innych opcji należą: Debug z parametrami `-g`, RelWithDebInfo z parametrami `-O2 -g -DNDEBUG` i MinSizeRel z parametrami `-Os -DNDEBUG`. Do sprawdzenia ustawienia zmiennej `${CMAKE_BUILD_TYPE}` stosuje się warunek `NOT`, a nie `NOT DEFINED` jak w następnych liniach, ponieważ jest ona domyślnie zdefiniowana, ale na ciąg pusty, sprowadzający się do fałszu. Aby zapamiętać to ustawienie w cache, tak, aby było widoczne np. w CMake GUI, wykorzystywana jest zamiast funkcji `set` odpowiednio sformułowana funkcja `set_property`.
	
	```cmake
	if(NOT DEFINED CMAKE_BUILD_WITH_INSTALL_RPATH)
		set(CMAKE_BUILD_WITH_INSTALL_RPATH true)
	endif()
	
	if(NOT DEFINED CMAKE_INSTALL_RPATH)
		set(CMAKE_INSTALL_RPATH $ORIGIN)
	endif()
	```
	Ustawia domyślną ścieżkę RPATH (runtime search path) na specjalny token `$ORIGIN` zamieniany automatycznie na ścieżkę do katalogu programu. W praktyce przydaje się to na systemach Linux, aby podobnie jak systemy Windows ładowały one biblioteki dynamiczne znajdujące się w tym samym katalogu, co program.
	
	```cmake
	if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	endif()
	
	if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	endif()
	```
	Ustawia domyślny eksport bibliotek dynamicznych oraz plików wykonywalnych do katalogu `bin` wewnątrz katalogu budowania. Dzięki temu pliki wyjściowe nie mieszają się w tym samym katalogu z różnorakimi plikami tymczasowymi.
	
	```cmake
	add_subdirectory(ext/raylib)
	```
	Uruchamia plik CMakeLists.txt, znajdujący się w katalogu `raylib` wewnątrz katalogu `ext`. Spowoduje to dodanie biblioteki raylib do kolejki budowania razem z projektem.
	
	```cmake
	add_subdirectory(src)
	```
	Uruchamia plik CMakeLists.txt, znajdujący się w katalogu `src`. Skonfiguruje on plik wyjściowy tego projektu, który ze względu na kolejność wywołania funkcji będzie następny do zbudowania po bibliotece raylib. Jest to nieco szerzej omówione niżej.

- #### [:page_facing_up: LICENSE](LICENSE)
	
	Plik o tej nazwie zawiera warunki licencyjne, które należy spełniać, aby wykorzystywać zawartość repozytorium. Brak zamieszczenia podobnego pliku przez właściciela praw, lub innej jednoznacznej informacji o udzielonej licencji, implikuje zastrzeżenie wszelkich praw, za wyjątkiem tych udzielonych osobno - np. w przypadku publicznych repozytoriów umieszczonych na platformie GitHub, [pewne przywileje są udzielane na mocy samych warunków tej platformy](https://docs.github.com/en/site-policy/github-terms/github-terms-of-service#3-ownership-of-content-right-to-post-and-license-grants).
	
	Związana z GitHub strona internetowa https://choosealicense.com/ prowadzi zbiór popularnych licencji otwartoźródłowych.

- #### [:page_facing_up: README.md](README.md)
	
	To ten plik, który właśnie czytasz :) Jego zawartość, sformatowana w składni Markdown, jest domyślnie wyświetlana na głównej stronie repozytorium przez platformy takie jak GitHub.

- #### [:file_folder: ext](ext)
	
	W tym katalogu umieściliśmy biblioteki zewnętrzne, wykorzystywane w projekcie. U nas jest to biblioteka raylib, umieszczona w repozytorium jako submoduł.

- #### [:file_folder: src](src)
	
	W tym katalogu przechowujemy nasze pliki z kodem źródłowym.
	
	- #### [:page_facing_up: src/CMakeLists.txt](src/CMakeLists.txt)
		
		Jest to kolejny skrypt CMake, dla czytelności oddzielony od skryptu znajdującego się w katalogu głównym, wykonującego go - gdy tamten skrypt przygotuje zależności i ustawienia dla projektu, ten szykuje w oparciu o nie budowę pliku wyjściowego (tutaj wykonywalnego, a mogłaby to być także biblioteka).
		
		**Zawartość**
		
		```cmake
		set(TARGET_NAME ${CMAKE_PROJECT_NAME})
		```
		Ustawia zmienną `${TARGET_NAME}`, która będzie oznaczała nazwę wyjściowego pliku, na nazwę projektu. Dzięki temu, jeżeli zechcemy nadać plikowi wyjściowemu nazwę inną od nazwy projektu (np. celem utworzenia kilku różnych plików wyjściowych), ustawić ją będzie trzeba tylko w jednym miejscu.
		
		```cmake
		file(GLOB_RECURSE src CONFIGURE_DEPENDS "*.c" "*.cpp" "*.h" "*.hpp")
		```
		Ładuje do zmiennej `${src}` ciąg nazw wszystkich plików źródłowych .c oraz .cpp, a także nagłówków .h i .hpp, w katalogu oraz jego podkatalogach. Flaga `CONFIGURE_DEPENDS` próbuje śledzić zmiany na liście plików przed każdą kompilacją - bez niej, CMake mógłby nie zauważyć nowych plików.
		
		```cmake
		add_executable(${TARGET_NAME} ${src})
		```
		Żąda utworzenia pliku wykonywalnego o nazwie ze zmiennej `${TARGET_NAME}`, używając plików źródłowych zawartych w zmiennej `${src}`. Nagłówki są wykrywane po rozszerzeniu i nie są przekazywane kompilatorowi, ale dzięki ich zamieszczeniu, mogą być wyświetlone jako elementy projektu przez obsługujące środowisko CMake edytory kodu.
		
		```cmake
		target_link_libraries(${TARGET_NAME} raylib)
		```
		Żąda linkowania biblioteki raylib do tworzonego pliku wykonywalnego. W rzeczywistości wywołanie to jest odpowiedzialne także za wiele innych działań składających się na dodanie biblioteki do użycia w tym pliku, jak chociażby dodanie ścieżki include dla nagłówków. Pomimo że linkowanie jest ostatnim krokiem szeroko pojętej kompilacji, a nagłówki są wymagane już na jej początku przez preprocesor, takie uproszczenie jest możliwe dlatego, że kod CMake jest tak naprawdę przetwarzany jeszcze przed kompilacją - na etapie konfiguracji projektu.
		
		```cmake
		if(APPLE)
			target_link_libraries(${TARGET_NAME} "-framework IOKit")
			target_link_libraries(${TARGET_NAME} "-framework Cocoa")
			target_link_libraries(${TARGET_NAME} "-framework OpenGL")
		endif()
		```
		[Zgodnie ze wskazaniem dokumentacji biblioteki raylib](https://github.com/raysan5/raylib/wiki/Working-with-CMake), w przypadku budowania dla systemów Apple (oznaczonego przez zdefiniowanie zmiennej `${APPLE}`), żąda także jawnie linkowania do frameworków IOKit, Cocoa oraz OpenGL. (Być może nie jest w stanie tego zapewnić żądanie linkowania samej biblioteki raylib - mechanizm działania frameworków systemów Apple różni się od mechanizmu stosowanego dla zwykłych bibliotek.)
	
	- #### [:page_facing_up: src/main.c](src/main.c)
		
		Jedyny w tym projekcie - ale jeden z nieskończoności możliwych - plik z kodem źródłowym właściwej aplikacji. Chociaż jest on gwoździem programu (ba dum tss), to jego działanie powinno być znacznie bardziej intuicyjne od funkcji pozostałych plików w tym repozytorium i łatwiejsze do zbadania. Dlatego zamiast ograniczać horyzonty tłumaczeniem tego pliku linijka po linijce, zapraszam do jego twórczej modyfikacji, wspomaganej chociażby takimi źródłami, jak [raylib cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html), dedykowany [zbiór przykładów](https://github.com/raysan5/raylib/tree/master/examples)... I rzecz jasna wyszukiwarka internetowa! :)


## Licencja

W katalogu ext znajduje się raylib, więc rządzi się, i wszystko co do niego linkuje jest w jakiś sposób rządzone, jego licencją - [bez obaw, to licencja zlib, łagodna jest](https://github.com/raysan5/raylib/blob/master/LICENSE) :) A reszta w domenie publicznej!
