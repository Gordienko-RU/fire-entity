#ifndef BOX_BLUR
#define BOX_BLUR

#include <SDL2/SDL.h>
#include <string>
#include "../Window/Window.h"
#include "../PointHandler/PointHandler.h"

using namespace std;

class BoxBlur {
  public:
    BoxBlur() {};
    void applyBlur(Window &window, PointHandler &pointHandler) const;
};

#endif // !BOX_BLUR