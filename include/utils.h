#ifndef UTILS_H

#define UTILS_H 

// initial value for game
#define WIDTH 60
#define HEIGHT 20
#define MAX_TAIL 100
#define FRUIT_VALUE 10
#define INITIAL_SPEED 100000
#define SPEED_INCREMENT 200
#define MIN_SPEED 2000

typedef enum{
  STOP=0,
  LEFT,
  RIGHT,
  UP,
  DOWN
} Direction;

typedef struct{
  int x;
  int y;
} Position;

typedef struct {
    Position head;
    Position tail[MAX_TAIL];
    Position fruit;
    Direction direction;
    int tail_length;
    int score;
    int game_over;
} GameState;


#endif // !DEBUG
