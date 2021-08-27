#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#include "./Point.h"

Point::Point(int maxX, int maxY): x(maxX/2), y(maxY/2) {
  // TODO: We can make step boundaries random as well, so point will have random step range.
  this->stepX = (rand() % 11) - 5;
  this->stepY = (rand() % 11) - 5;
}

void Point::updatePosition() {
  this->x += this->stepX;
  this->y += this->stepY;
}
