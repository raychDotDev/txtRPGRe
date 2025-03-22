#include "Game.hpp"
#include "Logger.hpp"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"
#include <SDL2/SDL.h>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

Game::Game(std::string title, int width, int height) {
  SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  log = Logger();
  SDL_SetWindowTitle(window, title.c_str());
  running = true;
  frameTimer = SDL_GetTicks();
  SetTargetFps(60);
  ter = new Terminal(renderer, 80, 24);
}

Game::~Game() {
  delete ter;
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Game::Run() {
  while (running) {
    float dt = (SDL_GetTicks() - frameTimer) * 0.001f;
    Update(dt);
    fps = 1.0f / dt;
    SDL_SetRenderDrawColor(renderer, 255, 150, 150, 255);
    SDL_RenderClear(renderer);
    Draw();
    SDL_RenderPresent(renderer);

    frameTimer = SDL_GetTicks();
    if (GetTargetFps() > 0) {
      SDL_Delay((Uint32)1000 / GetTargetFps());
    }
  }
}

void Game::Update(float dt) {
  SDL_PollEvent(&updateEvent);

  if (updateEvent.window.event == SDL_WINDOWEVENT_CLOSE ||
      (updateEvent.key.keysym.sym == SDLK_ESCAPE &&
       updateEvent.key.state == SDL_PRESSED)) {
    Stop();
  }
  if (this->view != nullptr) {
    this->view->Update(updateEvent, dt);
  }
}

void Game::Draw() {
  ter->Display(renderer);
  // if (this->view != nullptr) {
  //   this->view->Draw(renderer);
  // }
}

Uint32 Game::GetFps() { return fps; }
Uint32 Game::GetTargetFps() { return targetFps; }
void Game::SetTargetFps(Uint32 value) { targetFps = value; }

void Game::Stop() { running = false; }

void Game::SetView(View *view) {
  if (this->view != nullptr) {
    this->view->Unload(renderer);
  }
  this->view = nullptr;
  this->view = view;
  if (this->view != nullptr) {
    this->view->Load(renderer);
  }
}
