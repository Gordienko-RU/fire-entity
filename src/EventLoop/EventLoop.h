#ifndef EVENT_LOOP
#define EVENT_LOOP

#include <SDL2/SDL.h>

using namespace std;

class EventLoop {
  private:
    SDL_Event event;
    bool loopInProgress;
  public:
    EventLoop();
    void start();
    void end();
};

#endif // !EVENT_LOOP