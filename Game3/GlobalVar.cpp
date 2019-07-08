#include "GlobalVar.h"


//Initialize
HWND GlobalVar::g_HWND = NULL;
HINSTANCE GlobalVar::g_hInstance = NULL;
int GlobalVar::g_nCmdShow = SW_SHOWDEFAULT;

LPDIRECT3D9 GlobalVar::g_d3d = NULL;
LPDIRECT3DDEVICE9 GlobalVar::g_device = NULL;
LPD3DXSPRITE GlobalVar::g_sprite = NULL;
LPDIRECT3DSURFACE9 GlobalVar::g_backbuffer = NULL;


UINT GlobalVar::g_width = 256;
UINT GlobalVar::g_height = 240; //load map 192 + 48 (UI)
bool GlobalVar::g_isWindowed = true;

LPDIRECTINPUT8 GlobalVar::g_directInput = NULL;
LPDIRECTINPUTDEVICE8 GlobalVar::g_directKeyboard = NULL;

int GlobalVar::g_worldMapWidth = 0;
int GlobalVar::g_worldMapHeight = 0;

int GlobalVar::g_gameUIArea = 48;

GlobalVar::GlobalVar()
{
}


GlobalVar::~GlobalVar()
{
}

void GlobalVar::ReleaseAll()
{
	Memory::SafeRelease(g_directKeyboard);
	Memory::SafeRelease(g_directInput);
	Memory::SafeRelease(g_sprite);
	Memory::SafeRelease(g_backbuffer);
	Memory::SafeRelease(g_device);
	Memory::SafeRelease(g_d3d);
}

HWND GlobalVar::GetHWND()
{
	if (g_HWND != NULL)
		return g_HWND;
	else
	{
		return NULL;
	}
}

void GlobalVar::SetHWND(HWND hwnd)
{
	if (hwnd != NULL)
		g_HWND = hwnd;
}

void GlobalVar::ShowCreatedWindow()
{
	if (g_HWND != NULL)
		ShowWindow(g_HWND, g_nCmdShow);
}

void GlobalVar::ShowCreatedWindow(HWND hwnd)
{
	if (hwnd != NULL)
		ShowWindow(hwnd, g_nCmdShow);
}

int GlobalVar::GetnCmdShow()
{
	return g_nCmdShow;
}

void GlobalVar::SetnCmdShow(int nCmdShow)
{
	g_nCmdShow = nCmdShow;
}

HINSTANCE GlobalVar::GetHInstance()
{
	if (g_hInstance != NULL)
		return g_hInstance;
	return NULL;
}

void GlobalVar::SetHInstance(HINSTANCE hInstance)
{
	if (hInstance != NULL)
		g_hInstance = hInstance;
}

LPDIRECT3D9 GlobalVar::GetDirect3D()
{
	if (g_d3d != NULL)
		return g_d3d;
	return NULL;
}

void GlobalVar::SetDirect3D(LPDIRECT3D9 d3d)
{
	if (d3d != NULL)
		g_d3d = d3d;
}

LPDIRECT3DDEVICE9 GlobalVar::GetDevice()
{
	if (g_device != NULL)
		return g_device;
	return NULL;
}

void GlobalVar::SetDevice(LPDIRECT3DDEVICE9 device)
{
	if (device != NULL)
		g_device = device;
}

LPD3DXSPRITE GlobalVar::GetSprite()
{
	if (g_sprite != NULL)
		return g_sprite;
	return LPD3DXSPRITE();
}

void GlobalVar::SetSprite(LPD3DXSPRITE sprite)
{
	if (sprite != NULL)
		g_sprite = sprite;
}

LPDIRECT3DSURFACE9 GlobalVar::GetBackBuffer()
{
	return g_backbuffer;
}

void GlobalVar::SetBackBuffer(LPDIRECT3DSURFACE9 backbuffer)
{
	g_backbuffer = backbuffer;
}


UINT GlobalVar::GetScreenWidth()
{
	return g_width;
}

void GlobalVar::SetScreenWidth(UINT w)
{
	if (w != 0)
		g_width = w;
}

UINT GlobalVar::GetScreenHeight()
{
	return g_height;
}

void GlobalVar::SetScreenHeight(UINT h)
{
	if (h != 0)
		g_height = h;
}

bool GlobalVar::GetIsWindowed()
{
	return g_isWindowed;
}

void GlobalVar::SetIsWindowed(bool isWindowed)
{
	g_isWindowed = isWindowed;
}

LPDIRECTINPUT8 GlobalVar::GetDirectInput()
{
	return g_directInput;
}

void GlobalVar::SetDirectInput(LPDIRECTINPUT8 _di)
{
	if (_di != NULL)
		g_directInput = _di;
}

LPDIRECTINPUTDEVICE8 GlobalVar::GetDirectInputDevice()
{
	return g_directKeyboard;
}

void GlobalVar::SetDirectInputDevice(LPDIRECTINPUTDEVICE8 _didev)
{
	if (_didev != NULL)
		g_directKeyboard = _didev;
}

LPDIRECT3DSURFACE9 GlobalVar::LoadSurfaceFromFile(const char* filePath)
{
	LPDIRECT3DSURFACE9 surface = NULL;
	D3DXIMAGE_INFO info;
	if (FAILED(D3DXGetImageInfoFromFile(filePath, &info)))
	{
		MessageBox(NULL, "Cannot get map image infomation", "Error", MB_OK);
		return NULL;
	}
	GlobalVar::GetDevice()->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL
	);
	if (FAILED(D3DXLoadSurfaceFromFile(
		surface,
		NULL,
		NULL,
		filePath,
		NULL,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		NULL
	)))
	{
		MessageBox(NULL, "Cannot load map surface from file", "Error", MB_OK);
		return NULL;
	}
	return surface;
}

int GlobalVar::GetWorldMapWidth()
{
	return g_worldMapWidth;
}

void GlobalVar::SetWorldMapWidth(int x)
{
	g_worldMapWidth = x;
}

int GlobalVar::GeWorldMapHeight()
{
	return g_worldMapHeight;
}

void GlobalVar::SetWorldMapHeight(int y)
{
	g_worldMapHeight = y;
}

int GlobalVar::GetGameUIArea()
{
	return g_gameUIArea;
}
