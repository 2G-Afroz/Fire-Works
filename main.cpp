// main.cpp
#include <iostream>
#include "include/Firework2D.h"

#define WINDOW_WIDTH (float)GetMonitorWidth(0)
#define WINDOW_HEIGHT (float)GetMonitorHeight(0)

int main() {
  // Initialize raylib
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FireWorks");
  InitAudioDevice();
  SetTargetFPS(60);
  ClearBackground(BLACK);

  // Variables
  RenderTexture2D canvas = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

  // Resources
  Sound wistle = LoadSound("assets/whistle_firework.wav");
  Sound brust = LoadSound("assets/brust_firework.wav");

  // Particle2D Object
  std::vector<Firework2D> rockets;
  std::vector<Firework2D> exploders;

  // Main game loop
  while (!WindowShouldClose()) {
    ClearBackground(BLACK);
    //if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    if(GetRandomValue(0,100) < 10){
      rockets.push_back(
        Firework2D(
          {(float)GetRandomValue(0, WINDOW_WIDTH), WINDOW_HEIGHT},
          {0, 0.25},
          {0, (float)GetRandomValue(-14, -20)},
          ColorFromHSV(GetRandomValue(0, 360), 1, 1),
          2,
          false,
          wistle,
          brust
        )
      );
    }

    BeginTextureMode(canvas);
      DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, ColorAlpha(BLACK, 0.50));
      for(int i=0;i<exploders.size();i++){
        exploders.at(i).update();
        exploders.at(i).show();
      }
      for(int i=0;i<rockets.size();i++){
        rockets.at(i).update();
        rockets.at(i).show();
      }
    EndTextureMode();

    BeginDrawing();
      DrawTextureEx(
        canvas.texture,
        {WINDOW_WIDTH, WINDOW_HEIGHT},
        180,
        1.0f,
        WHITE
      );
    EndDrawing();

    // Erasing rockets and adding particles
    for(int i=0;i<rockets.size();i++){
      if(rockets.at(i).getAccn().y >= rockets.at(i).getVelocity().y){
        int prob = GetRandomValue(0, 30);
        if(prob < 10)
          rockets.at(i).explodeHeart(exploders);
        else {
          if(prob < 20)
            rockets.at(i).explode(exploders);
          else
            rockets.at(i).explodeRectangle(exploders);
        }
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
