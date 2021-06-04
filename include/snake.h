#ifndef SNAKE_H__
#define SNAKE_H__

#include "../common/common.h"

typedef struct cell {
    Point pos;
    struct cell *suiv;
} Cell;

typedef struct snake {
    enum Direction dir;
    Cell *head;
    Cell *tail;
} Snake;

Cell *create_cell(Point pos);
void destroy_cell(Cell *cell);

Snake *create_snake();

Snake *init_snake(Point pos);
void destroy_snake(Snake *snake);

void add_cell(Snake *snake, Cell *cell);
void destroy_cells(Cell *cells);

void move_snake(Snake *snake, enum Direction dir);

#endif