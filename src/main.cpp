#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "./Window/Window.h"
#include "./Swarm/Swarm.h"
#include "./PointHandler/PointHandler.h"
#include "./BoxBlur/BoxBlur.h"
#include "./EventLoop/EventLoop.h"

using namespace std;

void initializeApp() {
  // TODO: potentially can have errors here - add error handler
  SDL_Init(SDL_INIT_VIDEO);
  srand(time(0));
}

int main() {
  initializeApp();
  
  const int WINDOW_WIDTH = 5;
  const int WINDOW_HEIGHT = 5;
  const int PIXELS_AMOUNT = WINDOW_HEIGHT * WINDOW_WIDTH;
  const int SWARM_SIZE = 1;

  Window window("fire-entity", WINDOW_WIDTH, WINDOW_HEIGHT);
  BoxBlur boxBlur;

  PointHandler pointHandler(WINDOW_WIDTH, WINDOW_HEIGHT);
  Swarm swarm(SWARM_SIZE, pointHandler);

  EventLoop eventLoop(window, swarm, boxBlur, pointHandler);
  eventLoop.start();

  return 0;
}
