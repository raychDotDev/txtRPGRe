#include "Game.hpp"
#include "ViewMain.hpp"

int wmain() {
  Game game("Game!", 800, 600);
  ViewMain view = ViewMain();
  game.SetView(&view);
  game.Run();
}
