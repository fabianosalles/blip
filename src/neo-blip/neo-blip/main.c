#include <stdint.h>
#include <math.h>

#include "raylib.h"
#include "defs.h"
#include "maps.h"
#include "player.h"

Map *map;
Player player;
Camera2D camera = { 0 };
RenderTexture2D backbuffer;

void Update(float dt);
void Draw(float dt);

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NeoBlip");
	SetTargetFPS(60);
	backbuffer = LoadRenderTexture(BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);	

	map = CreateFirstMap();
	player.energy = map->energy;	
	player.position.x = (int)(map->spawnColumn * CELL_SIZE) + (CELL_SIZE / 2.0f);
	player.position.y = (int)map->spawnRow * CELL_SIZE+ (CELL_SIZE / 2.0f);
	player.radius = ((float)(CELL_SIZE) / 2.0f);
	player.speed = PLAYER_INICIAL_SPEED;

	camera.zoom = 1.0;
	camera.offset = (Vector2){ BACKBUFFER_WIDTH / 3, BACKBUFFER_HEIGHT / 3};

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		Update(dt);
		Draw(dt);		
	}
	CloseWindow();
	return 0;
}


void Update(float dt) {	
	PlayerUpdate(&player, map, dt);			
}


void DrawDebugText() {
	DrawText(TextFormat("FPS    : %d", GetFPS()), 25, 25, 18, WHITE);	
	DrawText(TextFormat("Player : %f.2, %f.2", player.position.x, player.position.y), 25, 40, 18, WHITE);	
	
	Vector2 gridPosition  = PlayerGetGridPosition(&player);	
	DrawText(TextFormat("Grid   : %f.01, %f.01", gridPosition.x, gridPosition.y), 25, 55, 18, WHITE);	
	DrawText(TextFormat("Grid   : %f, %f", trunc(gridPosition.x), trunc(gridPosition.y)), 25, 75, 18, WHITE);	

}

void Draw(float dt) {
camera.target = player.position;
	// draw on backbuffer
    BeginTextureMode(backbuffer);
		BeginMode2D(camera);
			ClearBackground((Color){192, 192, 192});
			MapDrawGrid(map, (Color){0xFF, 0xFF, 0xFF, 120});
			MapDraw(map);	
			PlayerDraw(&player);			
		EndMode2D();
    EndTextureMode();   
		          
    BeginDrawing();		
		ClearBackground(BLACK);
        // draws the buffer to screen, scaling it
		DrawTexturePro(
                backbuffer.texture,
                (Rectangle){0.0f, 0.0f, (float)BACKBUFFER_WIDTH, -(float)BACKBUFFER_HEIGHT},
                (Rectangle){0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT},
                (Vector2){0.0f, 0.0f}, 0.0f, WHITE);              		
		DrawDebugText();
    EndDrawing();	
}