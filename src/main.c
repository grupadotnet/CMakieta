#include "raylib.h"

int main(void) {
	InitWindow(640, 480, "Nazwa okna");
	
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(/*RAYWHITE == */ (Color) {245, 245, 245, 255});
		DrawText("Witaj, powiecie!", 0, 0, 52, BLACK); //TODO zrobić, żeby "świecie" działało... Z taką czcionką chyba się nie uda; DrawTextEx()?
		EndDrawing();
	}
	CloseWindow();
	return 0;
}