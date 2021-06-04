#ifndef COMMON_H__
#define COMMON_H__

typedef struct {
    int x;
    int y;
} Point;

enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    None
};

#endif