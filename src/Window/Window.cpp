#include <string>
#include <SDL2/SDL.h>
#include <iostream>

#include "./Window.h"

void Window::blurPixels() {
  Uint32 *temp = this->pixelsBuffer;
  this->pixelsBuffer = this->tempPixelsBuffer;
  this->tempPixelsBuffer = temp;

  /*
    NOTE: We are picking average color of all pixels in 3x3 matrix(target pixel neighbors),
    and calculate average r,g,b values to set them to target pixel.
  */
  // TODO: make a decomposition, too much stuff
  for (int targetPixelIndex = 0; targetPixelIndex < this->pixelsAmount; targetPixelIndex++) {
    const int participantIndexes[] = {
      targetPixelIndex - 1 - this->windowWidth,
      targetPixelIndex - this->windowWidth,
      targetPixelIndex + 1 - this->windowWidth,
      targetPixelIndex - 1,
      targetPixelIndex,
      targetPixelIndex + 1,
      targetPixelIndex - 1 + this->windowWidth,
      targetPixelIndex + this->windowWidth,
      targetPixelIndex + 1 + this->windowWidth,
    };

    const Uint8 sizeOfParticipantsArr = sizeof(participantIndexes);

    Uint8 totalRed = 0;
    Uint8 totalGreen = 0;
    Uint8 totalBlue = 0;

    for (int indexOfParticipantIndex = 0; indexOfParticipantIndex < sizeOfParticipantsArr; indexOfParticipantIndex++) {
      const int participantIndex = participantIndexes[indexOfParticipantIndex];
      // TODO: looks like such check is not enough since in fact we have 2 dimensional array
      const bool pixelWithinDimension = participantIndex > 0 && participantIndex < this->pixelsAmount;
      
      if (!pixelWithinDimension) {
        continue;
      }

      Uint32 participatedPixel = this->tempPixelsBuffer[participantIndex];

      totalRed += participatedPixel >> 24;
      totalGreen += participatedPixel >> 16;
      totalBlue += participatedPixel >> 8;
    }

    const Uint8 participantsAmount = sizeOfParticipantsArr / sizeof(int);

    Uint8 bluredColorDescriptor[] = {
      totalRed / participantsAmount,
      totalGreen / participantsAmount,
      totalBlue / participantsAmount,
      255,
    };

    this->setPixelColorByIndex(targetPixelIndex, bluredColorDescriptor);
  }
}

Window::Window(string name, int width, int height) {
  this->windowWidth = width;
  this->windowHeight = height;
  this->pixelsAmount = width * height;

  // TODO: This Uint32 used in a lot of places, can we set it as class variable?
  this->pixelsBuffer = new Uint32[this->pixelsAmount];
  this->tempPixelsBuffer = new Uint32[this->pixelsAmount];

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
  delete [] this->tempPixelsBuffer;
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
  memset(this->tempPixelsBuffer, rgbValue, bufferByteSize);
}
