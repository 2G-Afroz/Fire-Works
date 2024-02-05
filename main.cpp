// main.cpp
#include <iostream>
#include "include/Firework2D.h"

#define WINDOW_WIDTH 1450
#define WINDOW_HEIGHT 850

int main() {
  // Initialize raylib
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FireWorks");
  InitAudioDevice();
  SetTargetFPS(60);
  ClearBackground(BLACK);

  // Resources
  Sound wistle = LoadSound("assets/whistle_firework.wav");
  Sound brust = LoadSound("assets/brust_firework.wav");

  // Particle2D Object
  std::vector<Firework2D> rockets;
  std::vector<Firework2D> exploders;

  // Main game loop
  while (!WindowShouldClose()) {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      rockets.push_back(
        Firework2D(
          {(float)GetMouseX(), (float)GetMouseY()},
          {0, 0.25},
          {0, -16},
          ColorFromHSV(GetRandomValue(0, 360), 1, 1),
          2,
          false,
          wistle,
          brust
        )
      );
    }
    
    ClearBackground(BLACK);

    BeginDrawing();

      for(int i=0;i<exploders.size();i++){
        exploders.at(i).update();
        exploders.at(i).show();
      }
      for(int i=0;i<rockets.size();i++){
        rockets.at(i).update();
        rockets.at(i).show();
      }

    EndDrawing();
    // Erasing rockets
    for(int i=0;i<rockets.size();i++){
      if(rockets.at(i).getAccn().y >= rockets.at(i).getVelocity().y){
        rockets.at(i).explodeHeart(exploders);
        rockets.erase(rockets.begin() + i);
      }
    }
    // Erasing expoded particles
    for(int i=0;i<exploders.size();i++){
      if (exploders.at(i).getColorAlpha() <= 0){
        exploders.erase(exploders.begin() + i);
      }
      
    }
  }
	
  // Clean up
	CloseWindow();
	return 0;
}
