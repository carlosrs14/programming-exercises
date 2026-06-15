#include <stdio.h>
#include <SDL3/SDL_test_font.h>
#include <SDL3/SDL.h>

#define TITLE "canvas draw"
#define WIDTH 600
#define HEIGTH 600

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Game;


int sdl_initialize(Game* game);
void sdl_quit(Game* game);
void draw_circle(SDL_Renderer* renderer, float centerX, float centerY, float radius);
void draw_cross(Game* game);
void draw_rectangles(Game* game);
void draw_polygon(Game* game);

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

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }


        SDL_SetRenderDrawColor(game.renderer, 20, 20, 20, 255);
        SDL_RenderClear(game.renderer);

        SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
        SDLTest_DrawString(game.renderer, 50, 30, "CANVAS DRAWING SHAPES");


        draw_cross(&game);
        
        draw_rectangles(&game);

        SDL_SetRenderDrawColor(game.renderer, 100, 100, 255, 255);
        draw_circle(game.renderer, 150.0f, 480.0f, 60.0f);
        draw_circle(game.renderer, 150.0f, 480.0f, 40.0f);
        draw_circle(game.renderer, 150.0f, 480.0f, 20.0f);
        SDLTest_DrawString(game.renderer, 120, 560, "CIRCLES");

        draw_polygon(&game);

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

void draw_circle(SDL_Renderer* renderer, float centerX, float centerY, float radius) {
    float x = radius;
    float y = 0;
    float err = 0;

    while (x >= y) {
        SDL_RenderPoint(renderer, centerX + x, centerY + y);
        SDL_RenderPoint(renderer, centerX + y, centerY + x);
        SDL_RenderPoint(renderer, centerX - y, centerY + x);
        SDL_RenderPoint(renderer, centerX - x, centerY + y);
        SDL_RenderPoint(renderer, centerX - x, centerY - y);
        SDL_RenderPoint(renderer, centerX - y, centerY - x);
        SDL_RenderPoint(renderer, centerX + y, centerY - x);
        SDL_RenderPoint(renderer, centerX + x, centerY - y);

        y += 1.0f;
        if (err <= 0) {
            err += 2.0f * y + 1.0f;
        }
        if (err > 0) {
            x -= 1.0f;
            err -= 2.0f * x + 1.0f;
        }
    }
}

void draw_rectangles(Game *game) {
    SDL_SetRenderDrawColor(game->renderer, 100, 255, 100, 255);

    SDLTest_DrawString(game->renderer, 400, 320, "RECTANGLES");

    SDL_FRect fill_rect = { 350.0f, 210.0f, 200.0f, 90.0f };
    SDL_RenderFillRect(game->renderer, &fill_rect);
    
    SDL_FRect outline_rect = { 350.0f, 100.0f, 200.0f, 90.0f };
    SDL_RenderRect(game->renderer, &outline_rect);
}

void draw_polygon(Game *game) {
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 100, 255);

    SDLTest_DrawString(game->renderer, 410, 560, "POLYGON");
    
    SDL_RenderLine(game->renderer, 350.0f, 480.0f, 450.0f, 420.0f);
    SDL_RenderLine(game->renderer, 450.0f, 420.0f, 550.0f, 480.0f);
    SDL_RenderLine(game->renderer, 550.0f, 480.0f, 450.0f, 540.0f);
    SDL_RenderLine(game->renderer, 450.0f, 540.0f, 350.0f, 480.0f);
}

void draw_cross(Game *game) {
    SDL_SetRenderDrawColor(game->renderer, 255, 100, 100, 255);
    SDLTest_DrawString(game->renderer, 120, 320, "CROSS");

    SDL_RenderLine(game->renderer, 50.0f, 100.0f, 250.0f, 300.0f);
    SDL_RenderLine(game->renderer, 250.0f, 100.0f, 50.0f, 300.0f);
}
