#include <ncurses.h>

#include "include/game.h"

int main() {
    enum Direction dir;

    Game *game = init_game(10);

    if (!game) return 1;

    initscr();

    if (!has_colors()) {
        printw("\n\t Terminal does not support colors !");
        getch();
        return -1;
    }

    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    game->map[2][3] = AppleCell;
    game->map[4][6] = AppleCell;

    game->map[1][3] = AppleCell;
    game->map[3][6] = AppleCell;

    game->map[1][8] = AppleCell;


    game->map[6][6] = AppleCell;
    game->map[5][8] = AppleCell;
    game->map[6][5] = AppleCell;

    int key = 0;

    while (key != 27) {
        clear();

        show(game);

        dir = None;

        key = getch();

        if (key == S_KEY_UP)
            dir = UP;

        else if (key == S_KEY_DOWN)
            dir = DOWN;

        else if (key == S_KEY_RIGHT)
            dir = RIGHT;

        else if (key == S_KEY_LEFT)
            dir = LEFT;

        if (!update(game, dir)) break;

        refresh();
    }

    printw("\n\tGame Over ...");

    getch();
    endwin();

    destroy_game(game);
    return 0;
}