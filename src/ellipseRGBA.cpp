#include <random>
#include "constants.h"
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "ellipseRGBA.h"

Ball getEllipseRGBA()
{
	// Définition des dimensions de l'ellipse à partir du rayon
	Ball ellipse;
	ellipse.r = 10;

	// Définition des couleurs de l'ellipse (avec décalage du centre de rotation pour éviter les débordements)
	Ellipse_Color color = getRandomColor();
	ellipse.red = color.r;
	ellipse.green = color.g;
	ellipse.blue = color.b;
	ellipse.alpha = color.a;

	Ellipse_Coordinates coordinates = getRandomCoordinates(SCREEN_WIDTH, SCREEN_HEIGHT);
	ellipse.x = coordinates.x;
	ellipse.y = coordinates.y;

	// TODO: Utiliser `vx` et `vy` pour la direction de mouvement, générer ces valeurs aléatoirement
	// Ellipse_Direction
	ellipse.vx = 0;
	ellipse.vy = 0;

	return ellipse;
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
	int x = dis1(gen);
	int y = dis2(gen);

	return {x, y};
}

void drawEllipses(SDL_Renderer *renderer, Ball ellipse[])
{
	// Boucler dans le toute les ellipses
	for (size_t i = 0; i < BALLS_COUNT + 1; i++)
	{
		// Dessiner l'ellipse
		filledEllipseRGBA(renderer, ellipse[i].x, ellipse[i].y, ellipse[i].r, ellipse[i].r, ellipse[i].red, ellipse[i].green, ellipse[i].blue, ellipse[i].alpha);
	}
}