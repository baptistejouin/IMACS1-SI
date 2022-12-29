#include <random>
#include "constants.h"
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "wall.h"
#include "ellipseRGBA.h"

Ball getEllipseRGBA()
{
	Ball ellipse;

	// Définition des dimensions de l'ellipse à partir du rayon
	ellipse.r = BALL_RADIUS;

	// Définition des couleurs de l'ellipse
	Ellipse_Color color = getRandomColor();
	ellipse.red = color.r;
	ellipse.green = color.g;
	ellipse.blue = color.b;
	ellipse.alpha = color.a;

	// Définition des coordonnées de l'ellipse (avec décalage de l'origine pour éviter les débordements)
	Ellipse_Coordinates coordinates = getRandomCoordinates(SCREEN_WIDTH, SCREEN_HEIGHT);
	ellipse.x = coordinates.x;
	ellipse.y = coordinates.y;

	// TODO: Meilleur orgnanisation si dans "Ellipse_Direction"
	ellipse.vx = getRandomDirectionVector(BALLS_VX_MIN, BALLS_VX_MAX);
	ellipse.vy = getRandomDirectionVector(BALLS_VY_MIN, BALLS_VY_MAX);

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
	// Les coordonnées dépendent du rayon des ellipses afin de toujours les faires apparaitre entièrement dans la fenêtre, tant que le diamètre des ellipses ne dépasse pas la taille de la fenêtre, nous sommes assurés qu'elles seront comprises dedans.
	std::uniform_int_distribution<> dis1(0 + BALL_RADIUS, width - BALL_RADIUS);
	std::uniform_int_distribution<> dis2(0 + BALL_RADIUS, height - BALL_RADIUS);

	// // Génération de coordonnées aléatoire
	int x = dis1(gen), y = dis2(gen);

	return {x, y};
}

int getRandomDirectionVector(int min, int max)
{
	// Création d'un générateur de nombres aléatoires
	std::random_device rd;
	std::mt19937 gen(rd());

	// Création d'une distribution uniforme entre les limites
	std::uniform_int_distribution<> dis(min, max);

	int v = 0;

	do
	{
		v = dis(gen);
		// On exclu la valeur 0, sinon l'ellipse ne bougera pas (vecteur nul)
	} while (v == 0);

	return v;
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

void moveEllipes(Ball ellipse[], Walls walls)
{
	for (size_t i = 0; i < BALLS_COUNT + 1; i++)
	{
		// ActualX = ellipse[i].x + ellipse->r/2;
		// ActualY = ellipse[i].y + ellipse->r/2;

		// Changement des postions de l'ellipse
		ellipse[i].x += BALLS_SPEED * ellipse[i].vx;
		ellipse[i].y += BALLS_SPEED * ellipse[i].vy;

		// Détection des collisions, inverser les directions si collision avec un mur. On prend en compte le rayon des ellipses pour ne pas seulement limiter la collision aux coordonnées du centre.

		// Le mur gauche
		if (ellipse[i].x - BALL_RADIUS <= walls.wallLeft.x1)
		{
			ellipse[i].vx *= -1;
		}
		// Le mur droit
		if (ellipse[i].x + BALL_RADIUS >= walls.wallRight.x1)
		{
			ellipse[i].vx *= -1;
		}
		// Le mur du haut
		if (ellipse[i].y - BALL_RADIUS >= walls.wallTop.y1)
		{
			ellipse[i].vy *= -1;
		}
		// Le mur du bas
		if (ellipse[i].y + BALL_RADIUS <= walls.wallBottom.y1)
		{
			ellipse[i].vy *= -1;
		}
	}
}