#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "./Window/Window.h"
#include "./Swarm/Swarm.h"
#include "./Point/Point.h"

using namespace std;

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "Error while initialization" << endl;
    cout << "The error is " << SDL_GetError() << endl;

    return -1;
  };
  
  srand(time(0));

  const int WINDOW_HEIGHT = 600;
  const int WINDOW_WIDTH = 800;
  const int PIXELS_AMOUNT = WINDOW_HEIGHT * WINDOW_WIDTH;
  const int SWARM_SIZE = PIXELS_AMOUNT / 40;

  Window * window = new Window("fire-entity", WINDOW_WIDTH, WINDOW_HEIGHT);
  window->setSolidBgColor(0);

  Swarm swarm(SWARM_SIZE, window);
  swarm.fillWindow();

  SDL_Event event;
  bool loopInProgress = true;

  while (loopInProgress) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: {
          SDL_Quit();
          loopInProgress = false;
        }
      }
    }
  }

  delete window;

  return 0;
}
