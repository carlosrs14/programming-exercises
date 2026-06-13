#include <stdio.h>
#include <SDL3/SDL_test_font.h>
#include <SDL3/SDL.h>

#define TITLE "show layouts"
#define WIDTH 600
#define HEIGTH 600

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Game;

void layout_hbox(SDL_FRect parent, SDL_FRect* children, int count, float spacing) {
    float total_spacing = spacing * (count - 1);
    float item_w = (parent.w - total_spacing) / count;
    for (int i = 0; i < count; i++) {
        children[i].x = parent.x + i * (item_w + spacing);
        children[i].y = parent.y;
        children[i].w = item_w;
        children[i].h = parent.h;
    }
}

void layout_vbox(SDL_FRect parent, SDL_FRect* children, int count, float spacing) {
    float total_spacing = spacing * (count - 1);
    float item_h = (parent.h - total_spacing) / count;
    for (int i = 0; i < count; i++) {
        children[i].x = parent.x;
        children[i].y = parent.y + i * (item_h + spacing);
        children[i].w = parent.w;
        children[i].h = item_h;
    }
}

int sdl_initialize(Game* game);
void sdl_quit(Game* game);

int main() {
    Game game = {
        .window = NULL,
        .renderer = NULL
    };

    SDL_Event event;
    short running = 1;

    if (sdl_initialize(&game) == -1) {
        return 1;
    }

    SDL_FRect hbox_container = { 50.0f, 80.0f, 500.0f, 150.0f };
    SDL_FRect vbox_container = { 50.0f, 360.0f, 500.0f, 180.0f };

    SDL_FRect hbox_children[3];
    SDL_FRect vbox_children[3];

    layout_hbox(hbox_container, hbox_children, 3, 20.0f);
    layout_vbox(vbox_container, vbox_children, 3, 10.0f);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
        SDL_RenderClear(game.renderer);

        SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
        SDLTest_DrawString(game.renderer, 50, 40, "HBOX (HORIZONTAL)");
        SDLTest_DrawString(game.renderer, 50, 320,"VBOX (VERTICAL)");

        SDL_SetRenderDrawColor(game.renderer, 40, 40, 40, 255);
        SDL_RenderRect(game.renderer, &hbox_container);

        for (int i = 0; i < 3; i++) {
            if (i == 0) SDL_SetRenderDrawColor(game.renderer, 255, 100, 100, 255);
            else if (i == 1) SDL_SetRenderDrawColor(game.renderer, 100, 255, 100, 255);
            else SDL_SetRenderDrawColor(game.renderer, 100, 100, 255, 255);

            SDL_RenderFillRect(game.renderer, &hbox_children[i]);
        }

        SDL_SetRenderDrawColor(game.renderer, 40, 40, 40, 255);
        SDL_RenderRect(game.renderer, &vbox_container);

        for (int i = 0; i < 3; i++) {
            if (i == 0) SDL_SetRenderDrawColor(game.renderer, 255, 255, 100, 255);
            else if (i == 1) SDL_SetRenderDrawColor(game.renderer, 255, 100, 255, 255);
            else SDL_SetRenderDrawColor(game.renderer, 100, 255, 255, 255);

            SDL_RenderFillRect(game.renderer, &vbox_children[i]);
        }

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
