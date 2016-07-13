#include "conway.h"

void msleep(unsigned long seconds) {
    unsigned long retention_time = time(0) + seconds;
    while (time(0) < retention_time);
}

int main(int argc, char *argv[]) {
    Life *life = new_life(15, 40);
    for (int i = 0; i < 10; i++) {
        step(life);
        print_grid(life);
        msleep(1);
        system(clear);
    }
    release_life(life);
    return 0;
}