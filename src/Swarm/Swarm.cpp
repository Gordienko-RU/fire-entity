#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#include "./Swarm.h"
#include "../Point/Point.h"
#include "../Window/Window.h"

Swarm::Swarm(int size, int maxX, int maxY):
  size(size),
  maxX(maxX),
  maxY(maxY) {
  Uint8 initialPointColor[] = { 255, 255, 255, 255 };
  this->pointColor = initialPointColor;
  this->points = new Point * [size];

  for (int i = 0; i < size; i++) {
    points[i] = new Point(maxX, maxY);
  }
}

Swarm::~Swarm() {
  delete [] this->points;
}

bool Swarm::isPointXCoordinateOutOfDimension(int x) const {
  return x < 0 || x > this->maxX;
}

bool Swarm::isPointYCoordinateOutOfDimension(int y) const {
  return y < 0 || y > this->maxY;
}

void Swarm::fixPointMovingDirection(Point * point) {
  if (this->isPointXCoordinateOutOfDimension(point->x)) {
    point->stepX *= -1;
  }

  if (this->isPointYCoordinateOutOfDimension(point->y)) {
    point->stepY *= -1;
  }
}

void Swarm::fillWindowWithRandomPoints(Window &window) {
  for (int i = 0; i < this->size; i++) {
    Point *point = this->points[i];
    point->updatePosition();

    const bool pointOutOfDimension =
      this->isPointXCoordinateOutOfDimension(point->x)
      || this->isPointYCoordinateOutOfDimension(point->y);

    if (pointOutOfDimension) {
      this->fixPointMovingDirection(point);
      return;
    }

    const int pointIndex = (point->y - 1) * this->maxX + point->x;
    window.setPixelColorByIndex(pointIndex, this->pointColor);
  }
}
