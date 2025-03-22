#include "SDL2/SDL.h"
#include "Game.hpp"
#include "ViewMain.hpp"
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  Game game("Game!", 800, 600);
  ViewMain view = ViewMain();
  game.SetView(&view);
  game.Run();
	return 0;
}
