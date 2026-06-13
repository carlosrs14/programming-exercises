#include <stdio.h>
#include <SDL3/SDL_test_font.h>
#include <SDL3/SDL.h>

#define TITLE "show dialog"
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

    SDL_Event event;
    short running = 1;

    SDL_FRect btn_info = { 150.0f, 200.0f, 300.0f, 60.0f };
    SDL_FRect btn_error = { 150.0f, 300.0f, 300.0f, 60.0f };

    float mouse_x = 0;
    float mouse_y = 0;

    if (sdl_initialize(&game) == -1) {
        return 1;
    }

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }

            if (event.type == SDL_EVENT_MOUSE_MOTION) {
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
                float mx = event.button.x;
                float my = event.button.y;

                if (mx >= btn_info.x && mx <= btn_info.x + btn_info.w &&
                    my >= btn_info.y && my <= btn_info.y + btn_info.h) {
                    
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, 
                                              "Information", 
                                              "This is an SDL3 native info message dialog box!", 
                                              game.window);
                }
                else if (mx >= btn_error.x && mx <= btn_error.x + btn_error.w &&
                         my >= btn_error.y && my <= btn_error.y + btn_error.h) {
                    
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
                                              "Error Alert", 
                                              "A critical simulated error occurred!", 
                                              game.window);
                }
            }
        }

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
        SDL_RenderClear(game.renderer);

        SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
        SDLTest_DrawString(game.renderer, 80, 100, "SDL3 NATIVE DIALOG MESSAGES");

        if (mouse_x >= btn_info.x && mouse_x <= btn_info.x + btn_info.w &&
            mouse_y >= btn_info.y && mouse_y <= btn_info.y + btn_info.h) {
            SDL_SetRenderDrawColor(game.renderer, 100, 100, 255, 255);
        } else {
            SDL_SetRenderDrawColor(game.renderer, 50, 50, 150, 255);
        }
        SDL_RenderFillRect(game.renderer, &btn_info);
        SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
        SDLTest_DrawString(game.renderer, btn_info.x + 35, btn_info.y + 20,"SHOW INFO DIALOG");

        if (mouse_x >= btn_error.x && mouse_x <= btn_error.x + btn_error.w &&
            mouse_y >= btn_error.y && mouse_y <= btn_error.y + btn_error.h) {
            SDL_SetRenderDrawColor(game.renderer, 255, 100, 100, 255);
        } else {
            SDL_SetRenderDrawColor(game.renderer, 150, 50, 50, 255);
        }
        SDL_RenderFillRect(game.renderer, &btn_error);
        SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
        SDLTest_DrawString(game.renderer, btn_error.x + 30, btn_error.y + 20, "SHOW ERROR DIALOG");

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
