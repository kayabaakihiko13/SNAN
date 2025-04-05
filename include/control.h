#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>

#include "./utils.h"

inline void process_input(GameState *game);
inline void update_game(GameState *game);


void process_input(GameState *game){

  int ch = getch();
  switch (ch) {
    case KEY_LEFT: 
      case 'a' : 
        if(game->direction != RIGHT) game->direction = LEFT; 
        break;
    case KEY_RIGHT: 
      case 'd': 
        if(game->direction !=LEFT) game->direction = RIGHT;
        break;
    case KEY_UP: 
      case 'w':
        if(game->direction !=DOWN) game->direction = UP;
        break;

    case KEY_DOWN:
      case 's':
        if(game->direction !=UP) game->direction = DOWN;
        break;
  }
}

void update_game(GameState *game) {
    game->ate_food = false;
    // Move tail
    Position prev = game->tail[0];
    game->tail[0] = game->head;

    for (int i = 1; i < game->tail_length; i++) {
        Position current = game->tail[i];
        game->tail[i] = prev;
        prev = current;
    }

    // Move head
    switch (game->direction) {
        case LEFT:  game->head.x--; break;
        case RIGHT: game->head.x++; break;
        case UP:    game->head.y--; break;
        case DOWN:  game->head.y++; break;
        default: break;
    }

    // Check collisions
    if (game->head.x <= 0 || game->head.x >= WIDTH-1 ||
        game->head.y <= 0 || game->head.y >= HEIGHT-1) {
        game->game_over = 1;
    }

    for (int i = 0; i < game->tail_length; i++) {
        if (game->head.x == game->tail[i].x && game->head.y == game->tail[i].y) {
            game->game_over = 1;
        }
    }

    // Check fruit collision
    if (game->head.x == game->fruit.x && game->head.y == game->fruit.y) {
        game->score += FRUIT_VALUE;
        game->ate_food = true;
        game->fruit.x = (rand() % (WIDTH-2)) + 1;
        game->fruit.y = (rand() % (HEIGHT-2)) + 1;
        if (game->tail_length < MAX_TAIL) {
            game->tail_length++;
        }
    }
}


#endif // !DEBUG
