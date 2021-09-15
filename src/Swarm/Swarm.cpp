#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm> 

#include "../PointHandler/PointHandler.h"
#include "../PointHandler/Point/Point.h"
#include "./Swarm.h"
#include "../Window/Window.h"

Swarm::Swarm(int size, PointHandler &pointHandler)
  : size(size), pointHandler(pointHandler), pointColor(255, 140, 0) {

  this->points = new Point * [size];

  for (int i = 0; i < size; i++) {
    points[i] = this->pointHandler.createDimensionPoint();
  }
}

Swarm::~Swarm() {
  delete [] this->points;
}

void Swarm::fillWindowWithRandomPoints(Window &window) {
  for (int i = 0; i < this->size; i++) {
    Point *point = this->points[i];
    point->updatePosition();

    const int &x = point->x;
    const int &y = point->y;

    const bool pointOutOfDimension = this->pointHandler.isPointOutOfDimension(x, y);

    if (pointOutOfDimension) {
      this->pointHandler.fixPointMovingDirection(point);
      continue;
    }

    const int pointIndex = this->pointHandler.getPointIndexInPixelsBuffer(x, y);
    window.setPixelColorByIndex(pointIndex, this->pointColor);
  }
}
