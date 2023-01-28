#include <random>
#include <optional>
#include "constants.h"
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "wall.h"
#include "ellipse.h"

std::random_device rd;

Ellipse getEllipseRGBA(std::optional<Ellipse_Coordinates> coordinates, std::optional<Ellipse_Color> color)
{
	Ellipse ellipse;

	// Définition des dimensions de l'ellipse à partir du rayon
	ellipse.rad = BALL_RADIUS;

	// Définition des couleurs de l'ellipse
	// On vérifie si les paramètres optionnel contienent des valeurs, sinon nous en générons aléatoirement
	if (color.has_value())
	{
		ellipse.color.r = color->r;
		ellipse.color.g = color->g;
		ellipse.color.b = color->b;
	}
	else
	{
		Ellipse_Color color = getRandomColor();
		ellipse.color.r = color.r;
		ellipse.color.g = color.g;
		ellipse.color.b = color.b;
	}

	// Définition des coordonnées de l'ellipse (avec décalage de l'origine pour éviter les débordements)
	// On vérifie si les paramètres optionnel contienent des valeurs, sinon nous en générons aléatoirement
	if (coordinates.has_value())
	{
		ellipse.coordinates.x = coordinates->x;
		ellipse.coordinates.y = coordinates->y;
	}
	else
	{
		Ellipse_Coordinates coordinates = getRandomCoordinates();
		ellipse.coordinates.x = coordinates.x;
		ellipse.coordinates.y = coordinates.y;
	}

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
	Uint8 r = dis(gen), g = dis(gen), b = dis(gen);

	return {r, g, b};
}

// TODO: On voudrais que la balle ne puisse pas apparaitre dans un mur, pour l'instant c'est pas le cas
Ellipse_Coordinates getRandomCoordinates()
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

void drawEllipses(SDL_Renderer *renderer, std::vector<Ellipse> *ellipses)
{
	// Boucler dans le toute les ellipses
	for (size_t i = 0; i < ellipses->size(); i++)
	{
		Ellipse ellipse = (*ellipses)[i];
		// Dessiner l'ellipse
		filledEllipseRGBA(renderer, ellipse.coordinates.x, ellipse.coordinates.y, ellipse.rad, ellipse.rad, ellipse.color.r, ellipse.color.g, ellipse.color.b, 255);
	}
}

bool checkCollision(Ellipse &ball, Shape &shape)
{
	int ellipseX = ball.coordinates.x;
	int ellipseY = ball.coordinates.y;
	int ellipseR = ball.rad;
	int shapeX1 = shape.wallTop.x1;
	int shapeY1 = shape.wallTop.y1;
	int shapeX2 = shape.wallBottom.x2;
	int shapeY2 = shape.wallBottom.y2;

	// Check collision with top wall
	if (ellipseY - ellipseR <= shapeY1 && ellipseY + ellipseR >= shapeY1 && (ellipseX + ellipseR >= shapeX1 && ellipseX - ellipseR <= shapeX2))
	{
		ball.direction.vy = -ball.direction.vy;
		return true;
	}
	// Check collision with bottom wall
	else if (ellipseY + ellipseR >= shapeY2 && ellipseY - ellipseR <= shapeY2 && (ellipseX + ellipseR >= shapeX1 && ellipseX - ellipseR <= shapeX2))
	{
		ball.direction.vy = -ball.direction.vy;
		return true;
	}
	// Check collision with left wall
	else if (ellipseX - ellipseR <= shapeX1 && ellipseX + ellipseR >= shapeX1 && (ellipseY + ellipseR >= shapeY1 && ellipseY - ellipseR <= shapeY2))
	{
		ball.direction.vx = -ball.direction.vx;
		return true;
	}
	// Check collision with right wall
	else if (ellipseX + ellipseR >= shapeX2 && ellipseX - ellipseR <= shapeX2 && (ellipseY + ellipseR >= shapeY1 && ellipseY - ellipseR <= shapeY2))
	{
		ball.direction.vx = -ball.direction.vx;
		return true;
	}
	return false;
}

void moveEllipes(std::vector<Ellipse> *ellipses, Shape *shape)
{
	Shape windowWalls = getWindowWalls();
	for (size_t i = 0; i < ellipses->size(); i++)
	{
		Ellipse ellipse = (*ellipses)[i];
		// Génère un nombre aléatoire entre 1 et 4 pour pouvoir le multiplier au BALLS_SPEED
		// TODO: FIX THIS (bug, ball trop rapide, voir comment on peut différencier direction et vitesse)
		// attention, ne pas laissé ici, la génération et nombre aléatoire et le changement de vitesse ne doit se faire qu'a la collision avec un mur, par a chaque avancé de la balle
		// int randomSpeed = (1 + (rand() % 4)) * BALLS_SPEED;
		int randomSpeed = 1;

		// Changement des postions de l'ellipse
		(*ellipses)[i].coordinates.x += randomSpeed * ellipse.direction.vx;
		(*ellipses)[i].coordinates.y += randomSpeed * ellipse.direction.vy;

		if (!checkCollision((*ellipses)[i], *shape))
			checkCollision((*ellipses)[i], windowWalls);
	}
}

void handleOnClick(std::vector<Ellipse> *ellipses, int mouseX, int mouseY)
{
	const Ellipse_Coordinates mouseCoordinates = {mouseX, mouseY};
	bool foundIt = false;
	size_t i = 0;

	while (!foundIt && i < ellipses->size())
	{
		Ellipse ellipse = (*ellipses)[i];

		int x_diff = mouseCoordinates.x - ellipse.coordinates.x;
		int y_diff = mouseCoordinates.y - ellipse.coordinates.y;
		int distance = sqrt(x_diff * x_diff + y_diff * y_diff);

		if (distance <= ellipse.rad)
			foundIt = true;
		else
			i++;
	}

	if (foundIt)
	{
		// Suppression d'une ellipse
		(*ellipses).erase((*ellipses).begin() + i);
	}
	else
	{
		// Créaton d'une nouvelle ellipse
		Ellipse ellipse = getEllipseRGBA(mouseCoordinates);
		(*ellipses).push_back(ellipse);
	}
}