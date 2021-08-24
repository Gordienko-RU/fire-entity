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
  Uint8 initialPointColor[] = { 255, 255, 255, 0 };
  this->pointColor = initialPointColor;
  this->points = new Point * [size];

  for (int i = 0; i < size; i++) {
    points[i] = new Point(maxX, maxY);
  }
}

Swarm::~Swarm() {
  delete [] this->points;
}

void Swarm::fixPointMovingDirection(Point * point) {
  if (point->x < 0 || point->x > this->maxX) {
    point->stepX *= -1;
  }

  if (point->y < 0 || point->y > this->maxY) {
    point->stepY *= -1;
  }
}

void Swarm::fillWindowWithRandomPoints(Window &window) {
  for (int i = 0; i < this->size; i++) {
    Point *point = this->points[i];
    point->updatePosition();

    const int pointIndex = (point->y - 1) * this->maxX + point->x;
    const int indexOutOfDimension = pointIndex < 0 || pointIndex > window.pixelsAmount;

    if (indexOutOfDimension) {
      this->fixPointMovingDirection(point);
      return;
    }

    window.setPixelColorByIndex(pointIndex, this->pointColor);
  }
}
