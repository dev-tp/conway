#ifndef conway_h
#define conway_h

#include <stdlib.h>
#include <stdio.h>

#define true 1
#define false 0
#define swap(type, a, b) { type temp = a; a = b; b = temp; }

typedef int bool;

bool **new_grid(int width, int height);
void release_grid(bool **grid, int width, int height);
void print_grid(bool **grid, int width, int heigth);

typedef struct Field {
    bool **grid;
    int width, height;
} Field;

Field *new_field(int width, int height);
void release_field(Field *field);
bool alive(Field *field, int x, int y);
bool next(Field *field, int x, int y);

typedef struct Life {
    Field *first_field, *second_field;
    int width, height;
} Life;

Life *new_life(int width, int height);
void release_life(Life *life);
void step(Life *life);

#endif