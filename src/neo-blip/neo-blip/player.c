#pragma once

#include "defs.h"
#include "player.h"
#include <raylib.h>

void PlayerDraw(Player *player) {
	DrawCircle(
		player->position.x + (CELL_SIZE /2), 
		player->position.y + (CELL_SIZE /2),
		(CELL_SIZE / 2),
		BLUE
	);
}
