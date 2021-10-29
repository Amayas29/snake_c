#include <ncurses.h>

#include "common/sleep.h"
#include "include/game.h"

int main() {
    WINDOW* w = initscr();
    cbreak();
    nodelay(w, TRUE);

    if (!has_colors()) {
        printw("\n\t Terminal does not support colors !");
        getch();
        return -1;
    }

    enum Direction dir = RIGHT;

    Game* game = init_game(20);

    if (!game)
        return 1;

    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    int key = 0;

    while (key != 27) {
        clear();

        show(game);

        key = getch();

        if (key == S_KEY_UP)
            dir = UP;

        else if (key == S_KEY_DOWN)
            dir = DOWN;

        else if (key == S_KEY_RIGHT)
            dir = RIGHT;

        else if (key == S_KEY_LEFT)
            dir = LEFT;

        if (!update(game, dir))
            break;

        refresh();

        sleep_ms(240);
    }

    printw("\n\tGame Over ...");
    printw("\n\n\tPress a key to exit");
    refresh();

    getchar();
    endwin();

    destroy_game(game);
    return 0;
}
