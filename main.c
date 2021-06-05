#include <ncurses.h>

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <unistd.h>
#endif

void sleep_ms(int milliseconds) {
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
        sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

#include "include/game.h"

int main() {
    enum Direction dir = RIGHT;

    Game *game = init_game(20);

    if (!game) return 1;

    WINDOW *w = initscr();
    cbreak();
    nodelay(w, TRUE);

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

        sleep_ms(250);
    }

    printw("\n\tGame Over ...");

    getch();
    endwin();

    destroy_game(game);
    return 0;
}
