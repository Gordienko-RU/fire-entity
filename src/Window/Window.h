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

    void updateWindowContent() const;
  public:
    Window(string name, int width, int height);
    ~Window();
    void setPixelsValue(int rgbValue) const;
};

#endif // !WINDOW