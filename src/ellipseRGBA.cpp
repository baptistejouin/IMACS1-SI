#include <random>
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "ellipseRGBA.h"

SDL_Rect drawEllipseRGBA(SDL_Renderer *renderer)
{
	// Définition des dimensions de l'ellipse
	SDL_Rect ellipseRect;
	ellipseRect.x = 0;
	ellipseRect.y = 0;
	ellipseRect.w = 50;
	ellipseRect.h = 50;

	// Définition des couleurs de l'ellipse (avec décalage du centre de rotation pour éviter les débordements)
	Ellipse_Color color = getRandomColor();

	// Dessiner l'ellipse
	filledEllipseRGBA(renderer, ellipseRect.x + ellipseRect.w / 2, ellipseRect.y + ellipseRect.h / 2, ellipseRect.w / 2, ellipseRect.h / 2, color.r, color.g, color.b, color.a);

	return ellipseRect;
}

Ellipse_Color getRandomColor()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);

	Uint8 r = dis(gen);
	Uint8 g = dis(gen);
	Uint8 b = dis(gen);
	Uint8 a = 255;

	return {r, g, b, a};
}