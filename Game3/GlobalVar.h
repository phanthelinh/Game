#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <dinput.h>


#define GAME_TITLE				"Castle Vania"
#define CLASS_NAME				"Game"
#define FRAME_RATE				60.0f
#define FRAME_PER_SEC			1.0f/FRAME_RATE
#define KEYBOARD_BUFFER_SIZE	1024

namespace Memory
{
	template <class T> void SafeDelete(T& t)
	{
		if (t)
		{
			delete t;
			t = nullptr;
		}
	}

	template <class T> void SafeDeleteArr(T&t)
	{
		if (t)
		{
			delete[] t;
			t = nullptr;
		}
	}

	template <class T> void SafeRelease(T&t)
	{
		if (t)
		{
			t->Release();
			t = nullptr;
		}
	}
}

class GlobalVar
{
private:
	static HWND g_HWND;
	static HINSTANCE g_hInstance;
	static int g_nCmdShow;

	static LPDIRECT3D9 g_d3d;
	static LPDIRECT3DDEVICE9 g_device;
	static LPD3DXSPRITE g_sprite;
	static LPDIRECT3DSURFACE9 g_backbuffer;
	
	static UINT g_width, g_height; //Screen width, screen height
	static bool	g_isWindowed;

	static LPDIRECTINPUT8 g_directInput;
	static LPDIRECTINPUTDEVICE8 g_directKeyboard;

	static int g_worldMapWidth, g_worldMapHeight;
	static int g_gameUIArea;
public:
	GlobalVar();
	~GlobalVar();

	static void ReleaseAll();

	static HWND GetHWND();
	static void SetHWND(HWND hwnd);

	static void ShowCreatedWindow();
	static void ShowCreatedWindow(HWND hwnd);

	static int GetnCmdShow();
	static void SetnCmdShow(int nCmdShow);

	static HINSTANCE GetHInstance();
	static void SetHInstance(HINSTANCE hInstance);

	static LPDIRECT3D9 GetDirect3D();
	static void SetDirect3D(LPDIRECT3D9 d3d);

	static LPDIRECT3DDEVICE9 GetDevice();
	static void SetDevice(LPDIRECT3DDEVICE9 device);

	static LPD3DXSPRITE GetSprite();
	static void SetSprite(LPD3DXSPRITE sprite);

	static LPDIRECT3DSURFACE9 GetBackBuffer();
	static void SetBackBuffer(LPDIRECT3DSURFACE9 backbuffer);

	static UINT GetScreenWidth();
	static void SetScreenWidth(UINT w);

	static UINT GetScreenHeight();
	static void SetScreenHeight(UINT h);

	static bool GetIsWindowed();
	static void SetIsWindowed(bool isWindowed);

	static LPDIRECTINPUT8 GetDirectInput();
	static void SetDirectInput(LPDIRECTINPUT8 _di);

	static LPDIRECTINPUTDEVICE8 GetDirectInputDevice();
	static void SetDirectInputDevice(LPDIRECTINPUTDEVICE8 _didev);

	static LPDIRECT3DSURFACE9 LoadSurfaceFromFile(const char * filePath);

	static int GetWorldMapWidth();
	static void SetWorldMapWidth(int x);

	static int GeWorldMapHeight();
	static void SetWorldMapHeight(int y);

	static int GetGameUIArea();
};

