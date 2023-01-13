#include "constants.h"
#include "wall.h"
#include <iostream>

Walls getAllWalls()
{
	Wall wallTop = {WALL_TOP_X1, WALL_TOP_Y1, WALL_TOP_X2, WALL_TOP_Y2};
	Wall wallLeft = {WALL_LEFT_X1, WALL_LEFT_Y1, WALL_LEFT_X2, WALL_LEFT_Y2};
	Wall wallRight = {WALL_RIGHT_X1, WALL_RIGHT_Y1, WALL_RIGHT_X2, WALL_RIGHT_Y2};
	Wall wallBottom = {WALL_BOTTOM_X1, WALL_BOTTOM_Y1, WALL_BOTTOM_X2, WALL_BOTTOM_Y2};

	return {wallTop, wallLeft, wallRight, wallBottom};
};

void drawWalls(SDL_Renderer *renderer, Walls *walls)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // définir la couleur de la ligne en rouge

	SDL_Point borderPoints[8] = {
		{walls->wallTop.x1, walls->wallTop.y1},
		{walls->wallTop.x2, walls->wallTop.y2},
		{walls->wallRight.x1, walls->wallRight.y1},
		{walls->wallRight.x2, walls->wallRight.y2},
		{walls->wallBottom.x2, walls->wallBottom.y2},
		{walls->wallBottom.x1, walls->wallBottom.y1},
		{walls->wallLeft.x2, walls->wallLeft.y2},
		{walls->wallLeft.x1, walls->wallLeft.y1}};

	SDL_RenderDrawLines(renderer, borderPoints, 8);
}