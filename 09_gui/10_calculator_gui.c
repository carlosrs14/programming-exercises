#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL3/SDL_test_font.h>
#include <SDL3/SDL.h>
#include "component.h"

#define TITLE "calculator"
#define WIDTH 400
#define HEIGTH 500

typedef struct {
    Button component;
    char label[4];
} CalcButton;

int sdl_initialize(Game* game);
void sdl_quit(Game* game);
void init_buttons(CalcButton* buttons);
short is_point_in_rect(float x, float y, const SDL_FRect* r);
void calculator_press(char* current_input, double* accumulator, char* op, short* reset_display, const char* label);
void render_calculator(SDL_Renderer* renderer, const char* display_text, const CalcButton* buttons, int num_buttons, float mouse_x, float mouse_y);

int main() {
    Game game = {
        .window = NULL,
        .renderer = NULL
    };

    if (sdl_initialize(&game) == -1) {
        return 1;
    }

    CalcButton buttons[16];
    init_buttons(buttons);

    char current_input[32] = "0";
    double accumulator = 0.0;
    char op = '\0';
    short reset_display = 0;

    float mouse_x = 0.0f;
    float mouse_y = 0.0f;
    SDL_Event event;
    short running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_EVENT_MOUSE_MOTION) {
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
                float mx = event.button.x;
                float my = event.button.y;
                for (int i = 0; i < 16; i++) {
                    if (is_point_in_rect(mx, my, &buttons[i].component.rect)) {
                        buttons[i].component.pressed = 1;
                        calculator_press(current_input, &accumulator, &op, &reset_display, buttons[i].label);
                    }
                }
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
                for (int i = 0; i < 16; i++) {
                    buttons[i].component.pressed = 0;
                }
            }
        }

        render_calculator(game.renderer, current_input, buttons, 16, mouse_x, mouse_y);
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

void init_buttons(CalcButton* buttons) {
    const char* labels[16] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };

    float start_x = 20.0f;
    float start_y = 100.0f;
    float btn_w = 80.0f;
    float btn_h = 80.0f;
    float gap = 13.0f;

    for (int i = 0; i < 16; i++) {
        int row = i / 4;
        int col = i % 4;
        buttons[i].component.rect = (SDL_FRect){
            start_x + col * (btn_w + gap),
            start_y + row * (btn_h + gap),
            btn_w,
            btn_h
        };
        buttons[i].component.pressed = 0;
        snprintf(buttons[i].label, sizeof(buttons[i].label), "%s", labels[i]);
    }
}

short is_point_in_rect(float x, float y, const SDL_FRect* r) {
    return x >= r->x && x <= r->x + r->w && y >= r->y && y <= r->y + r->h;
}

void calculator_press(char* current_input, double* accumulator, char* op, short* reset_display, const char* label) {
    if (label[0] >= '0' && label[0] <= '9') {
        if (*reset_display || strcmp(current_input, "0") == 0) {
            snprintf(current_input, 32, "%s", label);
            *reset_display = 0;
        } else {
            if (strlen(current_input) < 15) {
                strcat(current_input, label);
            }
        }
    } else if (strcmp(label, "C") == 0) {
        snprintf(current_input, 32, "0");
        *accumulator = 0.0;
        *op = '\0';
        *reset_display = 0;
    } else if (strcmp(label, "=") == 0) {
        if (*op != '\0') {
            double current_val = atof(current_input);
            double result = 0.0;
            switch (*op) {
                case '+':
                    result = *accumulator + current_val;
                    break;
                case '-':
                    result = *accumulator - current_val;
                    break;
                case '*':
                    result = *accumulator * current_val;
                    break;
                case '/':
                    if (current_val != 0.0) {
                        result = *accumulator / current_val;
                    } else {
                        snprintf(current_input, 32, "Error");
                        *op = '\0';
                        *reset_display = 1;
                        return;
                    }
                    break;
                
                default:
                    break;
            }
            snprintf(current_input, 32, "%g", result);
            *op = '\0';
            *reset_display = 1;
        }
    } else {
        *accumulator = atof(current_input);
        *op = label[0];
        *reset_display = 1;
    }
}

void render_calculator(SDL_Renderer* renderer, const char* display_text, const CalcButton* buttons, int num_buttons, float mouse_x, float mouse_y) {
    SDL_SetRenderDrawColor(renderer, 25, 25, 35, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 10, 10, 15, 255);
    SDL_FRect display_box = { 20.0f, 20.0f, 360.0f, 60.0f };
    SDL_RenderFillRect(renderer, &display_box);
    SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);
    SDL_RenderRect(renderer, &display_box);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDLTest_DrawString(renderer, 35.0f, 40.0f, display_text);

    for (int i = 0; i < num_buttons; i++) {
        const CalcButton* btn = &buttons[i];
        
        if (btn->component.pressed) {
            SDL_SetRenderDrawColor(renderer, 60, 120, 215, 255);
        } else if (is_point_in_rect(mouse_x, mouse_y, &btn->component.rect)) {
            SDL_SetRenderDrawColor(renderer, 45, 45, 60, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 35, 35, 45, 255);
        }
        
        SDL_RenderFillRect(renderer, &btn->component.rect);
        SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);
        SDL_RenderRect(renderer, &btn->component.rect);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDLTest_DrawString(renderer, btn->component.rect.x + 35.0f, btn->component.rect.y + 35.0f, btn->label);
    }

    SDL_RenderPresent(renderer);
}
