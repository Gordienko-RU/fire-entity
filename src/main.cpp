#include <iostream>
#include <SDL2/SDL.h>

#include "./Window/Window.h"
#include "./EventLoop/EventLoop.h"

using namespace std;

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "Error while initialization" << endl;
    cout << "The error is " << SDL_GetError() << endl;

    return -1;
  };

  Window window("fire-entity", 800, 600);
  window.setSolidBgColor(255);

  // TODO: test code, remove
  Uint8 blackRGBARepresentation[] = { 1, 1, 1, 1 };

  for (int i = 3600; i < 7800; i++) {
    Uint32 *pixel = window.getPixel(i);
    window.setPixelColor(pixel, blackRGBARepresentation);
  }

  window.updateWindowContent();
  //----------

  EventLoop eventLoop;
  eventLoop.startListening();

  return 0;
}
