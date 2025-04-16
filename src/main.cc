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

    // Game loop variables
    GameState game;
    char play_again;

    do {
        // Show title screen first
        show_title_screen();

        // Title screen input handling
        int title_choice;
        bool game_started = false;
        bool quit_program = false;

        while (!game_started && !quit_program) {
            title_choice = getch();

            switch (title_choice) {
                case '1': // Start Game
                    game_started = true;
                    break;
                    
                case '2': // Controls
                    show_controls_screen();
                    show_title_screen();
                    break;
                    
                case '3': // Highscores
                    show_highscore_screen();
                    show_title_screen();
                    break;
                    
                case '4': // Quit
                    quit_program = true;
                    break;
                    
                default:
                    // Ignore other inputs
                    break;
            }
        }
        if (quit_program) {
            break;
        }

        // Game setup
        clear();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);

        srand(time(0));
        setup_game(&game);

        // Main game loop
        while (!game.game_over) {
            process_input(&game);
            update_game(&game);
            draw_game(&game);
            
            int current_speed = INITIAL_SPEED - (game.score * SPEED_INCREMENT);
            if(current_speed < MIN_SPEED) {
                current_speed = MIN_SPEED;
            }
            usleep(current_speed);
        }

        // Save highscore and show game over
        save_highscore(game.score);
        show_game_over_screen(game.score);

        // Play again prompt
        nodelay(stdscr, FALSE);
        play_again = getch();

    } while (play_again == 'Y' || play_again == 'y');

    endwin();
    return 0;
}
