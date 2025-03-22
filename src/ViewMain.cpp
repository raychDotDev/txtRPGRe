#include "ViewMain.hpp"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

ViewMain::ViewMain() {}
ViewMain::~ViewMain() {}

void ViewMain::Load(void *context) {}

void ViewMain::Unload(void *context) {}

void ViewMain::Update(void *context, SDL_Event event, float dt) {}

void ViewMain::Draw(void *context, Terminal *terminal) {
  terminal->Print(0, 0, L"ё\x6001пта))\x6002\x25A0");
}
