#ifndef POINT
#define POINT

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Point {
  private:
    double positionX;
    double positionY;
  public:
    Point(int windowHeight, int windowWidth);
};

#endif // !POINT