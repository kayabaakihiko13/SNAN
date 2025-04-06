#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>
#include <sys/time.h>
#include <time.h>


#include "../include/utils.h"
#include "../include/render.h"
#include "../include/control.h"

int main() {
    // Fix for WSL terminal
    setenv("TERM", "xterm-256color", 1);

    initscr();
    start_color();
    init_colors();

    // Show title screen first
    show_title_screen();

    // Title screen input handling
    int title_choice = 0;
    while (title_choice != '1' && title_choice != '3') {
        title_choice = getch();
        if (title_choice == '2') {
            clear();
            const char* controls[] = {
                "CONTROLS",
                "WASD or Arrow Keys - Move",
                "X - Quit Game",
                "Press any key to return"
            };
            
            for(int i = 0; i < 4; i++) {
                mvaddstr(5 + i*2, WIDTH/2 - 15, controls[i]);
            }
            refresh();
            
            nodelay(stdscr, FALSE);  // Mode blocking input
            getch();
            nodelay(stdscr, TRUE);
            show_title_screen();
        }
    }

    if (title_choice == '3') {
        endwin();
        return 0;
    }

    // Game loop
    GameState game;
    char play_again;

    do {
        // Game setup
        clear();
        noecho();
        cbreak();
        curs_set(0);
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);

        srand(time(0));
        setup_game(&game);

        // Main game loop
        while (!game.game_over) {
            draw_game(&game);
            process_input(&game);
            update_game(&game);
            int current_speed = INITIAL_SPEED -(game.score * SPEED_INCREMENT); 
            if(current_speed <MIN_SPEED){
              current_speed = MIN_SPEED;
            }
            usleep(current_speed);
        }

        // Game over screen
        show_game_over_screen(game.score);

        // Play again prompt
        timeout(-1);
        play_again = getch();

    } while (play_again == 'Y' || play_again == 'y');

    endwin();
    return 0;

}
