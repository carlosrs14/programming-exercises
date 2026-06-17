#pragma once

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_test_font.h>

#define GAME_WITDH 500
#define GAME_HEIGTH 500

#define PLAYING 0
#define LOSS -1
#define WON 1

#define MINE_VAL 10
#define COLS 20
#define ROWS 20
#define MINES 50

typedef struct button {
    SDL_FRect rect;
    int pressed;
} Button;

typedef struct game {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Game;

typedef struct cell {
    int value;
    bool revealed;
    bool flagged;
    bool exploded;
    Button btn;
    char label[4];
} Cell;

typedef struct board {
    int cols;
    int rows;
    int n_mines;
    int** mine_coords;
    Cell** matrix;
    int state;
} Board;

typedef struct point {
    int row;
    int col;
} Point;

int sdl_init(Game* game);
void sdl_quit(Game* game);
void generate_random_mines(Board* board);
void generate_board(Board *board);
bool is_mine_position_unique(int** mine_coords, int current_count, int row, int col);
void free_board(Board *board);
int count_adjacent_mines(const Board* board, int row, int col);
void reveal_cell(Board* board, int row, int col);
void flag_cell(Board* board, int row, int col);
void render_board(SDL_Renderer *renderer, Board *board, float mouse_x, float mouse_y);
bool is_point_in_rect(float x, float y, const SDL_FRect* r);
Point get_current_point(const float x, const float y, const Board* board);
bool check_win_condition(const Board* board);
void restart_game(Board* board);
