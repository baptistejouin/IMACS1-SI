#include "constants.h"
#include "wall.h"

Walls getAllWalls()
{
	Wall wallTop = {0, 0, SCREEN_WIDTH, 0};
	Wall wallLeft = {0, 0, 0, SCREEN_HEIGHT};
	Wall wallRight = {SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	Wall wallBottom = {0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};

	return {wallTop, wallLeft, wallRight, wallBottom};
};