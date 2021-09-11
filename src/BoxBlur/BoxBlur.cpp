#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#include "./BoxBlur.h"
#include "../Window/Window.h"

void BoxBlur::applyBlur(Window &window) {
  const int pixelsAmount = window.pixelsAmount;

  Uint32 bufferSnapshot[pixelsAmount];
  Uint32 *originalBuffer = window.pixelsBuffer;
  
  // TODO: there are better ways to copy array
  for (int i = 0; i < pixelsAmount; i++) {
    bufferSnapshot[i] = originalBuffer[i];
  }

  /*
    NOTE: We are picking average color of all pixels in 3x3 matrix(target pixel neighbors),
    and calculate average r,g,b values to set them to target pixel.
  */

  const int windowWidth = window.windowWidth;

  for (int targetPixelIndex = 0; targetPixelIndex < pixelsAmount; targetPixelIndex++) {
    const int participantIndexes[] = {
      targetPixelIndex - 1 - windowWidth,
      targetPixelIndex - windowWidth,
      targetPixelIndex + 1 - windowWidth,
      targetPixelIndex - 1,
      targetPixelIndex,
      targetPixelIndex + 1,
      targetPixelIndex - 1 + windowWidth,
      targetPixelIndex + windowWidth,
      targetPixelIndex + 1 + windowWidth,
    };

    const Uint8 sizeOfParticipantsArr = sizeof(participantIndexes);

    int totalRed = 0;
    int totalGreen = 0;
    int totalBlue = 0;

    for (int indexOfParticipantIndex = 0; indexOfParticipantIndex < sizeOfParticipantsArr; indexOfParticipantIndex++) {
      const int participantIndex = participantIndexes[indexOfParticipantIndex];
      // TODO: looks like such check is not enough since in fact we have 2 dimensional array
      const bool pixelWithinDimension = participantIndex > 0 && participantIndex < pixelsAmount;
      
      if (!pixelWithinDimension) {
        continue;
      }

      Uint32 participatedPixel = bufferSnapshot[participantIndex];

      Uint8 participantRed = participatedPixel >> 24;
      Uint8 participantGreen = participatedPixel >> 16;
      Uint8 participantBlue = participatedPixel >> 8;

      const bool pixelHasBGColor =
        (participantRed == 255) &&
        (participantGreen == 255) &&
        (participantBlue == 255);


      if (pixelHasBGColor) {
        continue;
      }

      totalRed += participantRed;
      totalGreen += participantGreen;
      totalBlue += participantBlue;
    }

    const Uint8 participantsAmount = sizeOfParticipantsArr / sizeof(int);

    Uint8 bluredColorDescriptor[] = {
      totalRed / participantsAmount,
      totalGreen / participantsAmount,
      totalBlue / participantsAmount,
      255,
    };

    window.setPixelColorByIndex(targetPixelIndex, bluredColorDescriptor);
  }
}
