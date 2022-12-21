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
	Uint8 r = 255, g = 0, b = 0, a = 255;

	// Dessiner l'ellipse
	filledEllipseRGBA(renderer, ellipseRect.x + ellipseRect.w / 2, ellipseRect.y + ellipseRect.h / 2, ellipseRect.w / 2, ellipseRect.h / 2, r, g, b, a);

	return ellipseRect;
}