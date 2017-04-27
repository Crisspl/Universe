#include "Game.h"

int main(int, char **)
{
   Game::initSystems();
   Game::get().run();
   fhl::ResMgr::clear();

   return 0;
}
