#pragma once

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


/// <summary>
/// Creates a new, empty layer and adds it to map
/// </summary>
Layer *MapAddNewLayer(Map *map);

Map *MapCreate();

void MapDrawGrid(Map *map, Color color);

void MapDraw(Map *map);

Map *CreateFirstMap();

