#include <stdio.h>
#include <SDL3/SDL.h>
#include "font.h"

#define TITLE "personalized font"
#define WIDTH 600
#define HEIGTH 600

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Game;

int sdl_initialize(Game* game);
void sdl_quit(Game* game);

int main() {
    // still been too difficult
    return 0;
}

void sdl_quit(Game* game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}
