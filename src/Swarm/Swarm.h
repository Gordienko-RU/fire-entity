#ifndef SWARM
#define SWARM

#include <SDL2/SDL.h>
#include <string>

#include "../Point/Point.h"
#include "../Window/Window.h"

using namespace std;

class Swarm {
  private:
    Window * window;
    int size;
  public:
    Point ** points;
    Swarm(int size, Window * window);
    ~Swarm();

    void fillWindow() const;
};

#endif // !SWARM