#ifndef POINT
#define POINT

#include <SDL2/SDL.h>

using namespace std;

class Point {
  public:
    int x;
    int y;
    int stepX;
    int stepY;

    Point(int maxX, int maxY);
    void updatePosition();
};

#endif // !POINT