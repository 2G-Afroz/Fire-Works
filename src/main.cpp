// main.cpp
#include <raylib.h>
#include <vector>
#define WINDOW_WIDTH 850
#define WINDOW_HEIGHT 850

// Class for Particle
class Particle {
  private:
    Vector2 pos;
    Color color;
    float velocity;
    float accn;
    int size = 2;
  public:
    Particle(Vector2 pos, float velocity, float accn){
      this->color = ColorFromHSV(GetRandomValue(0, 360), 1, 1);
      this->pos = pos;
      this->velocity = velocity;
      this->accn = accn;
    }

    void show(){
      DrawCircle(pos.x, pos.y, size, color);
    }

    void update(){
      pos.y -= accn;
      accn -= velocity;
    }

    // Getter 
    float getAccn(){
      return accn;
    }
};
	
int main() {
  // Initialize raylib
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FireWorks");
  SetTargetFPS(60);

  // Initializing variables
  std::vector<Particle> crackers;

  // Main game loop
  while (!WindowShouldClose()) {
      if(GetRandomValue(0, 10) < 2)
        crackers.push_back(
          Particle(
            {(float)GetRandomValue(0, WINDOW_WIDTH), WINDOW_HEIGHT}, 
            GetRandomValue(13, 18)/100.0f, GetRandomValue(13, 18)
            ));

      // Draw
      BeginDrawing();
      ClearBackground(BLACK);
      DrawText("Hello, 2G-Afroz!", 10, 10, 20, WHITE);
      for(int i = 0; i < crackers.size(); i++){

        crackers.at(i).update();
        crackers.at(i).show();

        if(crackers.at(i).getAccn() < 0){
          // remeove that cracker;
          crackers.erase(crackers.begin() + i);
        }
      }

      EndDrawing();
  }
	
  // Clean up
	CloseWindow();
	return 0;
}
