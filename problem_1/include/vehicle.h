#ifndef VEHICLE_H
#define VEHICLE_H

#include "point.h"

typedef struct vehicle_t {
  Point upper;
  Point down;
} Vehicle;

Vehicle vehicle_from_stdin(int rows, int cols, Point down);
Vehicle vehicle_random(int rows, int cols, Point down);
void vehicle_display(FILE* stream, const Vehicle* vehicle);
bool vehicle_equals(const Vehicle* lhs, const Vehicle* rhs);
int random_number(int min, int max);

#endif