#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#include "./Point.h"

Point::Point(int maxX, int maxY) {
  this->x = rand() % maxX;
  this->y = rand() % maxY;
  // TODO: We can make step boundaries random as well, so point will have random step range.
  this->stepX = (2 * (rand() % 2)) - 1;
  this->stepY = (2 * (rand() % 2)) - 1;
}

void Point::updatePosition() {
  this->x += this->stepX;
  this->y += this->stepY;
}
