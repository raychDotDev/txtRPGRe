#pragma once
#include "Logger.hpp"
#include "Terminal.hpp"
#include "View.hpp"
#include <string>
#include <SDL2/SDL.h>

class Game {
	public:
		Game(std::string title, int width, int height);
		~Game();
		void Run();
		void Stop();
		void SetTargetFps(Uint32 value);
		unsigned int GetTargetFps();
		Uint32 GetFps();
		void SetView(View*view);
	private:
		Terminal *ter;
		Logger log;
		View *view;
		Uint32 frameTimer;
		float fps = 0;
		bool running;
		void Update(float dt);
		void Draw();
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Event updateEvent;
		Uint32 targetFps = 60;
};
