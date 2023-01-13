#include "constants.h"
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "wall.h"
#include "ellipseRGBA.h"

void draw(SDL_Renderer *renderer, Ellipse ellipses[], Walls *walls)
{
    /* Remplissez cette fonction pour faire l'affichage du jeu */
    // TODO: Uniquement l'affichage, le traitement doit être fait un amont. Deuxièmement, la fonction draw() ne prend pas en compte le traitement des ellipses et des murs avant l'affichage. Cela doit être fait avant que les ellipses et les murs ne soient dessinés.
    drawEllipses(renderer, ellipses);
    moveEllipes(ellipses, walls);
    drawWalls(renderer, walls);
};

bool handleEvent()
{
    /* Remplissez cette fonction pour gérer les inputs utilisateurs */
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    SDL_Window *gWindow;
    SDL_Renderer *renderer;

    // Creation de la fenetre
    gWindow = init("Awesome Game");

    if (!gWindow)
    {
        SDL_Log("Failed to initialize!\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC

    /*  GAME INIT  */
    // Initialisation des Murs
    Walls walls = getAllWalls();

    // Initialisation des ellipses
    Ellipse ellipses[BALLS_COUNT];
    for (auto &ellipse : ellipses)
    {
        ellipse = getEllipseRGBA(&walls);
    }

    /*  GAME LOOP  */
    do
    {
        // TODO: GESTION ACTEURS

        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // DESSIN
        draw(renderer, ellipses, &walls);

        // UPDATE
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000 / 30);
    } while (handleEvent());

    // Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}
