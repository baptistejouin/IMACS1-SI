#include "constants.h"
#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "wall.h"
#include "ellipseRGBA.h"
#include "windows.h"

void draw(SDL_Renderer *renderer, Ellipse ellipses[], Walls walls)
{
    /* Remplissez cette fonction pour faire l'affichage du jeu */
    drawEllipses(renderer, ellipses);
    moveEllipes(ellipses, walls);
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
    bool is_running = true;

    // Creation de la fenetre
    gWindow = init("Awesome Game");

    if (!gWindow)
    {
        SDL_Log("Failed to initialize!\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC

    // Temps de début de la boucle de mise à jour
    Uint32 startTime = SDL_GetTicks();

    // Initialisation des ellipses
    Ellipse ellipses[BALLS_COUNT];

    for (auto &ellipse : ellipses)
    {
        ellipse = getEllipseRGBA();
    }

    // Initialisation des Murs
    Walls walls = getAllWalls();

    /*  GAME LOOP  */
    while (true)
    {
        // Calcul du temps écoulé depuis le début de la boucle de mise à jour
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        // INPUTS
        is_running = handleEvent();
        if (!is_running)
            break;

        // GESTION ACTEURS

        // ...

        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // DESSIN
        // Calcul de la distance parcourue par l'ellipse en fonction de la vitesse et du temps écoulé

        draw(renderer, ellipses, walls);

        // Mise à jour de l'affichage
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000 / 30);

        // Mise à jour du temps de début de la boucle de mise à jour
        startTime = SDL_GetTicks();
    }

    //Faire disparaître balles avec cliques
     while (true)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SDL_Quit();
                return 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);

                int x_diff = mouse_x - ellipse_x;
                int y_diff = mouse_y - ellipse_y;
                int distance = sqrt(x_diff * x_diff + y_diff * y_diff);

                if (distance <= ellipse_r)
                {
                    ellipse_visible = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (ellipse_visible)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            for (int i = 0; i < 360; i++)
            {
                float degInRad = i * M_PI / 180;
                SDL_RenderDrawPoint(renderer, ellipse_x + cos(degInRad) * ellipse_r, ellipse_y + sin(degInRad) * ellipse_r);
            }
        }

        SDL_RenderPresent(renderer);
    }

    
    // Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}
