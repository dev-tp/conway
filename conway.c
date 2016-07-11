#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "conway.h"

void set(Field *field, int x, int y, bool value) {
    field->grid[y][x] = value;
}

bool alive(Field *field, int x, int y) {
    x += field->width;
    x %= field->width;
    y += field->height;
    y %= field->height;
    return field->grid[y][x];
}

bool next(Field *field, int x, int y) {
    int alive = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if ((i != 0 || j != 0) && field->alive(field, x, y))
                alive++;
    return alive == 3 || alive == 2 && field->alive(field, x, y);
}

void step(Life *life) {
    for (int y = 0; y < life->height; y++)
        for (int x = 0; x < life->width; x++)
            life->second_field->set(life->second_field, x, y,
                life->first_field->next(life->first_field, x, y));

    Field *temp = life->first_field;
    life->first_field = life->second_field;
    life->second_field = temp;
}

Field *new_field(int width, int height) {
    Field *field = malloc(sizeof(Field));
    field->width = width;
    field->height = height;
    field->alive = alive;
    field->next = next;
    field->set = set;

    bool **grid = malloc(sizeof(bool *) * width);
    for (int i = 0; i < height; i++)
        grid[i] = malloc(sizeof(bool) * height);
    field->grid = grid;

    return field;
}

void release_field(Field *field) {
    if (field) {
        if (field->grid) {
            for (int i = 0; i < field->height; i++)
                free(field->grid[i]);
            free(field->grid);
        }
        free(field);
    }
}

Life *new_life(int width, int height) {
    Life *life = malloc(sizeof(Life));
    life->width = width;
    life->height = height;
    life->first_field = new_field(width, height);
    life->second_field = new_field(width, height);
    life->step = step;

    srand((unsigned int) time(NULL));

    for (int i = 0; i < (width * height / 4); i++) {
        int x = rand() % width;
        int y = rand() % height;
        life->first_field->set(life->first_field, x, y, true);
    }

    return life;
}

void release_life(Life *life) {
    if (life) {
        if (life->first_field)
            release_field(life->first_field);
        if (life->second_field)
            release_field(life->second_field);
        free(life);
    }
}

void print_grid(Life *life) {
    for (int y = 0; y < life->height; y++) {
        for (int x = 0; x < life->width; x++)
            printf("%c", life->first_field->alive(life->first_field, x, y) ? '*' : ' ');
        printf("\n");
    }
}