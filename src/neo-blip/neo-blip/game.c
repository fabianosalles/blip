#pragma once

#include <raylib.h>
#include "game.h"
#include "maps.h"
#include "player.h"


void GameUpdate(Game* game, float dt) {
	if (IsKeyPressed(KEY_F2)) {
		game->settings.debug = !game->settings.debug;
	}		

	if (IsKeyDown(KEY_KP_ADD)) {
		game->camera.zoom += 0.4f * dt;
	}

	if (IsKeyDown(KEY_KP_SUBTRACT)) {
		game->camera.zoom -= 0.4f * dt;
	}

	if (IsKeyDown(KEY_KP_0)) {
		game->camera.zoom = 1.0f;
	}

	PlayerUpdate(&game->player, game->map, dt);			
}

void GameRender(const Game* game) {
	
	MapDraw(game->map, &game->textures);	
	if (game->settings.debug) {
		MapDrawGrid(game->map, (Color){0xFF, 0xFF, 0xFF, 120});
	}

	PlayerDraw(&game->player);			
}
