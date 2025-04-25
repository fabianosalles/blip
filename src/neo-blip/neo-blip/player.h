#pragma once

#include <stdint.h>
#include <raylib.h>

typedef struct Player {
	Vector2 position;
	float speed;
	uint8_t energy;	
} Player;


void PlayerDraw(Player *player);
