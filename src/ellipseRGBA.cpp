#include <random>
#include "constants.h"
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "wall.h"
#include "ellipseRGBA.h"

std::random_device rd;

Ellipse getEllipseRGBA()
{
	Ellipse ellipse;

	// Définition des dimensions de l'ellipse à partir du rayon
	ellipse.rad = BALL_RADIUS;

	// Définition des couleurs de l'ellipse
	Ellipse_Color color = getRandomColor();
	ellipse.color.r = color.r;
	ellipse.color.g = color.g;
	ellipse.color.b = color.b;
	ellipse.color.a = color.a;

	// Définition des coordonnées de l'ellipse (avec décalage de l'origine pour éviter les débordements)
	Ellipse_Coordinates coordinates = getRandomCoordinates(SCREEN_WIDTH, SCREEN_HEIGHT);
	ellipse.coordinates.x = coordinates.x;
	ellipse.coordinates.y = coordinates.y;

	// Définition du vecteur directeur de l'ellipse
	Ellipse_Direction direction = getRandomDirectionVector(BALLS_V_MIN, BALLS_V_MAX);
	ellipse.direction.vx = direction.vx;
	ellipse.direction.vy = direction.vy;

	return ellipse;
}

Ellipse_Color getRandomColor()
{
	// Création d'un générateur de nombres aléatoires
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
	std::mt19937 gen(rd());

	// Création d'une distribution uniforme entre les limites
	// Les coordonnées dépendent du rayon des ellipses afin de toujours les faires apparaitre entièrement dans la fenêtre, tant que le diamètre des ellipses ne dépasse pas la taille de la fenêtre, nous sommes assurés qu'elles seront comprises dedans.
	std::uniform_int_distribution<> dis1(0 + BALL_RADIUS, width - BALL_RADIUS);
	std::uniform_int_distribution<> dis2(0 + BALL_RADIUS, height - BALL_RADIUS);

	// // Génération de coordonnées aléatoire
	int x = dis1(gen), y = dis2(gen);

	return {x, y};
}

Ellipse_Direction getRandomDirectionVector(int min, int max)
{
	// Création d'un générateur de nombres aléatoires
	std::mt19937 gen(rd());

	// Création d'une distribution uniforme entre les limites
	std::uniform_int_distribution<> dis(min, max);

	float vx, vy = 0;

	do
	{
		vx = dis(gen);
		vy = dis(gen);
		// On exclu la valeur 0, sinon l'ellipse ne bougera pas (vecteur nul)
	} while (vx == 0 || vy == 0);

	return {vx, vy};
}

void drawEllipses(SDL_Renderer *renderer, Ellipse ellipse[])
{
	// Boucler dans le toute les ellipses
	for (size_t i = 0; i < BALLS_COUNT + 1; i++)
	{
		// Dessiner l'ellipse
		filledEllipseRGBA(renderer, ellipse[i].coordinates.x, ellipse[i].coordinates.y, ellipse[i].rad, ellipse[i].rad, ellipse[i].color.r, ellipse[i].color.g, ellipse[i].color.b, ellipse[i].color.a);
	}
}

void moveEllipes(Ellipse ellipse[], Walls walls)
{	//Génère un nombre aléatoire entre 1 et 4 pour pouvoir le multiplier au BALLS_SPEED
	int random = 1 + (rand() % 4);
	for (size_t i = 0; i < BALLS_COUNT + 1; i++)
	{
		// Changement des postions de l'ellipse
		ellipse[i].coordinates.x += random*BALLS_SPEED * ellipse[i].direction.vx;
		ellipse[i].coordinates.y += random*BALLS_SPEED * ellipse[i].direction.vy;

		// Détection des collisions, inverser les directions si collision avec un mur. On prend en compte le rayon des ellipses pour ne pas seulement limiter la collision aux coordonnées du centre.

		// Le mur gauche ou le mur droit
		if ((ellipse[i].coordinates.x - BALL_RADIUS <= walls.wallLeft.x1) || (ellipse[i].coordinates.x + BALL_RADIUS >= walls.wallRight.x1))
		{
			ellipse[i].direction.vx *= -1;
		}
		// Le mur du haut ou du bas
		if ((ellipse[i].coordinates.y - BALL_RADIUS <= walls.wallTop.y1) || (ellipse[i].coordinates.y + BALL_RADIUS >= walls.wallBottom.y1))
		{
			ellipse[i].direction.vy *= -1;
		}
	}
}