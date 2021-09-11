#include <string>
#include <SDL2/SDL.h>
#include <iostream>

#include "./Window.h"

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

  this->setSolidBgColor(255);
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

void Window::setPixelColor(Uint32 *pixel, Uint8 *colorValues) const {
  Uint8 *pToSinglePixel = (Uint8 *) pixel;
  const int amountOfBytesToSet = sizeof(Uint32);

  for (Uint8 i = 0; i < amountOfBytesToSet; i++) {
    pToSinglePixel[i] = colorValues[i];
  }
}

void Window::setPixelColorByIndex(int index, Uint8 *colorValues) const {
  Uint32 color = 0;
  const int amountOfBytesToSet = sizeof(Uint32);

  for (Uint8 i = 0; i < amountOfBytesToSet; i++) {
    color += colorValues[i];
    color <<= 8;
  }

  this->pixelsBuffer[index] = color;
}

Uint32* Window::getPixel(int index) const {
  return this->pixelsBuffer + index;
}

void Window::setSolidBgColor(int rgbValue) const {
  const int bufferByteSize = this->pixelsAmount * sizeof(Uint32);

  memset(this->pixelsBuffer, rgbValue, bufferByteSize);
}
