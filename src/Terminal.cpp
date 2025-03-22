#include "Terminal.hpp"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include <string>
#include <tuple>
#include <valarray>

Terminal::Terminal(SDL_Renderer *context, int width, int height) {
  font = new TerminalFont(context, "assets/font.png", 128, 144, 8, 8);
  canvas = SDL_CreateTexture(
      context, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
      width * font->GetTileWidth(), height * font->GetTileHeight());
  this->width = width;
  this->height = height;
  buffer = std::valarray<TerminalGlyph>(0);
  buffer.resize(width * height,
                (TerminalGlyph){(int)L' ', (SDL_Color){255, 255, 255, 255},
                                (SDL_Color){0, 0, 0, 255}});
}

void Terminal::SetGlyph(int x, int y, TerminalGlyph g) {
  auto glyph = &buffer[y * width + x];
  glyph->character = g.character;
  glyph->fg = g.fg;
  glyph->bg = g.bg;
}

void Terminal::Print(int x, int y, std::wstring text) {
  if (y >= height || y < 0 || x >= width || x + (int)text.size() < 0)
    return;

  for (int i = 0; i < (int)text.size(); i++) {
    auto glyph =
        (TerminalGlyph){(int)text[i], {255, 255, 255, 255}, {0, 0, 0, 255}};
    SetGlyph(x + i, y, glyph);
  }
}

void Terminal::Display(SDL_Renderer *context) {
  int tileWidth = font->GetTileWidth(), tileHeight = font->GetTileHeight();
  SDL_SetRenderTarget(context, canvas);

  auto atlas_bglyph_pos = font->glyphs[0x2588];
  SDL_Rect bsrc = {(int)std::get<0>(atlas_bglyph_pos),
                   (int)std::get<1>(atlas_bglyph_pos), tileWidth, tileHeight};

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      auto g = &buffer[i * width + j];
      auto atlas_glyph_pos = font->glyphs[g->character];
      SDL_Rect src = {(int)std::get<0>(atlas_glyph_pos),
                      (int)std::get<1>(atlas_glyph_pos), tileWidth, tileHeight};
      SDL_FRect dest = {(float)(j * tileWidth), (float)(i * tileHeight),
                        (float)tileWidth, (float)tileHeight};

      SDL_SetTextureColorMod(font->atlas, g->bg.r, g->bg.g, g->bg.b);
      SDL_SetTextureAlphaMod(font->atlas, g->bg.a);
      SDL_RenderCopyF(context, font->atlas, &bsrc, &dest);

      SDL_SetTextureColorMod(font->atlas, g->fg.r, g->fg.g, g->fg.b);
      SDL_SetTextureAlphaMod(font->atlas, g->fg.a);
      SDL_RenderCopyF(context, font->atlas, &src, &dest);
    }
  }

  SDL_SetRenderTarget(context, NULL);
  SDL_RenderCopy(context, canvas, NULL, NULL);
}

Terminal::~Terminal() {
  SDL_DestroyTexture(canvas);
  delete font;
}
