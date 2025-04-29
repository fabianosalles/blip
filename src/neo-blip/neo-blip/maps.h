#pragma once

#include "defs.h"
#include <stdint.h>
#include <raylib.h>

typedef struct Layer; 

typedef struct Map {
	uint8_t number;	
	uint8_t energy;	
	uint16_t rows;	
	uint16_t columns;
	uint16_t spawnColumn;
	uint16_t spawnRow;
	uint8_t layerCount;
	struct Layer *layers;
} Map;

typedef struct Layer  {	
	Map *map;		// this map this layer belongs
	char **data;    
	struct Layer* next;
} Layer;

typedef enum {
	Wall = 'W',
	Heart = 'H',
	Energy = 'E',
	Water = 'A',
	Exit = 'X'
} MapContent;

/// <summary>
/// Creates a new, empty layer and adds it to map
/// </summary>
Layer *MapAddNewLayer(Map *map);

Map *MapCreate();
Map *CreateFirstMap();

void MapDrawGrid(const Map *map, Color color);
void MapDraw(const Map *map);
char MapGetContent(const Map *map, int layer, int row, int column);
GridCoord MapGetGridCoodAtPostion(Vector2 position);

