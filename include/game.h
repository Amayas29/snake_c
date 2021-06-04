#ifndef MAP_H__
#define MAP_H__

#include "../common/common.h"
#include "apple.h"
#include "snake.h"

#define S_KEY_UP 122
#define S_KEY_DOWN 115
#define S_KEY_RIGHT 100
#define S_KEY_LEFT 113

enum CellType {
    EmptyCell,
    AppleCell,
    SnakeCell,
    WallCell
};

typedef struct {
    Snake *snake;
    Apple *apple;
    int length;
    enum CellType **map;
} Game;

Game *init_game(int length);
void destroy_game(Game *game);
void show(Game *game);

int update(Game *game, enum Direction dir);

#endif