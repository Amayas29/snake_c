#include "../include/game.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN_LENGTH 5

Cell *get(Snake *snake, int x, int y) {
    for (Cell *current = snake->head; current; current = current->suiv) {
        if (current->pos.x == x && current->pos.y == y) return current;
    }

    return NULL;
}

Game *init_game(int length) {
    if (length < MIN_LENGTH) return NULL;

    Game *game = malloc(sizeof(Game));

    if (!game) {
        fprintf(stderr, "Failed to allocate the game\n");
        return NULL;
    }

    game->length = length;
    game->map = malloc(sizeof(enum CellType *) * length);

    if (!game->map) {
        fprintf(stderr, "Failed to allocate the map\n");
        free(game);
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        game->map[i] = malloc(sizeof(enum CellType) * length);

        if (!game->map[i]) {
            for (int j = 0; j < i; j++)
                free(game->map[j]);

            fprintf(stderr, "Failed to allocate the map\n");
            free(game);
            return NULL;
        }

        for (int j = 0; j < length; j++)
            game->map[i][j] = EmptyCell;
    }

    game->apple = NULL;  // TODO

    Point pos = {length / 2, length / 2};
    game->snake = init_snake(pos);

    game->map[game->snake->head->pos.y][game->snake->head->pos.x] = SnakeCell;

    return game;
}

void destroy_game(Game *game) {
    if (!game) return;

    for (int i = 0; i < game->length; i++)
        free(game->map[i]);

    free(game->map);
    destroy_snake(game->snake);
    // TODO

    free(game);
}

void show(Game *game) {
    if (!game) return;

    Point head = game->snake->head->pos;

    printw("\n\t+");

    for (int j = 0; j < game->length; j++) {
        printw("---+");
        game->map[0][j] = WallCell;
        game->map[game->length - 1][j] = WallCell;
        game->map[j][0] = WallCell;
        game->map[j][game->length - 1] = WallCell;
    }

    printw("\n");

    for (int i = 0; i < game->length; i++) {
        printw("\t|");

        for (int j = 0; j < game->length; j++) {
            printw(" ");

            if (game->map[i][j] == EmptyCell)
                printw(" ");

            else if (game->map[i][j] == AppleCell) {
                attron(COLOR_PAIR(1));
                printw("a");
                attroff(COLOR_PAIR(1));

            }

            else if (game->map[i][j] == SnakeCell) {
                attron(COLOR_PAIR(2));

                enum Direction dir = get(game->snake, j, i)->dir;
                // if (j == head.x && i == head.y) {
                if (dir == UP)
                    printw("^");

                else if (dir == DOWN)
                    printw("V");

                else if (dir == RIGHT)
                    printw(">");

                else if (dir == LEFT)
                    printw("<");

                // } else
                //     printw("o");

                attroff(COLOR_PAIR(2));

            }

            else {
                attron(A_REVERSE);
                printw(" ");
                attroff(A_REVERSE);
            }

            printw(" |");
        }

        printw("\n\t+");
        for (int j = 0; j < game->length; j++)
            printw("---+");

        printw("\n");
    }
}

static int collid_wall(Snake *snake, int length) {
    Point pos = snake->head->pos;

    return (pos.x == 0 || pos.x == length - 1 || pos.y == 0 || pos.y == length - 1);
}

int update(Game *game, enum Direction dir) {
    if (!game || !game->snake || !game->snake->head) return 0;

    if (collid_wall(game->snake, game->length)) return 0;

    Point old_pos = game->snake->tail->pos;

    int move = move_snake(game->snake, dir);

    if (!move) return 1;

    game->map[old_pos.y][old_pos.x] = EmptyCell;

    Point new_pos = game->snake->head->pos;

    enum CellType type = game->map[new_pos.y][new_pos.x];

    game->map[new_pos.y][new_pos.x] = SnakeCell;

    if (collid_wall(game->snake, game->length)) return 0;

    if (type == WallCell) return 0;

    if (type == SnakeCell) return 0;

    if (type == AppleCell) {
        Point tail_pos = game->snake->tail->pos;

        Point new = {tail_pos.x, tail_pos.y};

        enum Direction t_dir = game->snake->tail->dir;

        if (t_dir == UP && tail_pos.y != game->length - 1 && game->map[tail_pos.y + 1][tail_pos.x] == EmptyCell)
            new.y += 1;

        else if (t_dir == DOWN && tail_pos.y != 0 && game->map[tail_pos.y - 1][tail_pos.x] == EmptyCell)
            new.y -= 1;

        else if (t_dir == RIGHT && tail_pos.x != 0 && game->map[tail_pos.y][tail_pos.x - 1] == EmptyCell)
            new.x -= 1;

        else if (t_dir == LEFT && tail_pos.x != game->length - 1 && game->map[tail_pos.y][tail_pos.x + 1] == EmptyCell)
            new.x += 1;

        else
            return 0;

        add_cell(game->snake, create_cell(new));
        game->map[new.y][new.x] = SnakeCell;
    }

    return 1;
}