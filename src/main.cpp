#include <iostream>
#include <SDL2/SDL.h>

#include "./Window/Window.h"

using namespace std;

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "Error while initialization" << endl;
    cout << "The error is " << SDL_GetError() << endl;

    return -1;
  };

  Window window("fire-entity", 800, 600);
  window.setPixelsValue(255);

  // TODO: Event loop pooling also deserves separate class.
  SDL_Event event;
  bool quitProgram = false;

  while (!quitProgram) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: {
          SDL_Quit();
          quitProgram = true;
        }
      }
    }
  }

  cout << "Programm ended" << endl;

  return 0;
}
