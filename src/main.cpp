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
        alpha -= 0.015;
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
        SetSoundVolume(wistle, map(accn.y, 0, initAccnY, 0, 0.5f));
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
  for(int i = 0; i < 600; i++){
    exploders.push_back(
      Particle(
        pos,
        {0, GetRandomValue(180, 220)/1000.0f},
        {GetRandomValue(-800, 800)/91.0f, (float)GetRandomValue(-400, 1200)/91.0f},
        color,
        wistle,
        brust,
        true
      )
    );
  }
}

// Circle Explosion
void explodeCircle(std::vector<Particle> &exploders, Vector2 pos, Color color, Sound wistle, Sound brust){
  for(float a = 0; a < PI * 2; a+=0.01){
    exploders.push_back(
      Particle(
        pos,
        {0, 0.2},
        {cos(a) * GetRandomValue(1, 10), sin(a) * GetRandomValue(1, 10)},
        color,
        wistle,
        brust,
        true
      )
    );
  }
}

// Heart Explosion
int sgn(double d){
	return (d > 0) ? 1 : (d < 0 ? -1 : 1);
}
void explodeHeart(std::vector<Particle> &exploders, Vector2 pos, Color color, Sound wistle, Sound brust){
  // Bottom Heart
  for(float ang = 0; ang > -PI ; ang-=0.005){
    // This formula is used to create SuperShape
    float x = pow(abs(cos(ang)), 2) * GetRandomValue(400, 850)/100.0f  * sgn(cos(ang));
		float y = pow(abs(sin(ang)), 2) * GetRandomValue(400, 850)/100.0f * sgn(sin(ang));
    exploders.push_back(
      Particle(
        pos,
        {0, GetRandomValue(180, 220)/1000.0f},
        {x, y},
        color,
        wistle,
        brust,
        true
      )
    );
  }
  // Left Arc
  for(float ang = -PI/4; ang < 3 * PI / 4; ang+=0.01){
    // This formula is used to create SuperShape
    float x = pow(abs(cos(ang)), 1) * GetRandomValue(250, 560)/100.0f * sgn(cos(ang));
		float y = pow(abs(sin(ang)), 1) * GetRandomValue(250, 560)/100.0f * sgn(sin(ang));
    exploders.push_back(
      Particle(
        //{pos.x - 60, pos.y - 60},
        pos,
        {0, GetRandomValue(180, 220)/1000.0f},
        {x + 4, y + 4},
        color,
        wistle,
        brust,
        true
      )
    );
  }
  // Right Arc
  for(float ang = PI / 4; ang < 5 * PI / 4; ang+=0.01){
    // This formula is used to create SuperShape
    float x = pow(abs(cos(ang)), 1) * GetRandomValue(250, 560)/100.0f * sgn(cos(ang));
		float y = pow(abs(sin(ang)), 1) * GetRandomValue(250, 560)/100.0f * sgn(sin(ang));
    exploders.push_back(
      Particle(
        //{pos.x - 60, pos.y - 60},
        pos,
        {0, GetRandomValue(180, 220)/1000.0f},
        {x - 4, y + 4},
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
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      explodeHeart(exploders, {(float)GetMouseX(), (float)GetMouseY()}, WHITE, wistle_firework, brust_firework);
    }
    if(GetRandomValue(0, 100) < 3) {
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
      DrawRectangle(0,0,WINDOW_WIDTH, WINDOW_HEIGHT, ColorAlpha(BLACK, 0.45));
      DrawText("Hello, 2G-Afroz!", 10, 10, 20, WHITE);

      // Crackers Loop
      for(int i = 0; i < crackers.size(); i++){
        crackers.at(i).update();
        crackers.at(i).show();
        if(crackers.at(i).getAccn().y <= 0){
          // remeove that cracker;
          PlaySound(brust_firework);
          int random = GetRandomValue(0, 29);
          if(random < 10)
            explodeHeart(exploders, crackers.at(i).getPos(), crackers.at(i).getColor(), wistle_firework, brust_firework);
          else  if(random < 20)
                  explodeCircle(exploders, crackers.at(i).getPos(), crackers.at(i).getColor(), wistle_firework, brust_firework);
              else
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
