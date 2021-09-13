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

  cout << "new iteration: ------------------------- " << endl;
  cout << "\n " << endl;

  for (int colIndex = 0; colIndex < windowWidth; colIndex++) {
    for (int rowIndex = 0; rowIndex < windowHeight; rowIndex++) {
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

      int existedNeighborsAmount = 0;

      for (int neighborIndex = 0; neighborIndex < neighborsAmount; neighborIndex++) {
        const int * neighborCoordinates = neighborsCoordinates[neighborIndex];
        const int neighborColIndex = neighborCoordinates[0];
        const int neighborRowIndex = neighborCoordinates[1];

        const bool neighborOutOfDimension =
          pointHandler.isPointOutOfDimension(neighborColIndex, neighborRowIndex);

        // if (rowIndex == 0 && colIndex == 0) {
        //   cout << "neighborColIndex " << neighborColIndex << endl;
        //   cout << "neighborRowIndex " << neighborRowIndex << endl;
        //   cout << "neighborOutOfDimension " << neighborOutOfDimension << endl;
        //   cout << "\n " << endl;
        // }

        if (neighborOutOfDimension) {
          continue;
        }
        
        existedNeighborsAmount++;
        const int neighborIndexInPixelsBuffer =
          pointHandler.getPointIndexInPixelsBuffer(neighborColIndex, neighborRowIndex);

        const Uint32 pixel = bufferSnapshot[neighborIndexInPixelsBuffer];

        const Uint8 neighborRed = pixel >> 24;
        const Uint8 neighborGreen = pixel >> 16;
        const Uint8 neighborBlue = pixel >> 8;

        totalRed += neighborRed;
        totalGreen += neighborGreen;
        totalBlue += neighborBlue;
      }

      Uint8 bluredColor[] = {
        totalRed / existedNeighborsAmount,
        totalGreen / existedNeighborsAmount,
        totalBlue / existedNeighborsAmount,
      };

      if (bluredColor[0] != 255) {
        cout << "colIndex " << colIndex << endl;
        cout << "rowIndex " << rowIndex << endl;

        cout << "avg Red " << (int)bluredColor[0] << endl;
        cout << "avg Green " << (int)bluredColor[1] << endl;
        cout << "avg Blue " << (int)bluredColor[2] << endl;

        cout << "existedNeighborsAmount " << existedNeighborsAmount << endl;
        cout << "\n" << endl;
      }

      const int targetPixelIndex = pointHandler.getPointIndexInPixelsBuffer(colIndex, rowIndex);

      window.setPixelColorByIndex(targetPixelIndex, bluredColor);
    }
  }
}
