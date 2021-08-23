#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#include "./Point.h"

Point::Point(): positionX(Point::INITIAL_POINT_VALUE), positionY(Point::INITIAL_POINT_VALUE) {};

void Point::updatePosition(int maxXDimension, int maxYDimension) {
  const bool noInitialPosition = this->positionX == Point::INITIAL_POINT_VALUE;

  if (noInitialPosition) {
    this->positionX = rand() % maxXDimension;
    this->positionY = rand() % maxYDimension;

    return;
  }

  const int xStep = (2 * (rand() % 2)) - 1;
  const int yStep = (2 * (rand() % 2)) - 1;

  this->positionX += xStep;
  this->positionY += yStep;
}
