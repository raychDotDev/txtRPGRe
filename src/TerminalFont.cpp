#include "TerminalFont.hpp"
#include "Codepages.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <tuple>

TerminalFont::TerminalFont(SDL_Renderer *context, const char *path,
                           const int atlasWidth, const int atlasHeight,
                           const int tileWidth, const int tileHeight) {
  this->atlasWidth = atlasWidth;
  this->atlasHeight = atlasHeight;
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;
	
	atlas = IMG_LoadTexture(context, path);

  glyphs = std::map<int, std::tuple<float, float>>();

  for (int i = 0; i < atlasHeight/tileHeight; i++) {
    for (int j = 0; j < atlasWidth/tileWidth; j++) {
      glyphs[Codepage::CODEPAGE_866[i * (atlasWidth/tileWidth) + j]] =
          std::make_tuple(j*tileWidth, i*tileHeight);
    }
  }
}

TerminalFont::~TerminalFont() { SDL_DestroyTexture(atlas); }

int TerminalFont::GetAtlasWidth() { return atlasWidth; }
int TerminalFont::GetAtlasHeight() { return atlasHeight; }
int TerminalFont::GetTileWidth() { return tileWidth; }
int TerminalFont::GetTileHeight() { return tileHeight; }
