#include <stdio.h>

#include "conway.h"

int main() {
    Life *life = new_life(40, 15);
    if (life)
        print_grid(life);

    for (int i = 0; i < 50; i++) {
        life->step(life);
        print_grid(life);
        printf("\n");
    }

    release_life(life);
    return 0;
}