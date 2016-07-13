#ifndef conway_h
#define conway_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
#define swap(type, a, b) { type temp = a; a = b; b = temp; }

#ifdef _WIN32
    #define clear "cls"
#else
    #define clear "clear"
#endif

typedef int bool;

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

bool **new_grid(int width, int height);
void release_grid(bool **grid, int width, int height);
void print_grid(Life *life);

#endif