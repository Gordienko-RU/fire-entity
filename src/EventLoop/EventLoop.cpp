#include <SDL2/SDL.h>

#include "./EventLoop.h"

EventLoop::EventLoop() {
  this->loopInProgress = false;
}

void EventLoop::start() {
  this->loopInProgress = true;

  while (this->loopInProgress) {
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

void EventLoop::end() {
  this->loopInProgress = false;
}