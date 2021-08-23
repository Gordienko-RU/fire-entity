#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#include "./Swarm.h"
#include "../Point/Point.h"
#include "../Window/Window.h"

Swarm::Swarm(int size, int maxXDimension, int maxYDimension):
  maxXDimension(maxXDimension),
  size(size),
  maxYDimension(maxYDimension) {
  this->points = new Point * [size];

  for (int i = 0; i < size; i++) {
    points[i] = new Point();
  }
}

Swarm::~Swarm() {
  delete [] this->points;
}

void Swarm::fillWindowWithRandomPoints(Window &window) const {
  Uint8 pointColor [] = { 255, 255, 255, 0 };

  for (int i = 0; i < this->size; i++) {
    Point *point = this->points[i];
    point->updatePosition(this->maxXDimension, this->maxYDimension);

    const int pointPosition = (point->positionY - 1) * this->maxXDimension + point->positionX;

    window.setPixelColorByIndex(pointPosition, pointColor);
  }
}
