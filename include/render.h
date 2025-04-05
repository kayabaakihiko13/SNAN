#ifndef RENDER_H
#define RENDER_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>

#include "./utils.h"

// Color Macros
#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_YELLOW 3


// initial functional
inline void init_colors();

inline void setup_game(GameState *game);

inline void draw_game(GameState *game);

inline void show_game_over_screen(int score);

inline void show_title_screen();

void show_game_over_screen(int score) {
    // Switch to blocking input for the menu
    nocbreak();
    echo();
    curs_set(1);

    clear();
    
    // Game Over text (Red)
    attron(A_BOLD | COLOR_PAIR(COLOR_RED));
    mvprintw(HEIGHT/2 - 2, WIDTH/2 - 5, "GAME OVER");
    attroff(A_BOLD | COLOR_PAIR(COLOR_RED));
    
    // Score text (Yellow)
    attron(COLOR_PAIR(COLOR_GREEN));
    mvprintw(HEIGHT/2, WIDTH/2 - 8, "Final Score: %d", score);
    attroff(COLOR_PAIR(COLOR_YELLOW));
    
    // Play again prompt (Yellow)
    attron(COLOR_PAIR(COLOR_YELLOW));
    mvprintw(HEIGHT/2 + 2, WIDTH/2 - 10, "Play Again? (Y/N): ");
    attroff(COLOR_PAIR(COLOR_YELLOW));
    
    refresh();
}


void init_colors(){
  start_color();
  init_pair(COLOR_RED,COLOR_RED,COLOR_BLACK);
  init_pair(COLOR_GREEN,COLOR_GREEN,COLOR_BLACK);
  init_pair(COLOR_YELLOW,COLOR_YELLOW,COLOR_BLACK);
}


void setup_game(GameState *game){

  // this setup initial value
  game->game_over = 0;
  game->ate_food = false;
  game->direction = STOP;
  game->head.x = WIDTH /2;
  game->head.y = HEIGHT /2;
  game->fruit.x = (rand() % (WIDTH-2)) + 1;
  game->fruit.y = (rand()% (HEIGHT-2)) + 1;
  game->score = 0;
  game->tail_length = 0;
}

void show_title_screen() {
    clear();
    
    // Snake ASCII Art
    attron(COLOR_PAIR(COLOR_GREEN) | A_BOLD);
    mvprintw(5, WIDTH/2-10, "    ____  _   _    _    _   _ ");
    mvprintw(6, WIDTH/2-10, "   / ___|| \\ | |  / \\  | \\ | |");
    mvprintw(7, WIDTH/2-10, "   \\___ \\|  \\| | / _ \\ |  \\| |");
    mvprintw(8, WIDTH/2-10, "    ___) | |\\  |/ ___ \\| |\\  |");
    mvprintw(9, WIDTH/2-10, "   |____/|_| \\_/_/   \\_\\_| \\_|");
    attroff(COLOR_PAIR(COLOR_GREEN) | A_BOLD);

    // Game Title
    attron(COLOR_PAIR(COLOR_RED) | A_BOLD);
    mvprintw(12, WIDTH/2-5, "SNAKE GAME");
    attroff(COLOR_PAIR(COLOR_RED) | A_BOLD);

    // Menu Options
    attron(COLOR_PAIR(COLOR_YELLOW));
    mvprintw(15, WIDTH/2-8, "1. Start Game");
    mvprintw(16, WIDTH/2-8, "2. Controls");
    mvprintw(17, WIDTH/2-8, "3. Quit");
    attroff(COLOR_PAIR(COLOR_YELLOW));

    refresh();
}


void draw_game(GameState *game) {
    clear();
    
    // Draw borders
    attron(COLOR_PAIR(COLOR_GREEN));
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1) {
                mvaddch(i, j, '|');
            }
        }
    }
    attroff(COLOR_PAIR(COLOR_GREEN));
    
    // Draw snake head
    attron(COLOR_PAIR(COLOR_RED) | A_BOLD);
    mvaddch(game->head.y, game->head.x, 'O');
    attroff(COLOR_PAIR(COLOR_RED) | A_BOLD);
    
    // Draw snake tail
    for (int i = 0; i < game->tail_length; i++) {
        mvaddch(game->tail[i].y, game->tail[i].x, 'o');
    }
    
    // Draw fruit
    attron(COLOR_PAIR(COLOR_YELLOW));
    mvaddch(game->fruit.y, game->fruit.x, '@');
    attroff(COLOR_PAIR(COLOR_YELLOW));
    
    // Draw score
    mvprintw(HEIGHT, 0, "Score: %d", game->score);
    mvprintw(HEIGHT+1, 0, "Press 'x' to quit");
    
    refresh();
}
#endif
