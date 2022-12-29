#include <random>
#include "constants.h"
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "ellipseRGBA.h"

SDL_Rect drawEllipseRGBA(SDL_Renderer *renderer)
{
	// Définition des dimensions de l'ellipse
	SDL_Rect ellipseRect;
	ellipseRect.w = 50;
	ellipseRect.h = 50;

	// Définition des couleurs de l'ellipse (avec décalage du centre de rotation pour éviter les débordements)
	Ellipse_Color color = getRandomColor();
	Ellipse_Coordinates coordinates = getRandomCoordinates(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Dessiner l'ellipse
	filledEllipseRGBA(renderer, coordinates.x + ellipseRect.w / 2, coordinates.y + ellipseRect.h / 2, ellipseRect.w / 2, ellipseRect.h / 2, color.r, color.g, color.b, color.a);

	return ellipseRect;
}

Ellipse_Color getRandomColor()
{
	// Création d'un générateur de nombres aléatoires
	std::random_device rd;
	std::mt19937 gen(rd());

	// Création d'une distribution uniforme entre les limites
	std::uniform_int_distribution<> dis(0, 255);

	// Génération d'une couleur aléatoire
	Uint8 r = dis(gen), g = dis(gen), b = dis(gen), a = 255;

	return {r, g, b, a};
}

Ellipse_Coordinates getRandomCoordinates(int width, int height)
{
	// Création d'un générateur de nombres aléatoires
	std::random_device rd;
	std::mt19937 gen(rd());

	// Création d'une distribution uniforme entre les limites
	std::uniform_int_distribution<> dis1(0, width);
	std::uniform_int_distribution<> dis2(0, height);

	// // Génération de coordonnées aléatoire
	int y = dis1(gen);
	int x = dis2(gen);

	return {x, y};
}