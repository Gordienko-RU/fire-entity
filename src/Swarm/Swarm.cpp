#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>

#include "./Swarm.h"
#include "../Point/Point.h"
#include "../Window/Window.h"

Swarm::Swarm(int size, Window * window): window(window), size(size) {
  this->points = new Point * [size];

  for (int i = 0; i < size; i++) {
    points[i] = new Point(window->windowWidth, window->windowHeight);
  }
}

Swarm::~Swarm() {
  delete [] this->points;
}

void Swarm::fillWindow() const {
  Uint8 pointColor [] = { 255, 255, 255, 0 };

  // TODO: not elegant, need kind of destructurization here
  for (int i = 0; i < this->size; i++) {
    Point *point = this->points[i];
    const int pointPosition = (point->positionY - 1) * this->window->windowWidth + point->positionX;

    this->window->setPixelColorByIndex(pointPosition, pointColor);
  }

  window->updateWindowContent();
}
