#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#include "../Window/Window.h"
#include "../Swarm/Swarm.h"
#include "../BoxBlur/BoxBlur.h"
#include "./EventLoop.h"

EventLoop::EventLoop(Window &window, Swarm &swarm, BoxBlur &boxBlur)
  : window(window), swarm(swarm), boxBlur(boxBlur), loopInProgress(false) {}

void EventLoop::stop() {
  this->loopInProgress = false;
}

void EventLoop::start() {
  this->loopInProgress = true;

  while (this->loopInProgress) {
    this->swarm.fillWindowWithRandomPoints(window);
    this->boxBlur.applyBlur();
    this->window.updateWindowContent();

    while (SDL_PollEvent(&this->event)) {
      switch (this->event.type) {
        case SDL_QUIT: {
          SDL_Quit();
          this->stop();
        }
      }
    }
  }
}
