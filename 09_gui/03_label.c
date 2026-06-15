#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_test_font.h>
#include "component.h"

#define TITLE "show label"
#define WIDTH 600
#define HEIGTH 600

int sdl_initialize(Game* game);
void sdl_quit(Game* game);

int main() {
    Game game = {
        .window = NULL,
        .renderer = NULL
    };

    Label label = {
        .x = 200.0f,
        .y = 200.0f,
        .text = "Hello"
    };

    if (sdl_initialize(&game) == -1) {
        return 1;
    }

    SDL_Event event;
    short running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
        SDL_RenderClear(game.renderer);

        SDL_SetRenderDrawColor(game.renderer, 0, 255, 0, 255);

        SDLTest_DrawString(game.renderer, label.x, label.y, label.text);

        SDL_RenderPresent(game.renderer);
    }

    sdl_quit(&game);

    return 0;
}

int sdl_initialize(Game* game) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return -1;
    }

    game->window = SDL_CreateWindow(
        TITLE,
        WIDTH, HEIGTH, 0
    );
    if (!game->window) {
        return -1;
    }

    game->renderer = SDL_CreateRenderer(game->window, NULL);
    if (!game->renderer) {
        return -1;
    }

    return 0;
}

void sdl_quit(Game* game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}
