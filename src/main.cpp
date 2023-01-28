#include <optional>
#include "constants.h"
#include "vector"
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "wall.h"
#include "ellipseRGBA.h"
#include "SDL2/SDL.h"

void draw(SDL_Renderer *renderer, std::vector<Ellipse> *ellipses, Shape *walls)
{
    /* Gestion de l'affichage du jeu */
    drawEllipses(renderer, ellipses);
    drawShape(renderer, walls);
};

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
    // Initialisation des Murs
    Shape walls = getCustomWalls();

    // Initialisation des ellipses dans un vecteur
    std::vector<Ellipse> ellipses;
    for (size_t i = 0; i < BALLS_COUNT; i++)
    {
        Ellipse ellipse = getEllipseRGBA();
        ellipses.push_back(ellipse);
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
