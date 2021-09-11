#ifndef EVENT_LOOP
#define EVENT_LOOP

#include <SDL2/SDL.h>
#include "../Window/Window.h"
#include "../Swarm/Swarm.h"
#include "../BoxBlur/BoxBlur.h"

class EventLoop {
  private:
    SDL_Event event;
    Window &window;
    Swarm &swarm;
    BoxBlur &boxBlur;
    bool loopInProgress;

  public:
    EventLoop(Window &window, Swarm &swarm, BoxBlur &boxBlur);
    void start();
    void stop();
};

#endif // !EVENT_LOOP