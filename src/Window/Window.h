#ifndef WINDOW
#define WINDOW

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Window {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    Uint32 *pixelsBuffer;

    int windowWidth;
    int windowHeight;
    int pixelsAmount;
  public:
    Window(string name, int width, int height);
    ~Window();
    void updateWindowContent() const;
    void setSolidBgColor(int rgbValue) const;
    void setPixelColor(Uint32 *pixel, Uint8 *colorValues) const;
    void setPixelColorByIndex(int index, Uint8 *colorValues) const;
    Uint32* getPixel(int index) const;
};

#endif // !WINDOW