#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#include "./BoxBlur.h"
#include "../Window/Window.h"
#include "../PointHandler/PointHandler.h"

void BoxBlur::applyBlur(Window &window, PointHandler &pointHandler) const {
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
  const int &windowWidth = window.windowWidth;
  const int &windowHeight = window.windowHeight;

  for (int colIndex = 0; colIndex < 1; colIndex++) {
    for (int rowIndex = 0; rowIndex < 1; rowIndex++) {
      const int neighborsAmount = 9;

      const int neighborsCoordinates[neighborsAmount][2] = {
        { colIndex - 1, rowIndex - 1 },
        { colIndex, rowIndex - 1 },
        { colIndex + 1, rowIndex - 1 },

        { colIndex - 1, rowIndex },
        { colIndex, rowIndex },
        { colIndex + 1, rowIndex },

        { colIndex - 1, rowIndex + 1 },
        { colIndex, rowIndex + 1 },
        { colIndex + 1, rowIndex + 1 },
      };

      int totalRed = 0;
      int totalGreen = 0;
      int totalBlue = 0;

      // NOTE: existed and not empty bg pixels amount
      int relevantNeighborsAmount = 0;

      for (int neighborIndex = 0; neighborIndex < neighborsAmount; neighborIndex++) {
        const int * neighborCoordinates = neighborsCoordinates[neighborIndex];

        const int neighborColIndex = neighborCoordinates[0];
        const int neighborRowIndex = neighborCoordinates[1];
        const bool neighborOutOfDimension =
          pointHandler.isPointOutOfDimension(neighborColIndex, neighborRowIndex);

        if (neighborOutOfDimension) {
          continue;
        }

        const int neighborIndexInPixelsBuffer =
          pointHandler.getPointIndexInPixelsBuffer(neighborColIndex, neighborRowIndex);

        const Uint32 pixel = bufferSnapshot[neighborIndexInPixelsBuffer];

        cout << "pixel value: " << pixel << endl;

        const Uint8 neighborRed = pixel >> 24;
        const Uint8 neighborGreen = pixel >> 16;
        const Uint8 neighborBlue = pixel >> 8;

        cout << "rgb: " << neighborRed << " " << neighborGreen << " " << neighborBlue << endl;

        /*
          TODO: Not solid, we should have one source of truth, when declaring
          window solid bg, and when making such check, maybe even class, with
          const member and method to check point color.
        */
        const bool neighborIsEmptyPoint =
          neighborRed == 255 && neighborGreen == 255 && neighborBlue == 255;

        if (neighborIsEmptyPoint) {
          continue;
        }

        relevantNeighborsAmount++;

        totalRed += neighborRed;
        totalGreen += neighborGreen;
        totalBlue += neighborBlue;
      }

      if (!relevantNeighborsAmount) {
        continue;
      }

      cout << "relevant neighbors amount: " << relevantNeighborsAmount << endl;

      Uint8 bluredColor[] = {
        totalRed / relevantNeighborsAmount,
        totalGreen / relevantNeighborsAmount,
        totalBlue / relevantNeighborsAmount,
        255,
      };

      const int targetPixelIndex = pointHandler.getPointIndexInPixelsBuffer(colIndex, rowIndex);

      window.setPixelColorByIndex(targetPixelIndex, bluredColor);
    }
  }
}
