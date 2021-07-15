#include <string>
#include <SDL2/SDL.h>

#include "./Window.h"

Window::Window(string name, int width, int height) {
  this->windowWidth = width;
  this->windowHeight = height;
  this->pixelsAmount = width * height;

  // TODO: This Uint32 used in a lot of places, can we set it as class variable?
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

  for (int i = 0; i < amountOfBytesToSet; i++) {
    pToSinglePixel[i] = colorValues[i];
  }
}

Uint32* Window::getPixel(int index) const {
  return this->pixelsBuffer + index;
}

void Window::setSolidBgColor(int rgbValue) const {
  memset(this->pixelsBuffer, rgbValue, this->pixelsAmount * sizeof(Uint32));
  this->updateWindowContent();
}
