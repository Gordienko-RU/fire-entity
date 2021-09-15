#ifndef SWARM
#define SWARM

#include <SDL2/SDL.h>
#include <string>

#include "../PointHandler/PointHandler.h"
#include "../PointHandler/Point/Point.h"
#include "../Window/Window.h"
#include "../Color.h"

using namespace std;

class Swarm {
  private:
    int size;
    Color pointColor;
    PointHandler &pointHandler;

  public:
    Point ** points;
    Swarm(int size, PointHandler &pointHandler);
    ~Swarm();

    void fillWindowWithRandomPoints(Window &window);
};

#endif // !SWARM