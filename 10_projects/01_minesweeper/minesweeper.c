#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

#define GAME_WITDH 600
#define GAME_HEIGTH 600

#define MINE 10
#define COLS 10
#define ROWS 10
#define MINES 6

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Game;

typedef struct {
    int cols;
    int rows;
    int n_mines;
    int** mines;
    int** matrix;
} Board;

void sdl_quit(Game* game);
int sdl_init(Game* game);
void generate_random_mines(Board* board);
void generate_board(Board* board);
bool is_pos_valid(int** matrix, int mines, int row, int col);
void free_matrix(int **matrix, int mines);
void free_board(Board* board);
void print_matrix(int** matrix, int rows, int cols);
int count_mines(Board board, int row, int col);

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
        .mines = NULL
    };
    
    generate_random_mines(&board);
    generate_board(&board);
    print_matrix(board.matrix, board.rows, board.cols);

    sdl_init(&game);

    SDL_Event event;
    bool running = false;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }



            SDL_Delay(16);
        }
        
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

    int** matrix = (int**) malloc(sizeof(int*) * mines);
    for (size_t i = 0; i < mines; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * 2);
    }
    
    for (int i = 0; i < mines; i++) {
        int col = rand() % cols;
        int row = rand() % rows;

        if (is_pos_valid(matrix, mines, row, col)) {
            matrix[i][0] = row;
            matrix[i][1] = col;
        } else {
            i--;
        }
    }
}

void generate_board(Board *board) {
    board->matrix = (int**) malloc(sizeof(int*) * board->rows);

    for (int i = 0; i < board->rows; i++) {
        board->matrix[i] = (int*) calloc(board->cols, sizeof(int));
    }
    
    for (int i = 0; i < board->n_mines; i++) {
        board->matrix[board->mines[i][0]][board->mines[i][1]] = MINE;
    }

    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (board->matrix[i][j] != MINE) {
                board->matrix[i][j] = count_mines(*board, i, j);
            }
        }
    }
}

bool is_pos_valid(int** matrix, int mines, int row, int col) {
    for (size_t i = 0; i < mines; i++) {
        if (matrix[i][0] == row && matrix[i][1] == col) {
            return false;
        }
    }
    return true;    
}

void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void free_board(Board *board) {
    free_matrix(board->matrix, board->rows);
    free_matrix(board->mines, board->n_mines);
}

void print_matrix(int** matrix, int rows, int cols) {
    printf("-----printing matrix-----\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("[%d]", matrix[i][j]);
            fflush(stdout); 
        }
        printf("\n");
    }
}

int count_mines(Board board, int row, int col) {
    int count = 0;
    
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) continue;
            int n_i = row + i;
            int n_j = col + i;

            if (n_i == -1 || n_i == board.rows || n_j == -1 || n_j == board.cols) {
                continue;
            }

            if (board.matrix[n_i][n_j] == MINE) {
                count++;
            }
        }
    }

    return count;
}

// row  col
// [10][40]
// [32][42]
// [65][32]
// [43][23]