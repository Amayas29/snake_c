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

    int i = 3;
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

        Point pos = {2, i};
        add_cell(game->snake, create_cell(pos));

        i++;
        // if (!update(game, dir)) return;

        // if (snake_collid(game))
        //     break;

        // if (eat_apple(game))
        //     snake_grow(game->snake);

        refresh();
    }

    endwin();

    destroy_game(game);
    return 0;
}