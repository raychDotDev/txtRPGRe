#pragma once

#include "SDL2/SDL_pixels.h"
#include "TerminalFont.hpp"
#include <SDL2/SDL.h>
#include <string>
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
  int Print(int x, int y, const std::wstring &text);
  void Clear();
	void SetDefaultFGColor(SDL_Color value);
	void SetDefaultBGColor(SDL_Color value);
private:
  SDL_Color defaultForegroundColor = {255, 255, 255, 255};
  SDL_Color defaultBackgroundColor = {0, 0, 0, 255};
  TerminalFont *font;
  SDL_Texture *canvas;
  std::valarray<TerminalGlyph> buffer;
  int width, height;
};
