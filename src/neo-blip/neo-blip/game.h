#pragma once 

#include <raylib.h>
#include <stdbool.h>

#include "textures.h"
#include "maps.h"
#include "player.h"

typedef struct GameSettings {
	bool debug;
} GameSettings;


typedef struct Game {
	Camera2D camera;
	Player player;
	GameSettings settings;
	Map *map;
	GameTextures textures;
} Game;

