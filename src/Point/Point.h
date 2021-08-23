#ifndef POINT
#define POINT

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Point {
  public:
    static const int INITIAL_POINT_VALUE = -1;

    int positionX;
    int positionY;

    Point();
    void updatePosition(int maxXDimension, int maxYDimension);
};

#endif // !POINT