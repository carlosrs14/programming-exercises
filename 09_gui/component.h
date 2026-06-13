#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL3/SDL.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Game;

typedef struct {
    SDL_FRect rect;
    short pressed;
} Button;

typedef struct {
    float x;
    float y;
    const char* text;
} Label;

typedef struct {
    SDL_FRect rect;
    char text[64];
} TextInput;

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

typedef struct {
    SDL_MessageBoxFlags flags;
    const char* title;
    const char* message;
} Dialog;

#endif
