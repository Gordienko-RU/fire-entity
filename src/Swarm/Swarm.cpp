#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>

#include "./Swarm.h"
#include "../Point/Point.h"

Swarm::Swarm(int size, int windowHeight, int windowWidth) {
  this->size = size;
  this->points = new Point * [size];

  for (int i = 0; i < size; i++) {
    points[i] = new Point(windowHeight, windowWidth);
  }
}
