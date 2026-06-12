#include <stdio.h>
#include <SDL3/SDL.h>

#define TITLE "open window"
#define WIDTH HEIGTH
#define HEIGTH 600

struct Game {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

int sdl_initialize(struct Game* game);
void sdl_quit(struct Game* game);

int main() {
    struct Game game = {
        .window = NULL,
        .renderer = NULL
    };

    if (sdl_initialize(&game) == -1) {
        fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
        sdl_quit(&game);
        return 1;
    }

    SDL_RenderClear(game.renderer);

    SDL_RenderPresent(game.renderer);

    SDL_Delay(5000);

    sdl_quit(&game);

    return 0;
}

int sdl_initialize(struct Game *game) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("failed at SDL_Init\n");
        return -1;
    }
    
    game->window = SDL_CreateWindow(
        TITLE,
        WIDTH,
        HEIGTH,
        0
    );
    if (!game->window) {
        printf("failed at SDL_CreateWindow\n");
        return -1;
    }

    game->renderer = SDL_CreateRenderer(game->window, NULL);
    if (!game->renderer) {
        printf("failed at SDL_CreateRenderer\n");
        return -1;
    }

    return 0;
}

void sdl_quit(struct Game *game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}
