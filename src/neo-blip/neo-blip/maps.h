#pragma once

#include <stdint.h>
#include <raylib.h>
#include <stdbool.h>
#include "textures.h"

typedef struct Layer; 

typedef struct {
	uint8_t number;	
	uint8_t energy;	
	uint16_t rows;	
	uint16_t columns;
	uint16_t spawnColumn;
	uint16_t spawnRow;
	uint8_t layerCount;
	struct Layer *layers;
} Map;

typedef struct Layer {	
	Map *map;		// this map this layer belongs
	char **data;    
	struct Layer* next;
} Layer;

typedef enum {
	Wall = 'W',
	Heart = 'H',
	Energy = 'E',
	Water = 'A',
	Exit = 'X',
	Free = 'F'
} MapContent;

typedef struct {
	int row;
	int col;
} GridCoord;


/// <summary>
/// Creates a new, empty layer and adds it to map
/// </summary>
Layer *MapAddNewLayer(Map *map);

Map *MapCreate();
Map *CreateFirstMap();

void MapDrawGrid(const Map *map, Color color);
void MapDraw(const Map *map, GameTextures *textures);
bool MapCoordIsInGridBounds(const Map *map, const GridCoord *coord);
char MapGetContent(const Map *map, int layer, int row, int column);

GridCoord MapGetGridCoodAtPostion(Vector2 position);

