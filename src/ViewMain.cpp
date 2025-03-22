#include "ViewMain.hpp"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Game.hpp"

ViewMain::ViewMain() {}
ViewMain::~ViewMain() {}

void ViewMain::Load(void *context) {}

void ViewMain::Unload(void *context) {}

void ViewMain::Update(void *context, SDL_Event event, float dt) {}

void ViewMain::Draw(void *context, Terminal *terminal) {
	Game* con = (Game*)context;
}
