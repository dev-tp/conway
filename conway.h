#ifndef CONWAY_H
#define CONWAY_H

#define true 1
#define false 0

typedef int bool;

typedef struct Field {
    bool **grid;
    int width, height;
    bool (*alive)(struct Field *field, int x, int y);
    void (*set)(struct Field *field, int x, int y, bool value);
    bool (*next)(struct Field *field, int x, int y);
} Field;

Field *new_field(int width, int height);
void release_field(Field *field);
void set(Field *field, int x, int y, bool value);
bool alive(Field *field, int x, int y);
bool next(Field *field, int x, int y);

typedef struct Life {
    Field *first_field, *second_field;
    int width, height;
    void (*step)(struct Life *life);
} Life;

Life *new_life(int width, int height);
void release_life(Life *life);
void step(Life *life);

void print_grid(Life *life);

#endif
