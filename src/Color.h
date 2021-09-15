#ifndef COLOR
#define COLOR

#include <SDL2/SDL.h>

struct Color {
  Color(Uint8 r, Uint8 g, Uint8 b): red(r), green(g), blue(b) {};

  Uint8 red;
  Uint8 green;
  Uint8 blue;
};

#endif // !COLOR