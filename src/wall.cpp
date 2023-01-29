#include <iostream>
#include "constants.h"
#include "wall.h"

Shape getCustomWalls()
{
	Wall wallTop = {WALL_TOP_X1, WALL_TOP_Y1, WALL_TOP_X2, WALL_TOP_Y2};
	Wall wallLeft = {WALL_LEFT_X1, WALL_LEFT_Y1, WALL_LEFT_X2, WALL_LEFT_Y2};
	Wall wallRight = {WALL_RIGHT_X1, WALL_RIGHT_Y1, WALL_RIGHT_X2, WALL_RIGHT_Y2};
	Wall wallBottom = {WALL_BOTTOM_X1, WALL_BOTTOM_Y1, WALL_BOTTOM_X2, WALL_BOTTOM_Y2};

	return {wallTop, wallLeft, wallRight, wallBottom};
};

Shape getWindowWalls()
{
	Wall wallTop = {0, 0, SCREEN_WIDTH, 0};
	Wall wallLeft = {0, 0, 0, SCREEN_HEIGHT};
	Wall wallRight = {SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	Wall wallBottom = {0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};

	return {wallTop, wallLeft, wallRight, wallBottom};
};

void drawShape(SDL_Renderer *renderer, Shape *shape)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // définir la couleur de la ligne en rouge

	SDL_Point borderPoints[8] = {
		{shape->wallTop.x1, shape->wallTop.y1},
		{shape->wallTop.x2, shape->wallTop.y2},
		{shape->wallRight.x1, shape->wallRight.y1},
		{shape->wallRight.x2, shape->wallRight.y2},
		{shape->wallBottom.x2, shape->wallBottom.y2},
		{shape->wallBottom.x1, shape->wallBottom.y1},
		{shape->wallLeft.x2, shape->wallLeft.y2},
		{shape->wallLeft.x1, shape->wallLeft.y1}};

	SDL_RenderDrawLines(renderer, borderPoints, 8);
}