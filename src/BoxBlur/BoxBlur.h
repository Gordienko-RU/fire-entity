#ifndef BOX_BLUR
#define BOX_BLUR

#include <SDL2/SDL.h>
#include <string>
#include "../Window/Window.h"
#include "../PointHandler/PointHandler.h"

using namespace std;

class BoxBlur {
  private:
    Window &window;

  public:
    BoxBlur(Window &window);
    void applyBlur() const;
};

#endif // !BOX_BLUR