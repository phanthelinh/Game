#include "Global.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene4.h"

class Game
{
private:
	int InitWindow();
	int InitDirectX();
	int InitKeyboard();
	int	_nCmdShow;

	static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual void GameUpdate(float deltaTime);
	virtual void GameDraw();
public:
	Game(HINSTANCE hInstance, int nCmdShow);

	bool GameInit();
	void GameRun();
	void GameEnd();
};