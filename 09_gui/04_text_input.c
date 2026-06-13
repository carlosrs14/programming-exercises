#include <stdio.h>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_test_font.h>

#define TITLE "read text input"
#define WIDTH 600
#define HEIGTH 600

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Game;


int sdl_initialize(Game* game);
void sdl_quit(Game* game);

int main() {
    Game game = {
        .window = NULL,
        .renderer = NULL
    };

    char text_input[64] = "";
    SDL_Event event;
    short running = 1;

    if (sdl_initialize(&game) == -1) {
        return 1;
    }

    SDL_StartTextInput(game.window);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }

            if (event.type == SDL_EVENT_TEXT_INPUT) {
                if (strlen(text_input) + strlen(event.text.text) < sizeof(text_input) - 1) {
                    strcat(text_input, event.text.text);
                }
            }

            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_BACKSPACE) {
                    size_t len = strlen(text_input);
                    if (len > 0) {
                        text_input[len - 1] = '\0';
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
        SDL_RenderClear(game.renderer);

        SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
        SDLTest_DrawString(game.renderer, 200, 200, "TYPE SOMETHING:");

        SDL_SetRenderDrawColor(game.renderer, 100, 100, 100, 255);
        SDL_FRect box = { 185, 230, 200, 20 };
        SDL_RenderRect(game.renderer, &box);

        SDL_SetRenderDrawColor(game.renderer, 0, 255, 0, 255);
        
        char display_text[128];
        snprintf(display_text, sizeof(display_text), "%s_", text_input);
        SDLTest_DrawString(game.renderer, 200, 240, display_text);

        SDL_RenderPresent(game.renderer);
        SDL_Delay(16);
    }

    SDL_StopTextInput(game.window);
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
