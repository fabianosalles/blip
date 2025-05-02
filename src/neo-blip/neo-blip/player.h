#pragma once

#include <stdint.h>
#include <raylib.h>

#include "maps.h"

typedef struct Player {
	Vector2 position;
	float radius;
	float speed;
	uint8_t energy;	
	Rectangle boundingBox;
} Player;


void PlayerDraw(Player *player);
void PlayerUpdate(Player *player, Map *map, float dt);
Vector2 PlayerGetGridPosition(Player *player);
