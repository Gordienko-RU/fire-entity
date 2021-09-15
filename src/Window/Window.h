#ifndef WINDOW
#define WINDOW

#include <SDL2/SDL.h>
#include <string>
#include "../Color.h"

using namespace std;

class Window {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

  public:
    Uint32 *pixelsBuffer;
    Window(string name, int width, int height);
    ~Window();

    void blurPixels();
    void updateWindowContent() const;
    void setSolidBgColor(Color color) const;
    void setPixelColorByIndex(int index, Color color) const;

    Uint32* getPixel(int index) const;

    int windowWidth;
    int windowHeight;
    int pixelsAmount;
};

#endif // !WINDOW