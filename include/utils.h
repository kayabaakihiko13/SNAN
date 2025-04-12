#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>

#define WIDTH 60
#define HEIGHT 20
#define MAX_TAIL 100
#define FRUIT_VALUE 10
#define INITIAL_SPEED 100000
#define SPEED_INCREMENT 200
#define MIN_SPEED 2000
#define HS_FILE ".snakehs"
#define MAX_HS_ENTRIES 10

typedef enum {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
} Direction;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position head;
    Position tail[MAX_TAIL];
    int tail_length;
    Position fruit;
    Direction direction;
    int score;
    bool ate_food;
    bool game_over;
} GameState;

typedef struct {
    int score;
    char name[4];  // char array size 3
} HighScore;


#endif
