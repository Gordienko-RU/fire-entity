#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#include "./Point.h"

Point::Point(int maxX, int maxY) {
  this->x = rand() % maxX;
  this->y = rand() % maxY;
  this->stepX = (4 * (rand() % 2)) - 2;
  this->stepY = (4 * (rand() % 2)) - 2;
}

void Point::updatePosition() {
  this->x += this->stepX;
  this->y += this->stepY;
}
