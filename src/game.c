#include "../include/game.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN_LENGTH 5

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

    game->map[game->snake->head->pos.x][game->snake->head->pos.y] = SnakeCell;

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

                if (i == head.x && j == head.y) {
                    if (game->snake->dir == UP)
                        printw("^");

                    else if (game->snake->dir == DOWN)
                        printw("V");

                    else if (game->snake->dir == RIGHT)
                        printw(">");

                    else if (game->snake->dir == LEFT)
                        printw("<");

                } else
                    printw("o");

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