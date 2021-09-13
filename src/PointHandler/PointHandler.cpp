#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#include "./PointHandler.h"
#include "./Point/Point.h"

PointHandler::PointHandler(int maxX, int maxY)
  :
  maxX(maxX),
  maxY(maxY),
  minX(0),
  minY(0) {};

Point * PointHandler::createDimensionPoint() const {
  return new Point(this->maxX, this->maxY);
}

bool PointHandler::isPointYCoordinateOutOfDimension(int y) const {
  return y < this->minY || y > this->maxY - 1;
}

bool PointHandler::isPointXCoordinateOutOfDimension(int x) const {
  return x < this->minX || x > this->maxX - 1;
}

bool PointHandler::isPointOutOfDimension(int x, int y) const {
  return this->isPointXCoordinateOutOfDimension(x)
    || this->isPointYCoordinateOutOfDimension(y);
}

void PointHandler::fixPointMovingDirection(Point * point) const {
  if (this->isPointXCoordinateOutOfDimension(point->x)) {
    point->stepX *= -1;
  }

  if (this->isPointYCoordinateOutOfDimension(point->y)) {
    point->stepY *= -1;
  }
}

int PointHandler::getPointIndexInPixelsBuffer(int x, int y) const {
  return y * this->maxX + x;
}
