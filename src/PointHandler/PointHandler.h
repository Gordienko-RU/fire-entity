#ifndef POINT_HANDLER
#define POINT_HANDLER

#include <SDL2/SDL.h>
#include <string>
#include "./Point/Point.h"

using namespace std;

class PointHandler {
  private:
    const int maxX;
    const int maxY;
    const int minX;
    const int minY;

  public:
    PointHandler(int maxX, int maxY);
    Point * createDimensionPoint() const;
    bool isPointYCoordinateOutOfDimension(int y) const;
    bool isPointXCoordinateOutOfDimension(int x) const;
    bool isPointOutOfDimension(int x, int y) const;
    void fixPointMovingDirection(Point * point) const;
    int getPointIndexInPixelsBuffer(int x, int y) const;
};

#endif // !POINT_HANDLER