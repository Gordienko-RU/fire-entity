#ifndef SWARM
#define SWARM

#include <SDL2/SDL.h>
#include <string>

#include "../Point/Point.h"
#include "../Window/Window.h"

using namespace std;

class Swarm {
  private:
    int maxX;
    int maxY;
    int size;
    Uint8 *pointColor;

    void fixPointMovingDirection(Point *point);
    bool isPointXCoordinateOutOfDimension(int x) const;
    bool isPointYCoordinateOutOfDimension(int y) const;
  public:
    Point ** points;
    Swarm(int size, int maxX, int maxY);
    ~Swarm();

    void fillWindowWithRandomPoints(Window &window);
};

#endif // !SWARM