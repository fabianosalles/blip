#pragma once

#include <assert.h>
#include <stdbool.h>
#include "defs.h"
#include "maps.h"



__inline Map *MapCreate() {
	return (Map*)MemAlloc(sizeof(Map));	
}

Layer *MapAddNewLayer(Map *map){
	assert(map->rows > 0);
	assert(map->columns > 0);

	Layer *newLayer = MemAlloc(sizeof(Layer));		

	newLayer->map = map;
	newLayer->data = (char **)MemAlloc(sizeof(char) * map->rows * map->columns);
	
	// first layer on map
	if (map->layers == NULL) {
		map->layers = newLayer;		
		map->layerCount = 1;		
		return newLayer;
	}
	
	// get the last node
	Layer *node = map->layers;
	while (node->next != NULL)  {
		node = node->next;
	}
	
	node->next = newLayer;
	map->layerCount++;
	return newLayer;
}


Map *CreateFirstMap() {
	Map* map = MapCreate();
	map->number = 1;	
	map->energy = 50;
	map->spawnColumn = 2;
	map->spawnRow = 2;
	map->rows = 20;
	map->columns = 30;
	map->layerCount = 0;
	MapAddNewLayer(map);	

	map->layers[0].data[ 0] = "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
	map->layers[0].data[ 1] = "WFFFFFFFFWFFFFFFFWFFFFFFFFFWXW";
	map->layers[0].data[ 2] = "WFBFFFFWFWFFHHFFFWFWFFFFFFFWFW";
	map->layers[0].data[ 3] = "WFFFFFFWFWFFHHFFFWFWFFFHHFFWFW";
	map->layers[0].data[ 4] = "WFFFFFFWFWFFFFFFFWFWFFFHHFFWFW";
	map->layers[0].data[ 5] = "WWWWWWWWFWFFFFFFFWFWFFFFFFFWFW";
	map->layers[0].data[ 6] = "WFFFFFWFFWWWWWWFWWFWFFFFWWWWFW";
	map->layers[0].data[ 7] = "WFFFFFWFWFFFFWFFFFFWWWWWFFFFFW";
	map->layers[0].data[ 8] = "WFHHFFWFWFHHFWWWWWFFFFFFFWWWWW";
	map->layers[0].data[ 9] = "WFHHFFWFWFHHFWFFFWWWFWWWWWFHHW";
	map->layers[0].data[10] = "WFFFFFWFWFFFFWFFFHHWFWFFFFFHHW";
	map->layers[0].data[11] = "WFWWWWWFWWFFFWFFFHHWFWFFFFFFFW";
	map->layers[0].data[12] = "WFFFFFFFFWWFWWFFFWWWFFFFFFFFFW";
	map->layers[0].data[13] = "WWWWFWWWFFFFFWFFFWFFFWFFFFFFFW";
	map->layers[0].data[14] = "WFFFFFFWWWWWFWFWWWFWFWWWWWWWWW";
	map->layers[0].data[15] = "WFFFFFFWHHFWFFFFFFFWFWFFFFFFFW";
	map->layers[0].data[16] = "WFHHFFFWHHFWWWWWWWFWFWFFEFHHFW";
	map->layers[0].data[17] = "WFHHFEFWFFFFFFFFFWFWFWFFFFHHFW";
	map->layers[0].data[18] = "WFFFFFFWFFFFFFFFFFFWFFFFFFFFFW";
	map->layers[0].data[19] = "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";

	return map;
}

void MapDrawGrid(const Map *map, Color color) {		
	int mapW = CELL_SIZE * map->columns;
	int mapH = CELL_SIZE * map->rows;
	for (int row=1; row < map->rows; row++) {	
		DrawLineEx(
			(Vector2) { 0.f,  (float)(row * CELL_SIZE) }, 
			(Vector2) { mapW, (float)(row * CELL_SIZE) }, 
			1.0f, color);
		for (int col=1; col < map->columns; col++) {
			DrawLineEx(
				(Vector2){ (float)(col * CELL_SIZE), 0.0f }, 
				(Vector2){ (float)(col * CELL_SIZE), mapH }, 
				1.0f, color);	
		}
	}
}

void MapDraw(const Map *map, GameTextures *textures) {
	assert(map != NULL);
	assert(textures != NULL);

	Layer *layer = map->layers;

	for (int row=0; row < map->rows; row++) {
		char *rowdata = layer->data[row];
		for (int col=0; col < map->columns; col++) {
			//DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, (Color){132, 126, 136, 255 });
			if ((row < map->rows-1) && (col < map->columns-1)) {
				DrawTextureEx(textures->ground,
						(Vector2){ (col* (float)CELL_SIZE), (row * (float)CELL_SIZE)}, 0.0f, 1.0f, WHITE);
			}
			switch (rowdata[col])
			{			
			case Free:				
				//DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, (Color){132, 126, 136, 255 });
				break;
			case Wall: 
				//DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKGREEN);
				DrawTextureEx(textures->wall,
					(Vector2){ (col* (float)CELL_SIZE), (row * (float)CELL_SIZE)}, 0.0f, 1.0f, WHITE);
				break;
			case Heart:
				DrawCircle(
					(col * CELL_SIZE)+(CELL_SIZE /2), 
					(row * CELL_SIZE)+(CELL_SIZE /2), 
					(CELL_SIZE /2), RED);
				break;
			case Energy:
				DrawCircle(
					(col * CELL_SIZE)+(CELL_SIZE /2), 
					(row * CELL_SIZE)+(CELL_SIZE /2), 
					(CELL_SIZE /2), YELLOW);
				break;
			case Water:
				DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLUE);
				break;
			case Exit :
				DrawCircle(
					(col * CELL_SIZE)+(CELL_SIZE /2), 
					(row * CELL_SIZE)+(CELL_SIZE /2), 
					(CELL_SIZE /2), GREEN);
				break;
			default:
				break;
			}
		}
	}	
}


char MapGetContent(const Map *map, int layer, int row, int column) {
	assert(map != NULL);
	assert(layer < map->layerCount);
	assert(row < map->rows);
	assert(column < map->columns);
		
	return map->layers[layer].data[row][column];	
}


bool MapCoordIsInGridBounds(const Map *map, const GridCoord *coord) {
	return (
		(coord->row >= 0 && coord->row < map->rows) &&
		(coord->col >= 0 && coord->col < map->columns) 
	);
}

GridCoord MapGetGridCoodAtPostion(Vector2 position) {
	GridCoord coord;

	if (position.x < 0.0f)  {
		coord.col = -1;
	}
	else {
		coord.row = (position.y / (float)CELL_SIZE);
	}
		
	if (position.y < 0.0f) {
		coord.row = -1;
	}
	else {
		coord.col = (position.x / (float)CELL_SIZE);
	}
	return coord;
}