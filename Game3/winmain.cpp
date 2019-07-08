#include "Framework/Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game* game = new Game(hInstance, nCmdShow);
	if (game->GameInit())
	{
		game->GameRun();
	}
	game->GameEnd();
	delete game;
	return 0;
}