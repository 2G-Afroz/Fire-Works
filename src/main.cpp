// main.cpp
#include <raylib.h>
#include <vector>
#include <iostream>
#define WINDOW_WIDTH 850
#define WINDOW_HEIGHT 850

// Class for Particle
class Particle {
  private:
    Vector2 pos;
    Color color;
    Vector2 velocity;
    Vector2 accn;
    int size;
    float alpha;
    bool exploder;
  public:
    Particle(Vector2 pos, Vector2 velocity, Vector2 accn, Color color, bool exploder){
      this->pos = pos;
      this->velocity = velocity;
      this->accn = accn;
      this->color = color;
      this->exploder = exploder;
      size = 2;
      alpha = 1.0f;
    }

    void show(){
      DrawCircle(pos.x, pos.y, size, color);
    }

    void update(){

      if(exploder){
        // Updating acceleration
        accn.x /= 1.05f;
        accn.y /= 1.05f;

        // Updating alpha color
        alpha -= 0.025;
        color = ColorAlpha(color, alpha);
      }

      // Changing position
      pos.x -= accn.x;
      pos.y -= accn.y;

      // Changing Acceleration
      accn.x += velocity.x;
      accn.y -= velocity.y;
    }

    // Getters
    Vector2 getPos(){
      return pos;
    }
    Vector2 getAccn(){
      return accn;
    }

    float getAlpha(){
      return alpha;
    }

    Color getColor(){
      return color;
    }
};

// Function to create exploder
void explode(std::vector<Particle> &exploders, Vector2 pos, Color color){
  for(int i = 0; i < 100; i++){
    exploders.push_back(Particle(
                          pos,
                          //{0, GetRandomValue(100, 120)/1000.0f},
                          {0, 0.5},
                          {GetRandomValue(-800, 800)/100.0f, (float)GetRandomValue(-400, 1200)/100.0f},
                          color,
                          true
                        ));
  }
}
	
int main() {
  // Initialize raylib
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FireWorks");
  SetTargetFPS(60);
  ClearBackground(BLACK);

  // Initializing variables
  std::vector<Particle> crackers;
  std::vector<Particle> exploders;

  // Main game loop
  while (!WindowShouldClose()) {
    // Adding crackers
    if(GetRandomValue(0, 10) < 2)
      crackers.push_back(
        Particle(
          {(float)GetRandomValue(0, WINDOW_WIDTH), WINDOW_HEIGHT}, 
          {0, GetRandomValue(150, 300)/1000.0f},
          {0, (float)GetRandomValue(13, 18)},
          ColorFromHSV(GetRandomValue(0, 360), 1, 1),
          false
        ));

    // Draw
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Hello, 2G-Afroz!", 10, 10, 20, WHITE);

    // Crackers Loop
    for(int i = 0; i < crackers.size(); i++){
      crackers.at(i).update();
      crackers.at(i).show();
      if(crackers.at(i).getAccn().y <= 0){
        // remeove that cracker;
        explode(exploders, crackers.at(i).getPos(), crackers.at(i).getColor());
        crackers.erase(crackers.begin() + i);
      }
    }

    // Exploders Loop
    for(int i = 0; i < exploders.size(); i++){
      exploders.at(i).update();
      exploders.at(i).show();

      if(exploders.at(i).getAlpha() <= 0.0f){
        // Remove that exploder-particle
        exploders.erase(exploders.begin() + i);
      }
    }

    EndDrawing();
  }
	
  // Clean up
	CloseWindow();
	return 0;
}
