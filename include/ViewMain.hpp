#pragma once
#include "SDL2/SDL_surface.h"
#include "View.hpp"
#include <SDL2/SDL.h>

class ViewMain : public View {
private:
  SDL_Texture *image;

public:
  ViewMain();
  ~ViewMain();
	void Load(SDL_Renderer * context) override;
	void Unload(SDL_Renderer * context) override;
  void Update(SDL_Event event, float dt) override;
  void Draw(SDL_Renderer *context) override;
};
