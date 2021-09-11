#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "./Window/Window.h"
#include "./Swarm/Swarm.h"
#include "./PointHandler/PointHandler.h"
#include "./BoxBlur/BoxBlur.h"

using namespace std;

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "Error while initialization" << endl;
    cout << "The error is " << SDL_GetError() << endl;

    return -1;
  };
  
  srand(time(0));

  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 600;
  const int PIXELS_AMOUNT = WINDOW_HEIGHT * WINDOW_WIDTH;
  const int SWARM_SIZE = 1;

  Window window("fire-entity", WINDOW_WIDTH, WINDOW_HEIGHT);
  BoxBlur boxBlur(window);

  PointHandler pointHandler(WINDOW_WIDTH, WINDOW_HEIGHT);
  Swarm swarm(SWARM_SIZE, pointHandler);

  SDL_Event event;
  bool loopInProgress = true;

  while (loopInProgress) {
    swarm.fillWindowWithRandomPoints(window);
    boxBlur.applyBlur();
    window.updateWindowContent();

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: {
          SDL_Quit();
          loopInProgress = false;
        }
      }
    }
  }

  return 0;
}
