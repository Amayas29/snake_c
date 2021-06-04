#include "../include/snake.h"

#include <stdio.h>
#include <stdlib.h>

Snake *init_snake(Point pos) {
    Snake *snake = create_snake();
    add_cell(snake, create_cell(pos));

    return snake;
}

Cell *create_cell(Point pos) {
    Cell *cell = malloc(sizeof(Cell));

    if (!cell) {
        fprintf(stderr, "Failed to allocate the cell\n");
        return NULL;
    }

    cell->pos = pos;

    cell->suiv = NULL;
    return cell;
}

void destroy_cell(Cell *cell) {
    free(cell);
}

Snake *create_snake() {
    Snake *snake = malloc(sizeof(Snake));

    if (!snake) {
        fprintf(stderr, "Failed to allocate the snake\n");
        return NULL;
    }

    snake->head = NULL;
    snake->tail = NULL;

    snake->dir = RIGHT;

    return snake;
}

void destroy_snake(Snake *snake) {
    if (!snake) return;

    destroy_cells(snake->head);
    free(snake);
}

void add_cell(Snake *snake, Cell *cell) {
    if (!snake || !cell) return;

    cell->suiv = NULL;

    if (!snake->head)
        snake->head = cell;

    if (snake->tail)
        snake->tail->suiv = cell;

    snake->tail = cell;
}

void destroy_cells(Cell *cells) {
    Cell *tmp = NULL;

    while (cells) {
        tmp = cells->suiv;
        destroy_cell(cells);
        cells = tmp;
    }
}

static int inverse_direction(enum Direction dir1, enum Direction dir2) {
    if ((dir1 == UP && dir2 == DOWN) || (dir2 == UP && dir1 == DOWN)) return 1;
    if ((dir1 == RIGHT && dir2 == LEFT) || (dir2 == RIGHT && dir1 == LEFT)) return 1;

    return 0;
}

static void move_cell(Cell *cell, enum Direction dir) {
    if (dir == UP)
        cell->pos.y += 1;

    else if (dir == DOWN)
        cell->pos.y -= 1;

    else if (dir == RIGHT)
        cell->pos.x += 1;

    else if (dir == LEFT)
        cell->pos.x -= 1;
}

void move_snake(Snake *snake, enum Direction dir) {
    if (!snake || !snake->head) return;

    if (inverse_direction(dir, snake->dir)) return;

    if (dir == None) return;

    Point old_pos = snake->head->pos;

    for (Cell *current = snake->head; current; current = current->suiv) {
        Point tmp = current->pos;
        current->pos = old_pos;
        old_pos = tmp;
    }

    move_cell(snake->head, dir);
}
