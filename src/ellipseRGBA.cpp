#include <random>
#include "constants.h"
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "wall.h"
#include "ellipseRGBA.h"

std::random_device rd;

Ellipse getEllipseRGBA(Shape *shape)
{
	Ellipse ellipse;

	// Définition des dimensions de l'ellipse à partir du rayon
	ellipse.rad = BALL_RADIUS;

	// Défini si l'ellipse est visible ou non (oui par défaut)
	ellipse.visible = true;

	// Définition des couleurs de l'ellipse
	Ellipse_Color color = getRandomColor();
	ellipse.color.r = color.r;
	ellipse.color.g = color.g;
	ellipse.color.b = color.b;
	ellipse.color.a = color.a;

	// Définition des coordonnées de l'ellipse (avec décalage de l'origine pour éviter les débordements)
	Ellipse_Coordinates coordinates = getRandomCoordinates(shape);

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

// TODO: On voudrais que la balle ne puisse pas apparaitre dans un mur, pour l'instant c'est pas le cas
Ellipse_Coordinates getRandomCoordinates(Shape *shape)
{
	// Création d'un générateur de nombres aléatoires
	std::mt19937 gen(rd());

	// Création d'une distribution uniforme entre les limites
	// Les coordonnées dépendent du rayon des ellipses afin de toujours les faires apparaitre entièrement dans la fenêtre, tant que le diamètre des ellipses ne dépasse pas la taille de la fenêtre, nous sommes assurés qu'elles seront comprises dedans. On ajoute 1 pour la marge de la première frame.
	std::uniform_int_distribution<> dis1(0 + (BALL_RADIUS + 1), SCREEN_WIDTH - (BALL_RADIUS + 1));
	std::uniform_int_distribution<> dis2(0 + (BALL_RADIUS + 1), SCREEN_HEIGHT - (BALL_RADIUS + 1));

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

void moveEllipes(Ellipse ellipse[], Shape *shape)
{
	Shape windowWalls = getWindowWalls();
	// TODO: changer en tableau de taille variable OU liste chaîné
	for (size_t i = 0; i < BALLS_COUNT + 1; i++)
	{
		// Si pas visible, pas de calcules
		if (ellipse[i].visible)
		{
			// Génère un nombre aléatoire entre 1 et 4 pour pouvoir le multiplier au BALLS_SPEED
			int randomSpeed = (1 + (rand() % 4)) * BALLS_SPEED;
			// TODO: FIX THIS (bug, ball trop rapide, voir comment on peut différencier direction et vitesse)
			randomSpeed = 1;

			// Changement des postions de l'ellipse
			ellipse[i].coordinates.x += randomSpeed * ellipse[i].direction.vx;
			ellipse[i].coordinates.y += randomSpeed * ellipse[i].direction.vy;

			// Coordonnée du point mouvant
			int xb = ellipse[i].coordinates.x;
			int yb = ellipse[i].coordinates.y;

			if ((xb - BALL_RADIUS <= windowWalls.wallLeft.x1) || (xb + BALL_RADIUS >= windowWalls.wallRight.x1))
			{
				ellipse[i].direction.vx *= -1;
			}
			else if ((yb - BALL_RADIUS <= windowWalls.wallTop.y1) || (yb + BALL_RADIUS >= windowWalls.wallBottom.y1))
			{
				ellipse[i].direction.vy *= -1;
			}
		}
	}
}

void handleOnClick(Ellipse ellipse[], int mouseX, int mouseY)
{
	// TODO: changer en tableau de taille variable OU liste chaîné
	for (size_t i = 0; i < BALLS_COUNT + 1; i++)
	{
		int x_diff = mouseX - ellipse[i].coordinates.x;
		int y_diff = mouseY - ellipse[i].coordinates.y;
		int distance = sqrt(x_diff * x_diff + y_diff * y_diff);

		if (distance <= ellipse[i].rad)
		{
			ellipse[i].visible = false;
		}
	}
}