#include "raylib.h"
#include <stdint.h>
#include "defs.h"


#include "maps.h"
#include "player.h"

Map *map;
Player player;
Camera2D camera = { 0 };

void ProcessInput();

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NeoBlip");
	SetTargetFPS(60);
	RenderTexture2D backbuffer = LoadRenderTexture(BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);	

	map = CreateFirstMap();
	player.energy = map->energy;	
	player.position.x = (int)map->spawnColumn * CELL_SIZE;
	player.position.y = (int)map->spawnRow * CELL_SIZE;
	player.speed = PLAYER_INICIAL_SPEED;

	camera.zoom = 1.0;
	camera.offset = (Vector2){ BACKBUFFER_WIDTH / 3, BACKBUFFER_HEIGHT / 3};

	while (!WindowShouldClose()) {

		ProcessInput();		
		camera.target = player.position;

		// draw on backbuffer
        BeginTextureMode(backbuffer);
			BeginMode2D(camera);
				ClearBackground((Color){192, 192, 192});
				MapDraw(map);	
				MapDrawGrid(map, (Color){0xFF, 0xFF, 0xFF, 120});
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
              
			DrawText("Hello...", 32, 30, 20, WHITE);
        EndDrawing();	
	}

	CloseWindow();
	return 0;
}



void ProcessInput() {
	float dt = GetFrameTime();
	
	if (IsKeyDown(KEY_UP)) {
		//float temp = player.position.y -= (player.speed * dt);
		player.position.y -= (player.speed * dt);
	}

	if (IsKeyDown(KEY_DOWN)) {
		player.position.y += (player.speed * dt);
	}

	if (IsKeyDown(KEY_LEFT)) {
		player.position.x -= (player.speed * dt);
	}

	if (IsKeyDown(KEY_RIGHT)) {
		player.position.x += (player.speed * dt);
	}

}