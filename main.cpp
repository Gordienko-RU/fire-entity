#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main() {
  // TODO: Each step should be placed into separate function, to make all that clear.
  // Or probably it would be better for future extension to split it into classes and move to
  // appropriate files as well.

  // TODO: Think about correct error handling. At the moment it would be enough to have one global catch,
  // to catch and log all errors.

  // TODO: It would be fun to build some inner interface above SDL, to make it abstract,
  // so in future we can switch lib for pixel handling without extra pain.

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "Error while initialization" << endl;
    cout << "The error is " << SDL_GetError() << endl;

    return -1;
  };

  const int SCREEN_HEIGHT = 600;
  const int SCREEN_WIDTH = 800;

  SDL_Window *window =
    SDL_CreateWindow(
      "fire entity",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN);

  if (window == NULL) {
    cout << "Error while creating window" << endl;
    cout << "The error is " << SDL_GetError() << endl;

    return -2;
  }

  // TODO: Event loop pooling also deserves separate class.

  SDL_Event event;
  bool quitProgram = false;

  while (!quitProgram) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: {
          SDL_Quit();
          SDL_DestroyWindow(window);
          quitProgram = true;
        }
      }
    }
  }

  cout << "Programm ended" << endl;

  return 0;
}
