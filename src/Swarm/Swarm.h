#ifndef SWARM
#define SWARM

#include <SDL2/SDL.h>
#include <string>

#include "../Point/Point.h"
#include "../Window/Window.h"

using namespace std;

class Swarm {
  private:
    int maxXDimension;
    int maxYDimension;
    int size;
  public:
    Point ** points;
    Swarm(int size, int maxXDimension, int maxYDimension);
    ~Swarm();

    void fillWindowWithRandomPoints(Window &window) const;
};

#endif // !SWARM