#include <stdio.h>
#include <SDL2/SDL.h>

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
        sdl_quit(&game);
        perror("error sdl");
        return 1;
    }

    SDL_RenderClear(game.renderer);

    SDL_RenderPresent(game.renderer);

    SDL_Delay(5000);

    sdl_quit(&game);

    return 0;
}

int sdl_initialize(struct Game *game) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return -1;
    }
    
    game->window = SDL_CreateWindow(
        TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGTH, 0
    );
    if (!game->window) {
        return -1;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, 0);
    if (!game->renderer) {
        return -1;
    }

    return 0;
}

void sdl_quit(struct Game *game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    exit(0);
}
