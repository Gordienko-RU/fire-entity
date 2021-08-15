#ifndef POINT
#define POINT

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Point {
  public:
    int positionX;
    int positionY;
    Point(int windowWidth, int windowHeight);
};

#endif // !POINT