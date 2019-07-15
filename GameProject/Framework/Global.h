#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>


#define CLASS_NAME				"Game Project Class"
#define GAME_TITLE				"Game Project"
#define GLOBAL					Global::GetInstance()
#define KEYBOARD_BUFFER_SIZE	1024
#define FRAME_PER_SEC			60.0f
#define FRAME_TIME_MILLISEC		100.0f/FRAME_PER_SEC
#define VK_X					0x58
#define VK_Z					0x5a
class Global
{
private:
	static Global*		_instance;
public:
	static Global*		GetInstance();
	
	HINSTANCE			g_hInstance = NULL;			//hInstance of the game
	HWND				g_HWND;				//HWND of the game
	bool				g_IsWindowed = true;		//true if windowed
	int					g_ScreenWidth = 256;
	int					g_ScreenHeight = 240;
	LPDIRECT3DDEVICE9	g_DirectDevice = NULL;		//Direct X device
	LPD3DXSPRITE		g_SpriteHandler = NULL;		//Direct X Sprite handler
	LPDIRECT3DSURFACE9	g_BackBuffer = NULL;		//Back buffer
	int					g_GameUIArea = 0;				//game ui start position
	int					g_WorldMapWidth;
	int					g_WorldMapHeight;
};