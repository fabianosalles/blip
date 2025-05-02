#pragma once

#include <math.h>
#include <raylib.h>
#include <stdint.h>
#include "defs.h"
#include "player.h"

static Vector2 _playerGridPosition = {0};


void PlayerDraw(Player *player) {	
	DrawCircleV(
		(Vector2){ player->position.x, player->position.y },
		player->radius,
		BLUE
	);
	
	//collision 
	/*DrawRectangleLines(
		player->boundingBox.x,
		player->boundingBox.y,
		player->boundingBox.width,
		player->boundingBox.height,
		GREEN		
	);	*/
}

void PlayerUpdateBBox(Player *player) {	
	player->boundingBox.x = player->position.x - player->radius;
	player->boundingBox.y = player->position.y - player->radius;
	player->boundingBox.width = player->radius * 2.0f;
	player->boundingBox.height = player->radius * 2.0f;
}

void PlayerUpdate(Player *player, Map *map, float dt) {

	char mapContent;
	int8_t xDirection = 0;
	int8_t yDirection = 0;

	if (IsKeyDown(KEY_UP))   yDirection -= 1;
	if (IsKeyDown(KEY_DOWN)) yDirection +=  1;
	if (IsKeyDown(KEY_LEFT)) xDirection -=  1;
	if (IsKeyDown(KEY_RIGHT)) xDirection +=  1;

	// move the player	
	player->position.x += (player->speed * dt * xDirection);
	player->position.y += (player->speed * dt * yDirection);	
	PlayerUpdateBBox(player);	

	// check for top wall collisions
	if (yDirection < 0) {
		GridCoord topCell = MapGetGridCoodAtPostion((Vector2){ 
			player->position.x, 
			player->position.y - player->radius, 
		});
			
		if (MapCoordIsInGridBounds(map, &topCell)) {
			mapContent = MapGetContent(map, 0, topCell.row, topCell.col);
			if (mapContent == Wall) {
				player->position.y = (topCell.row * CELL_SIZE) + CELL_SIZE + player->radius;
			}
		}
	}

	// check for left wall collisions
	if (xDirection < 0) {
		GridCoord leftCell = MapGetGridCoodAtPostion((Vector2){ 
			player->position.x - player->radius, 
			player->position.y  
		});

		if (MapCoordIsInGridBounds(map, &leftCell)) {
			mapContent = MapGetContent(map, 0, leftCell.row, leftCell.col);
			if (mapContent == Wall) {
				player->position.x = (leftCell.col * CELL_SIZE) + CELL_SIZE + player->radius;
			}
		}
	}

	// check for bottom wall collisions
	if (yDirection > 0) {
		GridCoord bottomCell = MapGetGridCoodAtPostion((Vector2){ 
			player->position.x, 
			player->position.y + player->radius, 
		});
				
		if (MapCoordIsInGridBounds(map, &bottomCell)) {
			mapContent = MapGetContent(map, 0, bottomCell.row, bottomCell.col);
			if (mapContent == Wall) {
				player->position.y = (bottomCell.row * CELL_SIZE) - player->radius;
			}
		}		
	}
	
	// check for right wall collisions
	if (xDirection > 0) {
		GridCoord rightCell = MapGetGridCoodAtPostion((Vector2){ 
			player->position.x + player->radius, 
			player->position.y, 
		});
				
		//is in-bounds?
		if (MapCoordIsInGridBounds(map, &rightCell)) {
			mapContent = MapGetContent(map, 0, rightCell.row, rightCell.col);
			if (mapContent == Wall) {
				player->position.x = (rightCell.col * CELL_SIZE) - player->radius;
			}
		}		
	}
	
	
}

/// <summary>
/// Gets the player top-lft point translated to grid coordinates
/// </summary>
/// <param name="player"></param>
Vector2 PlayerGetGridPosition(Player *player) {
	_playerGridPosition.x = ((player->position.x / CELL_SIZE));
	_playerGridPosition.y = ((player->position.y / CELL_SIZE));
	return _playerGridPosition;
}