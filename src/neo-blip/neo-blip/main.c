#include <stdint.h>
#include <math.h>
#include <raylib.h>

#include "defs.h"
#include "game.h"

RenderTexture2D backbuffer;

Game game = {
	.camera = { 0 },	
	.settings.debug = false	
};


void Update(float dt);
void Draw(float dt);

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NeoBlip");
	SetTargetFPS(60);

	backbuffer = LoadRenderTexture(BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);	
	
	const char *workingDirectory = GetWorkingDirectory();	
	game.textures.wall = LoadTexture("assets\\wall.png");
	game.textures.ground = LoadTexture("assets\\ground.png");

	game.map = CreateFirstMap();
	game.player.energy = game.map->energy;	
	game.player.position.x = (int)(game.map->spawnColumn * CELL_SIZE) + (CELL_SIZE / 2.0f);
	game.player.position.y = (int)game.map->spawnRow * CELL_SIZE+ (CELL_SIZE / 2.0f);
	game.player.radius = ((float)(CELL_SIZE) / 2.0f);
	game.player.speed = PLAYER_INICIAL_SPEED;

	game.camera.zoom = 1.0;
	game.camera.offset = (Vector2){ BACKBUFFER_WIDTH / 3, BACKBUFFER_HEIGHT / 3};

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		Update(dt);
		Draw(dt);		
	}
	CloseWindow();

	UnloadTexture(game.textures.wall);
	UnloadTexture(game.textures.ground);
	return 0;
}


void Update(float dt) {	

	if (IsKeyPressed(KEY_F2)) {
		game.settings.debug = !game.settings.debug;
	}		

	PlayerUpdate(&game.player, game.map, dt);			
}


void DrawDebugText() {
	DrawText(TextFormat("FPS    : %d", GetFPS()), 25, 25, 18, WHITE);	
	DrawText(TextFormat("Player : %f.2, %f.2", game.player.position.x, game.player.position.y), 25, 40, 18, WHITE);	
	
	Vector2 gridPosition  = PlayerGetGridPosition(&game.player);	
	DrawText(TextFormat("Grid   : %f.01, %f.01", gridPosition.x, gridPosition.y), 25, 55, 18, WHITE);	
	DrawText(TextFormat("Grid   : %f, %f", trunc(gridPosition.x), trunc(gridPosition.y)), 25, 75, 18, WHITE);	

}

void Draw(float dt) {
	game.camera.target = game.player.position;
	// draw on backbuffer
    BeginTextureMode(backbuffer);
		BeginMode2D(game.camera);
			ClearBackground((Color){192, 192, 192});
			MapDraw(game.map, &game.textures);	
			if (game.settings.debug) {
				MapDrawGrid(game.map, (Color){0xFF, 0xFF, 0xFF, 120});
			}
			PlayerDraw(&game.player);			
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