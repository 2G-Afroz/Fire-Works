// main.cpp
#include <raylib.h>
#include <vector>
#define WINDOW_WIDTH 850
#define WINDOW_HEIGHT 850

// Function and Class Definitions
class Particle;
void explode(std::vector<Particle> &exploders, Vector2 pos, Color color, Sound wistle, Sound brust);
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);

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
    // For sound
    Sound wistle;
    float initAccnY;
    Sound brust;
  public:
    Particle(Vector2 pos, Vector2 velocity, Vector2 accn, Color color, Sound wistle, Sound brust, bool exploder){
      this->pos = pos;
      this->velocity = velocity;
      this->accn = accn;
      this->color = color;
      this->exploder = exploder;
      size = 2;
      alpha = 1.0f;
      // For sound
      initAccnY = accn.y;
      this->wistle = wistle;
      this->brust = brust;
      if(!exploder){
        PlaySound(wistle);
      }
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

      // Decreasing volume of non-exploder
      if(!exploder){
        SetSoundVolume(wistle, map(accn.y, 0, initAccnY, 0, 0.8f));
      }
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
void explode(std::vector<Particle> &exploders, Vector2 pos, Color color, Sound wistle, Sound brust){
  for(int i = 0; i < 100; i++){
    exploders.push_back(
      Particle(
        pos,
        //{0, GetRandomValue(100, 120)/1000.0f},
        {0, 0.5},
        {GetRandomValue(-800, 800)/91.0f, (float)GetRandomValue(-400, 1200)/91.0f},
        color,
        wistle,
        brust,
        true
      )
    );
  }
}

// Function to map value
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
    // Ensure the input value is within the current range
    value = std::min(std::max(value, fromLow), fromHigh);

    // Map the value to the target range
    return toLow + (toHigh - toLow) * ((value - fromLow) / (fromHigh - fromLow));
}
	
int main() {
  // Initialize raylib
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FireWorks");
  InitAudioDevice();
  SetTargetFPS(60);
  ClearBackground(BLACK);

  // Initializing variables
  std::vector<Particle> crackers;
  std::vector<Particle> exploders;
  RenderTexture2D canvas = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
  Sound wistle_firework = LoadSound("assets/whistle_firework.wav");
  Sound brust_firework = LoadSound("assets/brust_firework.wav");

  // Main game loop
  while (!WindowShouldClose()) {
    // Adding crackers
    //if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    if(GetRandomValue(0, 100) < 2) {
      crackers.push_back(
        Particle(
          {(float)GetRandomValue(0, WINDOW_WIDTH), WINDOW_HEIGHT}, 
          {0, GetRandomValue(150, 300)/1000.0f},
          {0, (float)GetRandomValue(13, 18)},
          ColorFromHSV(GetRandomValue(0, 360), 1, 1),
          wistle_firework,
          brust_firework,
          false
        )
      );
    }

    // Drawing on Texture
    BeginTextureMode(canvas);
      DrawRectangle(0,0,WINDOW_WIDTH, WINDOW_HEIGHT, ColorAlpha(BLACK, 0.5));
      DrawText("Hello, 2G-Afroz!", 10, 10, 20, WHITE);

      // Crackers Loop
      for(int i = 0; i < crackers.size(); i++){
        crackers.at(i).update();
        crackers.at(i).show();
        if(crackers.at(i).getAccn().y <= 0){
          // remeove that cracker;
          PlaySound(brust_firework);
          explode(exploders, crackers.at(i).getPos(), crackers.at(i).getColor(), wistle_firework, brust_firework);
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
    EndTextureMode();
    // Draw
    BeginDrawing();
      DrawTexturePro(
        canvas.texture,
        (Rectangle){0, 0, (float)canvas.texture.width, (float)-canvas.texture.height},
        (Rectangle){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT},
        (Vector2){0, 0}, 0,
        WHITE
        );
    EndDrawing();
  }
	
  // Clean up
	CloseWindow();
	return 0;
}
