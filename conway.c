#include "conway.h"

bool **new_grid(int width, int height) {
    bool **grid = malloc(sizeof(bool *) * width);
    for (int i = 0; i < width; i++)
        grid[i] = malloc(sizeof(bool) * height);

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            grid[i][j] = false;

    return grid;
}

void release_grid(bool **grid, int width, int height) {
    if (grid) {
        for (int i = 0; i < width; i++)
            free(grid[i]);
        free(grid);
    }
}

void print_grid(bool **grid, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++)
            printf("%c", grid[i][j] ? '*' : ' ');
        printf("\n");
    }
}

Field *new_field(int width, int height) {
    Field *field = malloc(sizeof(Field));
    field->width = width;
    field->height = height;
    field->grid = new_grid(width, height);
    return field;
}

void release_field(Field *field) {
    if (field) {
        if (field->grid)
            release_grid(field->grid, field->width, field->height);
        free(field);
    }
}

bool alive(Field *field, int x, int y) {
    x += field->width;
    x %= field->width;
    y += field->height;
    y %= field->height;
    return field->grid[x][y];
}

bool next(Field *field, int x, int y) {
    int life = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if ((i != 0 || j != 0) && alive(field, x + i, y + j))
                ++life;
    return life == 3 || (life == 2 && alive(field, x, y));
}

Life *new_life(int width, int height) {
    Life *life = malloc(sizeof(Life));
    life->first_field = new_field(width, height);
    life->second_field = new_field(width, height);
    life->width = width;
    life->height = height;

    for (int i = 0; i < (width * height / 4); i++) {
        int x = arc4random_uniform(width), y = arc4random_uniform(height);
        life->first_field->grid[x][y] = true;
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

void step(Life *life) {
    for (int i = 0; i < life->width; i++)
        for (int j = 0; j < life->height; j++)
            life->second_field->grid[i][j] = next(life->first_field, i, j);
    swap(Field *, life->first_field, life->second_field);
}