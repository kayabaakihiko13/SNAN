#ifndef UTILS_H

#define UTILS_H 

// initial value for game
#define WIDTH 60
#define HEIGHT 20
#define MAX_TAIL 100
#define FRUIT_VALUE 1
#define INITIAL_SPEED 100000


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
    int tail_length;
    Position fruit;
    Direction direction;
    int score;
    int game_over;
    bool ate_food;
} GameState;


#endif // !DEBUG
