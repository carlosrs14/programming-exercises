#include <stdio.h>
#include <SDL3/SDL.h>
#include "component.h"

#define TITLE "show button"
#define WIDTH 600
#define HEIGTH 600

int sdl_initialize(Game* game);
void sdl_quit(Game* game);

int main() {
    Game game = {
        .window = NULL,
        .renderer = NULL
    };

    Button b = {
        .rect = {250.0f, 250.0f, 100.0f, 50.0f},
        .pressed = 0
    };
        
    SDL_Event event;
    short running = 1;

    if (sdl_initialize(&game) == -1) {
        return 1;
    }

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
                float mx = event.button.x;
                float my = event.button.y;
                
                if (mx >= b.rect.x &&
                    mx <= b.rect.x + b.rect.w &&
                    my >= b.rect.y &&
                    my <= b.rect.y + b.rect.h) {

                    b.pressed = !b.pressed;
                    printf("btn pressed\n");
                }
            }
        }

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
        SDL_RenderClear(game.renderer);

        if (b.pressed) {
            SDL_SetRenderDrawColor(game.renderer, 0, 255, 0, 255);
        } else {
            SDL_SetRenderDrawColor(game.renderer, 255, 0, 0, 255);
        }

        SDL_RenderFillRect(game.renderer, &b.rect);

        SDL_RenderPresent(game.renderer);

        SDL_Delay(16);
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
