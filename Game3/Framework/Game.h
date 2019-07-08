#pragma once
#include <time.h>
#include "../GlobalVar.h"
#include "../Scene/SceneManager.h"
#include "../Scene/DemoScene.h"
#include "../Scene/TitleScene.h"
class Game
{
private:
	int InitWindow();
	int InitDirectX();
	int InitKeyboard();
	HINSTANCE _hInstance;
	int _nCmdShow;
	static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual void GameUpdate(float deltaTime);
	virtual void GameDraw();
public:
	Game(HINSTANCE hInstance, int nCmdShow);
	~Game();

	int GameInit();
	void GameRun();
	void GameEnd();
};

