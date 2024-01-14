// main.cpp
#include <raylib.h>
#define WINDOW_WIDTH 850
#define WINDOW_HEIGHT 850
	
int main() {
  // Initialize raylib
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FireWorks");
	
  // Main game loop
  while (!WindowShouldClose()) {
      // Draw
      BeginDrawing();
      ClearBackground(BLACK);
      DrawText("Hello, 2G-Afroz!", 10, 10, 20, WHITE);
      EndDrawing();
  }
	
  // Clean up
	CloseWindow();
	return 0;
}
