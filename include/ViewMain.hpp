#pragma once
#include "SDL2/SDL_surface.h"
#include "View.hpp"
#include <SDL2/SDL.h>

class ViewMain : public View {
private:
public:
  ViewMain();
  ~ViewMain();
	void Load(void *context) override;
	void Unload(void *context) override;
  void Update(void*context,SDL_Event event, float dt) override;
  void Draw(void*context,Terminal *terminal) override;
};
