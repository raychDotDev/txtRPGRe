#pragma once

#include "SDL2/SDL_pixels.h"
#include "TerminalFont.hpp"
#include <SDL2/SDL.h>
#include <valarray>

struct TerminalGlyph {
  int character;
  SDL_Color fg;
  SDL_Color bg;
};

class Terminal {
public:
  Terminal(SDL_Renderer *context, int width, int height);
  ~Terminal();
  void Display(SDL_Renderer *context);
  void SetGlyph(int x, int y, TerminalGlyph g);

private:
  TerminalFont *font;
  SDL_Texture *canvas;
  std::valarray<TerminalGlyph> buffer;
  int width, height;
};
