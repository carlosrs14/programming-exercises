#include <stdio.h>
#include <SDL3/SDL_test_font.h>
#include <SDL3/SDL.h>

#define TITLE "show menu"
#define WIDTH 600
#define HEIGTH 600

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Game;

typedef struct {
    SDL_FRect menu_bar;
    SDL_FRect btn_file;
    SDL_FRect btn_edit;
    SDL_FRect file_dropdown;
    SDL_FRect edit_dropdown;
    SDL_FRect file_items[3];
    SDL_FRect edit_items[2];
    const char* file_texts[3];
    const char* edit_texts[2];
    short file_open;
    short edit_open;
    float mouse_x;
    float mouse_y;
} Menu;

int sdl_initialize(Game* game);
void sdl_quit(Game* game);
void menu_init(Menu* menu);
short is_point_in_rect(float x, float y, const SDL_FRect* r);
void menu_handle_event(Menu* menu, const SDL_Event* event, short* running);
void menu_render(SDL_Renderer* renderer, const Menu* menu);

int main() {
    Game game = {
        .window = NULL,
        .renderer = NULL
    };

    Menu menu;
    SDL_Event event;
    short running = 1;

    menu_init(&menu);

    if (sdl_initialize(&game) == -1) {
        return 1;
    }

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
            menu_handle_event(&menu, &event, &running);
        }

        menu_render(game.renderer, &menu);
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

void menu_init(Menu* menu) {
    menu->menu_bar = (SDL_FRect){ 0.0f, 0.0f, (float)WIDTH, 30.0f };
    menu->btn_file = (SDL_FRect){ 10.0f, 5.0f, 50.0f, 20.0f };
    menu->btn_edit = (SDL_FRect){ 70.0f, 5.0f, 50.0f, 20.0f };
    menu->file_dropdown = (SDL_FRect){ 10.0f, 30.0f, 100.0f, 90.0f };
    menu->edit_dropdown = (SDL_FRect){ 70.0f, 30.0f, 100.0f, 60.0f };

    menu->file_items[0] = (SDL_FRect){ 10.0f, 30.0f, 100.0f, 30.0f };
    menu->file_items[1] = (SDL_FRect){ 10.0f, 60.0f, 100.0f, 30.0f };
    menu->file_items[2] = (SDL_FRect){ 10.0f, 90.0f, 100.0f, 30.0f };
    menu->file_texts[0] = "NEW";
    menu->file_texts[1] = "OPEN";
    menu->file_texts[2] = "EXIT";

    menu->edit_items[0] = (SDL_FRect){ 70.0f, 30.0f, 100.0f, 30.0f };
    menu->edit_items[1] = (SDL_FRect){ 70.0f, 60.0f, 100.0f, 30.0f };
    menu->edit_texts[0] = "UNDO";
    menu->edit_texts[1] = "REDO";

    menu->file_open = 0;
    menu->edit_open = 0;
    menu->mouse_x = 0.0f;
    menu->mouse_y = 0.0f;
}

short is_point_in_rect(float x, float y, const SDL_FRect* r) {
    return x >= r->x && x <= r->x + r->w && y >= r->y && y <= r->y + r->h;
}

void menu_handle_event(Menu* menu, const SDL_Event* event, short* running) {
    if (event->type == SDL_EVENT_MOUSE_MOTION) {
        menu->mouse_x = event->motion.x;
        menu->mouse_y = event->motion.y;
    }
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && event->button.button == SDL_BUTTON_LEFT) {
        float mx = event->button.x;
        float my = event->button.y;

        if (is_point_in_rect(mx, my, &menu->btn_file)) {
            menu->file_open = !menu->file_open;
            menu->edit_open = 0;
        }
        else if (is_point_in_rect(mx, my, &menu->btn_edit)) {
            menu->edit_open = !menu->edit_open;
            menu->file_open = 0;
        }
        else if (menu->file_open) {
            short clicked_outside = 1;
            for (int i = 0; i < 3; i++) {
                if (is_point_in_rect(mx, my, &menu->file_items[i])) {
                    clicked_outside = 0;
                    printf("File menu clicked: %s\n", menu->file_texts[i]);
                    if (i == 2) {
                        *running = 0;
                    }
                }
            }
            if (clicked_outside) {
                menu->file_open = 0;
            }
        }
        else if (menu->edit_open) {
            short clicked_outside = 1;
            for (int i = 0; i < 2; i++) {
                if (is_point_in_rect(mx, my, &menu->edit_items[i])) {
                    clicked_outside = 0;
                    printf("Edit menu clicked: %s\n", menu->edit_texts[i]);
                }
            }
            if (clicked_outside) {
                menu->edit_open = 0;
            }
        }
    }
}

void menu_render(SDL_Renderer* renderer, const Menu* menu) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDLTest_DrawString(renderer, 50, 250, "CLICK FILE OR EDIT TO SEE DROPDOWN");

    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
    SDL_RenderFillRect(renderer, &menu->menu_bar);

    short hover_file = is_point_in_rect(menu->mouse_x, menu->mouse_y, &menu->btn_file);
    if (menu->file_open || hover_file) {
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(renderer, &menu->btn_file);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDLTest_DrawString(renderer, menu->btn_file.x + 5.0f, menu->btn_file.y + 3.0f, "FILE");

    short hover_edit = is_point_in_rect(menu->mouse_x, menu->mouse_y, &menu->btn_edit);
    if (menu->edit_open || hover_edit) {
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(renderer, &menu->btn_edit);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDLTest_DrawString(renderer, menu->btn_edit.x + 5.0f, menu->btn_edit.y + 3.0f, "EDIT");

    if (menu->file_open) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &menu->file_dropdown);
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        SDL_RenderRect(renderer, &menu->file_dropdown);

        for (int i = 0; i < 3; i++) {
            if (is_point_in_rect(menu->mouse_x, menu->mouse_y, &menu->file_items[i])) {
                SDL_SetRenderDrawColor(renderer, 0, 120, 215, 255);
                SDL_RenderFillRect(renderer, &menu->file_items[i]);
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDLTest_DrawString(renderer, menu->file_items[i].x + 10.0f, menu->file_items[i].y + 7.0f, menu->file_texts[i]);
        }
    }
    else if (menu->edit_open) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &menu->edit_dropdown);
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        SDL_RenderRect(renderer, &menu->edit_dropdown);

        for (int i = 0; i < 2; i++) {
            if (is_point_in_rect(menu->mouse_x, menu->mouse_y, &menu->edit_items[i])) {
                SDL_SetRenderDrawColor(renderer, 0, 120, 215, 255);
                SDL_RenderFillRect(renderer, &menu->edit_items[i]);
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDLTest_DrawString(renderer, menu->edit_items[i].x + 10.0f, menu->edit_items[i].y + 7.0f, menu->edit_texts[i]);
        }
    }

    SDL_RenderPresent(renderer);
}
