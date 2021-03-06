#ifndef POINT_H
#define POINT_H
#include <stdbool.h>
#include <stdio.h>

typedef struct point_t {
  int x;
  int y;
} Point;

bool point_equals(const Point* lhs, const Point* rhs);

Point point_add(const Point* lhs, const Point* rhs);

void point_display(FILE* stream, const Point* point);

#endif