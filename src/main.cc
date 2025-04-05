#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>


#include "../include/utils.h"
#include "../include/render.h"
#include "../include/control.h"

int main() {
    // Fix for WSL terminal
    setenv("TERM", "xterm-256color", 1);

    initscr();
    start_color();
    init_colors();
    
    // initalsasi Audio
    AudioState audio = {0};
    pthread_t audio_tid;
    bool audio_enabled = false;
    if(audio_init(&audio) == 0) {
        if(LoadWav("../audio/bgm.wav", &audio.bgm.data, &audio.bgm.samples) &&
           LoadWav("../audio/eat.wav", &audio.sfx_eat.data, &audio.sfx_eat.samples)) 
        {
            pthread_create(&audio_tid, NULL, audio_thread, &audio);
            audio_enabled = true;
        }
        else {
            fprintf(stderr, "Failed to load audio files\n");
            snd_pcm_close(audio.handle);
        }
    }
    else {
        fprintf(stderr, "Audio system disabled\n");
    }
    

    // Show title screen first
    show_title_screen();
    
    // Title screen input handling
    int title_choice = 0;
    while (title_choice != '1' && title_choice != '3') {
        title_choice = getch();
        
        if (title_choice == '2') {
            // Show controls screen
            clear();
            mvprintw(5, WIDTH/2-10, "CONTROLS");
            mvprintw(7, WIDTH/2-15, "WASD or Arrow Keys - Move");
            mvprintw(8, WIDTH/2-15, "X - Quit Game");
            mvprintw(10, WIDTH/2-15, "Press any key to return");
            refresh();
            getch();
            show_title_screen();
        }
    }
    
    if (title_choice == '3') {
        endwin();
        return 0;
    }
    if(audio_enabled) {
        audio.running = false;
        pthread_join(audio_tid, NULL);
        snd_pcm_drain(audio.handle);  // Tunggu sampai audio selesai
        snd_pcm_close(audio.handle);
        free(audio.bgm.data);
        free(audio.sfx_eat.data);
    }

    // Original game loop
    GameState game;
    char play_again;

    do {
        // Game setup
        clear();
        noecho();
        cbreak();
        curs_set(0);
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);  // Non-blocking input during game

        srand(time(0));
        setup_game(&game);

        // Main game loop
        while (!game.game_over) {
            draw_game(&game);
            process_input(&game);
            update_game(&game);
            // trigger saat ular makan
            if(game.ate_food){
              play_eat_sfx(&audio);
            }
            usleep(INITIAL_SPEED - (game.score * 100));
        }

        // Game over screen
        show_game_over_screen(game.score);

        // Get user input for play again
        timeout(-1);  // Blocking input for this
        play_again = getch();

    } while (play_again == 'Y' || play_again == 'y');

    endwin();
    return 0;
}
