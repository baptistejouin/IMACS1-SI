#include <random>
#include "constants.h"
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "wall.h"
#include "ellipseRGBA.h"

std::random_device rd;

Ellipse getEllipseRGBA(Walls *walls)
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
	Ellipse_Coordinates coordinates = getRandomCoordinates(walls);

	ellipse.coordinates.x = coordinates.x;
	ellipse.coordinates.y = coordinates.y;

	// Définition du vecteur directeur de l'ellipse
	Ellipse_Direction direction = getRandomDirectionVector(BALLS_VECT_MAX);
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

Ellipse_Coordinates getRandomCoordinates(Walls *walls)
{
	// Création d'un générateur de nombres aléatoires
	std::mt19937 gen(rd());

	// Création d'une distribution uniforme entre les limites
	// Les coordonnées dépendent du rayon des ellipses afin de toujours les faires apparaitre entièrement dans la fenêtre, tant que le diamètre des ellipses ne dépasse pas la taille de la fenêtre, nous sommes assurés qu'elles seront comprises dedans. On ajoute 1 pour la marge de la première frame.
	// TODO: Supporter les murs penché dans l'apparition (choix de coordonée) (ici ça n'est pas fait pour, donc il y peut y avoir des soucis)
	std::uniform_int_distribution<> dis1(walls->wallTop.x1 + (BALL_RADIUS + 1), walls->wallTop.x2 - (BALL_RADIUS + 1));
	std::uniform_int_distribution<> dis2(walls->wallLeft.y1 + (BALL_RADIUS + 1), walls->wallLeft.y2 - (BALL_RADIUS + 1));

	// // Génération de coordonnées aléatoire
	int x = dis1(gen), y = dis2(gen);

	return {x, y};
}

Ellipse_Direction getRandomDirectionVector(int maxVect)
{
	// Création d'un générateur de nombres aléatoires
	std::mt19937 gen(rd());

	// Création d'une distribution uniforme entre les limites
	std::uniform_int_distribution<> dis((maxVect * -1), maxVect);

	int vx, vy = 0;

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

int distPointWall(int x1, int y1, int x2, int y2, int xb, int yb)
{
	// projection vectoriel, juste pour la distance
	return ((y2 - y1) * xb - (x2 - x1) * yb + x2 * y1 - y2 * x1) / sqrt(pow((y2 - y1), 2) + pow((x2 - x1), 2));
}

void moveEllipes(Ellipse ellipse[], Walls *walls)
{
	// TODO: tableau de taille variable OU liste chaîné
	for (size_t i = 0; i < BALLS_COUNT + 1; i++)
	{
		// Génère un nombre aléatoire entre 1 et 4 pour pouvoir le multiplier au BALLS_SPEED
		int random = 1 + (rand() % 4);

		// Changement des postions de l'ellipse
		ellipse[i].coordinates.x += random * ellipse[i].direction.vx;
		ellipse[i].coordinates.y += random * ellipse[i].direction.vy;

		// Coordonnée du point mouvant
		int xb = ellipse[i].coordinates.x;
		int yb = ellipse[i].coordinates.y;

		// Détection des collisions, inverser les directions si collision avec un mur. On prend en compte le rayon des ellipses pour ne pas seulement limiter la collision aux coordonnées du centre.
		int distanceWallLeft = distPointWall(walls->wallLeft.x1, walls->wallLeft.y1, walls->wallLeft.x2, walls->wallLeft.y2, xb, yb) - BALL_RADIUS;
		int distanceWallRight = distPointWall(walls->wallRight.x1, walls->wallRight.y1, walls->wallRight.x2, walls->wallRight.y2, xb, yb) + BALL_RADIUS;
		int distanceWallTop = distPointWall(walls->wallTop.x1, walls->wallTop.y1, walls->wallTop.x2, walls->wallTop.y2, xb, yb) + BALL_RADIUS;
		int distanceWallBottom = distPointWall(walls->wallBottom.x1, walls->wallBottom.y1, walls->wallBottom.x2, walls->wallBottom.y2, xb, yb) - BALL_RADIUS;

		if (distanceWallLeft <= 0)
		{
			// TODO: prendre en compte l'angle du mur penché (j'ai pas le calcul encore)
			// ellipse[i].direction.vy *= (mLeft * -1);
			ellipse[i].direction.vx *= -1;
		}

		if (distanceWallRight >= 0)
		{
			ellipse[i].direction.vx *= -1;
		}
		if (distanceWallBottom <= 0 || distanceWallTop >= 0)
		{
			ellipse[i].direction.vy *= -1;
		}
	}
}