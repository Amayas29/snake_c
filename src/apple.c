#include "../include/apple.h"
#include <stdio.h>
#include <stdlib.h>

Point generate_apple(int limit) {
    Point pos = { rand() % limit, rand() % limit };
    return pos;
}
