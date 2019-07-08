#pragma once
#include <d3dx9.h>
#include <iostream>
#include <string>

using namespace std;

#define FRAME_RATE 20

class Font
{
private:
	LPD3DXFONT	_font;
	RECT		_fontPosition;
	void _render(const char* text_, float x_, float y_, D3DCOLOR color_);
	DWORD _localTime;
	int _frameRate;
	bool _isDrawAnimation;

	void _initialize();

public:
	Font(LPDIRECT3DDEVICE9 d3ddev_, int size_, int screenWidth_, int screenHeight_);
	~Font();
	void updateAnimation();
	void render(const char* text_, float x_, float y_);
	void render(int number_, float x_, float y_);
	void render(float number_, float x_, float y_);
	void renderAnimation(char* text_, float x_, float y_, int deltaTime_);
	void renderAnimation(int number_, float x_, float y_, int deltaTime_);
	void onLost();
};