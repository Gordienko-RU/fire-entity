#include <string>
#include <SDL2/SDL.h>
#include <iostream>

#include "./Window.h"
#include "../Color.h"

Window::Window(string name, int width, int height) {
  this->windowWidth = width;
  this->windowHeight = height;
  this->pixelsAmount = width * height;

  this->pixelsBuffer = new Uint32[this->pixelsAmount];

  // TODO: Handle errors while creation.
  this->window =
    SDL_CreateWindow(
      "fire entity",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      this->windowWidth,
      this->windowHeight,
      SDL_WINDOW_SHOWN);

  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  this->texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_STATIC,
    this->windowWidth,
    this->windowHeight);

  const Color bgColor(255, 255, 255);

  this->setSolidBgColor(bgColor);
};

Window::~Window() {
  delete [] this->pixelsBuffer;
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyTexture(this->texture);
  SDL_DestroyWindow(this->window);
}

void Window::updateWindowContent() const {
  SDL_UpdateTexture(this->texture, NULL, this->pixelsBuffer, this->windowWidth * sizeof(Uint32));
  SDL_RenderClear(this->renderer);
  SDL_RenderCopy(this->renderer, texture, NULL, NULL);
  SDL_RenderPresent(this->renderer);
}

void Window::setPixelColorByIndex(int index, Color color) const {
  Uint32 finalColorToSet = 0;
  const int amountOfBytesToSet = sizeof(Uint32);

  finalColorToSet += color.red;
  finalColorToSet <<= 8;

  finalColorToSet += color.green;
  finalColorToSet <<= 8;

  finalColorToSet += color.blue;
  finalColorToSet <<= 8;

  finalColorToSet += 255;

  this->pixelsBuffer[index] = finalColorToSet;
}

Uint32* Window::getPixel(int index) const {
  return this->pixelsBuffer + index;
}

void Window::setSolidBgColor(Color color) const {
  for (int i = 0; i < this->pixelsAmount; i++) {
    this->setPixelColorByIndex(i, color);
  }
}
