#pragma once
#include "Terminal.hpp"
#include <SDL2/SDL.h>

class View {
public:
  View() {}
  ~View() {}
  virtual void Load(void *context) {}
  virtual void Unload(void *context) {}
  virtual void Update(void *context, SDL_Event event, float dt) {}
  virtual void Draw(void *context, Terminal *terminal) {}
};
