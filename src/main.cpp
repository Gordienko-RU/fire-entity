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

  Uint8 blueColor[] = { 255, 255, 255, 255 };

  for (int i = 30000; i < 80000; i++) {
    window.setPixelColorByIndex(i, blueColor);
  } 

  window.updateWindowContent();

  EventLoop eventLoop;
  eventLoop.startListening();

  return 0;
}
