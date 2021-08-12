#ifndef SWARM
#define SWARM

#include <SDL2/SDL.h>
#include <string>
#include "../Point/Point.h"

using namespace std;

class Swarm {
  private:
    int size;
    Point ** points;
  public:
    Swarm(int size, int windowHeight, int windowWidth);
    ~Swarm();
};

#endif // !SWARM