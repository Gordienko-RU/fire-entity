#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#include "../Window/Window.h"
#include "../Swarm/Swarm.h"
#include "../BoxBlur/BoxBlur.h"
#include "./EventLoop.h"
#include "../PointHandler/PointHandler.h"

EventLoop::EventLoop(Window &window, Swarm &swarm, BoxBlur &boxBlur, PointHandler &pointHandler)
  :
  window(window),
  swarm(swarm),
  boxBlur(boxBlur),
  pointHandler(pointHandler),
  loopInProgress(false) {}

void EventLoop::stop() {
  this->loopInProgress = false;
}

// TODO: no need to keep references as class member, we can just pass them as args
void EventLoop::start() {
  this->loopInProgress = true;

  while (this->loopInProgress) {
    this->swarm.fillWindowWithRandomPoints(this->window);
    this->boxBlur.applyBlur(this->window, this->pointHandler);
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
