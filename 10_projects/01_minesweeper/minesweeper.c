#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
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


void sdl_quit(Game* game);
int sdl_init(Game* game);
void generate_random_mines(Board* board);
void generate_board(Board* board);
bool is_mine_position_unique(int** mine_coords, int current_count, int row, int col);
void free_board(Board* board);
void print_board(const Board* board);
int count_adjacent_mines(const Board* board, int row, int col);
void reveal_cell(Board* board, int row, int col);
void flag_cell(Board* board, int row, int col);
void render_board(SDL_Renderer* renderer, Board* board, float x, float y);
bool is_point_in_rect(float x, float y, const SDL_FRect* r);
Point get_current_point(const float x, const float y, const Board* board);
bool check_win_condition(const Board* board);
void restart_game(Board* board);

int main() {
    Game game = {
        .renderer = NULL,
        .window = NULL
    };
    Board board = {
        .n_mines = MINES,
        .cols = COLS,
        .rows = ROWS,
        .matrix = NULL,
        .mine_coords = NULL,
        .state = PLAYING
    };
    
    generate_random_mines(&board);
    generate_board(&board);
    sdl_init(&game);

    float mouse_x = 0.0f, mouse_y = 0.0f;

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            else if (event.type == SDL_EVENT_MOUSE_MOTION) {
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (board.state == PLAYING) {
                    Point p = get_current_point(mouse_x, mouse_y, &board);

                    if (p.row != -1 && p.col != -1) {
                        switch (event.button.button) {
                            case SDL_BUTTON_LEFT:
                                reveal_cell(&board, p.row, p.col);
                                if (board.state == PLAYING && check_win_condition(&board)) {
                                    board.state = WON;
                                    for (int r = 0; r < board.rows; r++) {
                                        for (int c = 0; c < board.cols; c++) {
                                            if (board.matrix[r][c].value == MINE_VAL) {
                                                board.matrix[r][c].flagged = true;
                                            }
                                        }
                                    }
                                }
                                break;

                            case SDL_BUTTON_RIGHT:
                                flag_cell(&board, p.row, p.col);
                                break;
                        }
                    }
                }
            }
            else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_R) {
                    restart_game(&board);
                }
            }
        }

        render_board(game.renderer, &board, mouse_x, mouse_y);
        SDL_Delay(16);
    }

    free_board(&board);
    sdl_quit(&game);
    return 0;
}

void sdl_quit(Game* game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

int sdl_init(Game* game) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return -1;
    }

    game->window = SDL_CreateWindow("MinesWeeper", GAME_WITDH, GAME_HEIGTH, 0);
    if (game->window == NULL) {
        return -1;
    }

    game->renderer = SDL_CreateRenderer(game->window, NULL);
    if (game->renderer == NULL) {
        return 0;
    }
    return 0;
}

void generate_random_mines(Board* board) {
    srand(time(NULL));
    int mines = board->n_mines;
    int cols = board->cols;
    int rows = board->rows;

    board->mine_coords = (int**) malloc(sizeof(int*) * mines);
    for (int i = 0; i < mines; i++) {
        board->mine_coords[i] = (int*) malloc(sizeof(int) * 2);
    }
    
    for (int i = 0; i < mines; i++) {
        int col = rand() % cols;
        int row = rand() % rows;

        if (is_mine_position_unique(board->mine_coords, i, row, col)) {
            board->mine_coords[i][0] = row;
            board->mine_coords[i][1] = col;
        } else {
            i--;
        }
    }
}

void generate_board(Board *board) {
    board->matrix = (Cell**) malloc(sizeof(Cell*) * board->rows);

    for (int i = 0; i < board->rows; i++) {
        board->matrix[i] = (Cell*) calloc(board->cols, sizeof(Cell));
    }
    
    for (int i = 0; i < board->n_mines; i++) {
        board->matrix[board->mine_coords[i][0]][board->mine_coords[i][1]].value = MINE_VAL;
    }

    float start_x = 20.0f;
    float start_y = 20.0f;
    float btn_w = 20.0f;
    float btn_h = 20.0f;
    float gap = 1.0f;

    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            Cell* cell = &board->matrix[i][j];
            cell->btn.rect = (SDL_FRect) {
                start_x + j * (btn_w + gap),
                start_y + i * (btn_h + gap),
                btn_w,
                btn_h
            };
            cell->exploded = false;

            if (cell->value != MINE_VAL) {
                cell->value = count_adjacent_mines(board, i, j);
                if (cell->value > 0) {
                    snprintf(cell->label, sizeof(cell->label), "%d", cell->value);
                } else {
                    cell->label[0] = '\0';
                }
            } else {
                snprintf(cell->label, sizeof(cell->label), "*");
            }
        }
    }
}

bool is_mine_position_unique(int** mine_coords, int current_count, int row, int col) {
    for (int i = 0; i < current_count; i++) {
        if (mine_coords[i][0] == row && mine_coords[i][1] == col) {
            return false;
        }
    }
    return true;    
}

void free_board(Board *board) {
    if (board->matrix) {
        for (int i = 0; i < board->rows; i++) {
            free(board->matrix[i]);
        }
        free(board->matrix);
    }
    if (board->mine_coords) {
        for (int i = 0; i < board->n_mines; i++) {
            free(board->mine_coords[i]);
        }
        free(board->mine_coords);
    }
}

void print_board(const Board* board) {
    printf("----- Board state -----\n");
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (board->matrix[i][j].revealed) {
                if (board->matrix[i][j].value == MINE_VAL) {
                    printf("[*]");
                } else {
                    printf("[%d]", board->matrix[i][j].value);
                }
            } else if (board->matrix[i][j].flagged) {
                printf("[F]");
            } else {
                printf("[#]");
            }
        }
        printf("\n");
    }
}

int count_adjacent_mines(const Board* board, int row, int col) {
    int count = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int n_i = row + i;
            int n_j = col + j;

            if (n_i >= 0 && n_i < board->rows && n_j >= 0 && n_j < board->cols) {
                if (board->matrix[n_i][n_j].value == MINE_VAL) {
                    count++;
                }
            }
        }
    }

    return count;
}

void reveal_cell(Board* board, int row, int col) {
    if (row < 0 || row >= board->rows || col < 0 || col >= board->cols) {
        return;
    }
    
    if (board->matrix[row][col].revealed || board->matrix[row][col].flagged) {
        return;
    }

    if (board->matrix[row][col].value == MINE_VAL) {
        board->state = LOSS;
        board->matrix[row][col].exploded = true;
        for (int i = 0; i < board->rows; i++) {
            for (int j = 0; j < board->cols; j++) {
                if (board->matrix[i][j].value == MINE_VAL && !board->matrix[i][j].flagged) {
                    board->matrix[i][j].revealed = true;
                }
            }
        }
        return;
    }

    board->matrix[row][col].revealed = true;

    if (board->matrix[row][col].value == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                reveal_cell(board, row + i, col + j);
            }
        }
    }
}

void flag_cell(Board* board, int row, int col) {
    if (row < 0 || row >= board->rows || col < 0 || col >= board->cols) {
        return;
    }
    if (!board->matrix[row][col].revealed) {
        board->matrix[row][col].flagged = !board->matrix[row][col].flagged;
    }
}

void render_board(SDL_Renderer *renderer, Board *board, float mouse_x, float mouse_y) {
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            Cell* cell = &board->matrix[i][j];

            if (cell->revealed) {
                SDL_SetRenderDrawColor(renderer, 205, 205, 205, 255);
                if (cell->value == MINE_VAL) {
                    if (cell->exploded) {
                        SDL_SetRenderDrawColor(renderer, 230, 60, 60, 255);
                    } else {
                        SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
                    }
                }
                SDL_RenderFillRect(renderer, &cell->btn.rect);

                if (cell->value == MINE_VAL) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDLTest_DrawString(renderer, cell->btn.rect.x + 6.0f, cell->btn.rect.y + 6.0f, cell->label);
                } else if (cell->value > 0) {
                    switch (cell->value) {
                        case 1: SDL_SetRenderDrawColor(renderer, 0, 0, 240, 255); break;
                        case 2: SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); break;
                        case 3: SDL_SetRenderDrawColor(renderer, 220, 0, 0, 255); break;
                        case 4: SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255); break;
                        case 5: SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255); break;
                        case 6: SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255); break;
                        case 7: SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); break;
                        case 8: SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); break;
                    }
                    SDLTest_DrawString(renderer, cell->btn.rect.x + 6.0f, cell->btn.rect.y + 6.0f, cell->label);
                }
            } else {
                if (is_point_in_rect(mouse_x, mouse_y, &cell->btn.rect) && board->state == PLAYING) {
                    SDL_SetRenderDrawColor(renderer, 185, 185, 185, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
                }
                SDL_RenderFillRect(renderer, &cell->btn.rect);

                if (cell->flagged) {
                    SDL_SetRenderDrawColor(renderer, 220, 30, 30, 255);
                    SDLTest_DrawString(renderer, cell->btn.rect.x + 6.0f, cell->btn.rect.y + 6.0f, "F");
                }
            }
        }
    }

    int flags_placed = 0;
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (board->matrix[i][j].flagged) {
                flags_placed++;
            }
        }
    }

    char status_str[100];
    if (board->state == PLAYING) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        snprintf(status_str, sizeof(status_str), "Mines: %d | Flags: %d | [R] Restart", board->n_mines, flags_placed);
    } else if (board->state == LOSS) {
        SDL_SetRenderDrawColor(renderer, 220, 30, 30, 255);
        snprintf(status_str, sizeof(status_str), "GAME OVER! Press [R] to Restart");
    } else if (board->state == WON) {
        SDL_SetRenderDrawColor(renderer, 30, 180, 30, 255);
        snprintf(status_str, sizeof(status_str), "YOU WIN! Press [R] to play again");
    }

    SDLTest_DrawString(renderer, 20.0f, 470.0f, status_str);

    SDL_RenderPresent(renderer);
}

bool is_point_in_rect(float x, float y, const SDL_FRect* r) {
    return x >= r->x && x <= r->x + r->w && y >= r->y && y <= r->y + r->h;
}

Point get_current_point(const float x, const float y, const Board* board) {
    Point p = {
        .col = -1,
        .row = -1
    };

    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (is_point_in_rect(x, y, &board->matrix[i][j].btn.rect)) {
                p.row = i;
                p.col = j;
            }
        }
    }
    
    return p;
}

bool check_win_condition(const Board* board) {
    int unrevealed_count = 0;
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (!board->matrix[i][j].revealed) {
                unrevealed_count++;
            }
        }
    }
    return unrevealed_count == board->n_mines;
}

void restart_game(Board* board) {
    free_board(board);
    board->state = PLAYING;
    board->matrix = NULL;
    board->mine_coords = NULL;
    generate_random_mines(board);
    generate_board(board);
}
