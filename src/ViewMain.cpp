#include "ViewMain.hpp"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

ViewMain::ViewMain() {}
ViewMain::~ViewMain() {}

void ViewMain::Load(SDL_Renderer *context) {
  image = IMG_LoadTexture(context, "assets/font.png");
  canvas = SDL_CreateTexture(context, SDL_PIXELFORMAT_RGBA8888,
                             SDL_TEXTUREACCESS_TARGET, 256, 256);
}

void ViewMain::Unload(SDL_Renderer *context) { 
	SDL_DestroyTexture(image); 
	SDL_DestroyTexture(canvas);
}

void ViewMain::Update(SDL_Event event, float dt) {}

void ViewMain::Draw(SDL_Renderer *context) {
	SDL_SetRenderTarget(context, canvas);
  SDL_RenderCopy(context, image, NULL, NULL);
	SDL_SetRenderTarget(context, NULL);
	auto dest = (SDL_Rect){0,0,400,400};
	SDL_RenderCopy(context, canvas, NULL, &dest);
}
