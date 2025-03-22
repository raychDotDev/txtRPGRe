#pragma once
#include "Codepages.hpp"
#include <map>
#include <tuple>
#include <SDL2/SDL.h>

class TerminalFont {
public:
  SDL_Texture *atlas;
  TerminalFont(SDL_Renderer *context, const char *path, int atlasWidth,
               int atlasHeight, int tileWidth, int tileHeight);
  ~TerminalFont();
	std::map<int, std::tuple<float, float>> glyphs;
	int GetAtlasWidth();
	int GetAtlasHeight();
	int GetTileWidth();
	int GetTileHeight();
private:
  int atlasWidth, atlasHeight;
  int tileWidth, tileHeight;
};
