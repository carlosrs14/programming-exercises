#include <SDL3/SDL.h>
#include <SDL3/SDL_test_font.h>
#include "../include/minesweeper.h"

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

