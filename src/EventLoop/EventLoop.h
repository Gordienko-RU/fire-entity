#ifndef EVENT_LOOP
#define EVENT_LOOP

#include <SDL2/SDL.h>
#include "../Window/Window.h"

using namespace std;

class EventLoop {
  private:
    SDL_Event event;
    Window *window;
    bool loopInProgress;
  public:
    EventLoop();
    void startListening();
    void stopListening();
    void setWindow(Window *window);
};

#endif // !EVENT_LOOP