#pragma once
#include <SDL2/SDL.h>

class View {
public:
  View() {}
  ~View() {}
	virtual void Load(SDL_Renderer *context) {}
	virtual void Unload(SDL_Renderer *context) {}
	virtual void Update(SDL_Event event, float dt) {}
	virtual void Draw(SDL_Renderer *context) {}
};
