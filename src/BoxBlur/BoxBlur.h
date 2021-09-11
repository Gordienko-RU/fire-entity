#ifndef BOX_BLUR
#define BOX_BLUR

#include <SDL2/SDL.h>
#include <string>
#include "../Window/Window.h"

using namespace std;

class BoxBlur {
  public:
    BoxBlur() {};
    void applyBlur(Window &window);
};

#endif // !BOX_BLUR