#include <optional>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "constants.h"
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "wall.h"
#include "ellipse.h"
#include "SDL2/SDL.h"

void draw(SDL_Renderer *renderer, std::vector<Ellipse> *ellipses, Shape *walls)
{
    /* Gestion de l'affichage du jeu */
    drawEllipses(renderer, ellipses);
    drawShape(renderer, walls);
};

void hexToRGB(std::string hexColor, Uint8 &r, Uint8 &g, Uint8 &b)
{
    // Vérifier si la longueur est correcte
    if (hexColor.length() != 6)
    {
        std::cout << "Invalid hex color format" << std::endl;
        return;
    }
    // Extraire les valeurs de rouge, vert et bleu
    r = std::stoi(hexColor.substr(0, 2), nullptr, 16);
    g = std::stoi(hexColor.substr(2, 2), nullptr, 16);
    b = std::stoi(hexColor.substr(4, 2), nullptr, 16);
}

bool handleEvent(std::vector<Ellipse> *ellipses)
{
    /* Gestion des inputs utilisateurs */
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            return false;
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            handleOnClick(ellipses, mouseX, mouseY);
        }
        return true;
    }
    return true;
}

int main(int argc, char **argv)
{
    SDL_Window *gWindow;
    SDL_Renderer *renderer;

    // Création de la fenêtre
    gWindow = init("Guerin Lucie, Jouin Baptiste, IMAC");

    if (!gWindow)
    {
        SDL_Log("Failed to initialize!\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC

    /*  GAME INIT  */
    std::vector<Ellipse> ellipses;

    // Initialisation des Murs
    Shape walls = getCustomWalls();

    // Utilisation des paramètres d'entré
    if (argc <= 2)
    {
        // Si l’utilisateur exécute le jeu avec un argument en ligne de commande, changer le nombre de balles en fonction de l’argument.
        int ballsCount = argc == 2 ? std::stoi(argv[1]) : BALLS_COUNT;

        // Initialisation des ellipses dans un vecteur
        for (int i = 0; i < ballsCount; i++)
        {
            Ellipse ellipse = getEllipseRGBA();
            ellipses.push_back(ellipse);
        }
    }

    // Si l’utilisateur exécute le jeu avec plusieurs arguments, ajouter une balle par argument, l’argument définira la couleur de balle.
    else
    {
        for (int i = 1; i < argc; i++)
        {
            Uint8 r, g, b;
            hexToRGB(argv[i], r, g, b);
            Ellipse_Color color = {r, g, b};

            Ellipse ellipse = getEllipseRGBA(std::nullopt, color);
            ellipses.push_back(ellipse);
        }
    }

    /*  GAME LOOP  */
    do
    {
        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // DESSIN
        draw(renderer, &ellipses, &walls);

        // UPDATE
        SDL_RenderPresent(renderer);

        // MISE À JOUR DU JEU POUR LA PROCHAINE FRAME
        moveEllipes(&ellipses, &walls);

        // PAUSE en ms
        SDL_Delay(1000 / 30);
    } while (handleEvent(&ellipses));

    // Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}
