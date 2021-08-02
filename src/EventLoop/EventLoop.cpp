#include <SDL2/SDL.h>
#include <iostream>

#include "./EventLoop.h"

EventLoop::EventLoop() {
  this->loopInProgress = false;
}

void EventLoop::startListening() {
  this->loopInProgress = true;

  // TODO: remove after playing, as well as window prop from event loop
  const int pixelsAmount = this->window->windowHeight * this->window->windowWidth;

  Uint8 red = 0;
  Uint8 green = 0;
  Uint8 blue = 0;
  Uint8 alfa = 0;

  bool maxValueAchieved = false;

  while (this->loopInProgress) {
    Uint8 colors[] = { red, green, blue, alfa };

    switch(red) {
      case 255: {
        cout << "255 achieved" << endl;
        maxValueAchieved = true;
        break;
      }
      case 0: {
        cout << "0 achieved" << endl;
        maxValueAchieved = false;
        break;
      }
    }

    for (int i = 0; i < pixelsAmount; i++) {
      window->setPixelColorByIndex(i, colors);
    }

    if (maxValueAchieved) {
      red -= 1;
      green -= 1;
      blue -= 1;
    } else {
      red += 1;
      green += 1;
      blue += 1;
    }

    window->updateWindowContent();

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: {
          SDL_Quit();
          this->loopInProgress = false;
        }
      }
    }
  }
}

void EventLoop::stopListening() {
  this->loopInProgress = false;
}

void EventLoop::setWindow(Window *window) {
  this->window = window;
}