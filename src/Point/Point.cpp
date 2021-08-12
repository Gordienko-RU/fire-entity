#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>

#include "./Point.h"

Point::Point(int windowHeight, int windowWidth) {
  this->positionX = rand() % windowWidth;
  this->positionY = rand() % windowHeight;
}
