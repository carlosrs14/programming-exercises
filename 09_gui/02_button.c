#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 600
#define HEIGTH 600

typedef struct {
    SDL_Rect rect;
    short pressed;
} Button;

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
        WIDTH, HEIGTH, 0
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Button b = {
        .rect = {250, 250, 100, 50},
        .pressed = 0
    };
        
    SDL_Event event;
    short running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mx = event.button.x;
                int my = event.button.y;
                
                if (mx >= b.rect.x &&
                    mx <= b.rect.x + b.rect.w &&
                    my >= b.rect.y &&
                    my <= b.rect.y + b.rect.h) {

                    b.pressed = !b.pressed;
                    printf("btn pressed\n");
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (b.pressed)
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        SDL_RenderFillRect(renderer, &b.rect);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
