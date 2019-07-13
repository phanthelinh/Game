#include "Game.h"
#include <time.h>
#include <dinput.h>

int Game::InitWindow()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = GLOBAL->g_hInstance;
	wc.lpfnWndProc = WinProc;
	wc.lpszClassName = CLASS_NAME;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);
	DWORD style;
	if (GLOBAL->g_IsWindowed) {
		style = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		style = WS_EX_TOPMOST | WS_POPUP;
	}

	HWND hwnd = CreateWindow(
		CLASS_NAME,
		GAME_TITLE,
		style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		GLOBAL->g_ScreenWidth,
		GLOBAL->g_ScreenHeight,
		NULL, NULL,
		GLOBAL->g_hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Failed to create Window", "Error", MB_OK);
		return 0;
	}
	GLOBAL->g_HWND = hwnd;
	ShowWindow(hwnd, _nCmdShow);
	return 1;
}

int Game::InitDirectX()
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d != NULL)
	{
		//GlobalVar::SetDirect3D(d3d);
	}
	else
	{
		MessageBox(NULL, "Failed to create Direct3D", "Error", MB_OK);
		return 0;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = GLOBAL->g_ScreenWidth;
	d3dpp.BackBufferHeight = GLOBAL->g_ScreenHeight;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//D3DFMT_A8B8G8R8;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GLOBAL->g_HWND;
	d3dpp.Windowed = GLOBAL->g_IsWindowed;


	LPDIRECT3DDEVICE9 dev;
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		GLOBAL->g_HWND,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&dev
	);
	if (dev == NULL)
	{
		MessageBox(NULL, "Failed to create Direct3D Device", "Error", MB_OK);
		return 0;
	}
	GLOBAL->g_DirectDevice = dev;
	
	//Create Sprite
	LPD3DXSPRITE sprite;
	if (FAILED(D3DXCreateSprite(GLOBAL->g_DirectDevice, &sprite)))
	{
		MessageBox(NULL, "Cannot create sprite", "Error", MB_OK);
		return 0;
	}
	GLOBAL->g_SpriteHandler = sprite;
	//Get back buffer
	LPDIRECT3DSURFACE9 backbuffer;
	if (FAILED(dev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer)))
	{
		MessageBox(NULL, "Cannot create Back Buffer", "Error", MB_OK);
		return 0;
	}
	GLOBAL->g_BackBuffer = backbuffer;
	return 1;
}

int Game::InitKeyboard()
{
	LPDIRECTINPUT8 _di;
	HRESULT hr = DirectInput8Create
	(
		GLOBAL->g_hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&_di, NULL
	);
	if (hr != DI_OK)
	{
		MessageBox(NULL, "Cannot create Direct Input", "Error", MB_OK);
		return 0;
	}
	//GlobalVar::SetDirectInput(_di);

	LPDIRECTINPUTDEVICE8 _Keyboard;
	hr = _di->CreateDevice(GUID_SysKeyboard, &_Keyboard, NULL);
	if (hr != DI_OK)
	{
		MessageBox(NULL, "Cannot create Direct Input Device", "Error", MB_OK);
		return 0;
	}
	//GlobalVar::SetDirectInputDevice(_Keyboard);

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = _Keyboard->SetDataFormat(&c_dfDIKeyboard);

	hr = _Keyboard->SetCooperativeLevel(GLOBAL->g_HWND, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = _Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK)
	{
		MessageBox(NULL, "Cannot set property for Direct Input Device", "Error", MB_OK);
		return 0;
	}
	hr = _Keyboard->Acquire();
	if (hr != DI_OK)
	{
		MessageBox(NULL, "Cannot acquire Direct Input Device", "Error", MB_OK);
		return 0;
	}

	return 1;
}

LRESULT Game::WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		SCENES->GetCurrentScene()->OnKeyDown(wParam);
		break;
	case WM_KEYUP:
		SCENES->GetCurrentScene()->OnKeyUp(wParam);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

void Game::GameUpdate(float deltaTime)
{
	SCENES->GetCurrentScene()->Update(deltaTime);
}

void Game::GameDraw()
{
	auto scene =SCENES->GetCurrentScene();
	auto device = GLOBAL->g_DirectDevice;
	auto spriteHandler = GLOBAL->g_SpriteHandler;
	//device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	device->ColorFill(GLOBAL->g_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	device->BeginScene();
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	
	scene->Draw();

	spriteHandler->End();
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}

Game::Game(HINSTANCE hInstance, int nCmdShow)
{
	Global::GetInstance()->g_hInstance = hInstance;
	this->_nCmdShow = nCmdShow;
}

bool Game::GameInit()
{
	if (InitWindow())
	{
		if (!InitDirectX())
			return false;
		else
		{
			if (!InitKeyboard())
				return false;
		}
	}
	else
	{
		return false;
	}
	SceneManager::GetInstance()->ReplaceScene(new DemoScene());
	return true;
}

void Game::GameRun()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	srand(time(NULL));
	float previousTime = (float)GetTickCount();
	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		float currentTime = (float)GetTickCount();
		float deltaTime = (currentTime - previousTime); //milisecond
		
		if (deltaTime >= FRAME_TIME_MILLISEC)
		{
			deltaTime = max(deltaTime, FRAME_TIME_MILLISEC);
			
			GameUpdate(deltaTime/1000.0f);
			GameDraw();
			previousTime = currentTime;
		}
		else
		{
			Sleep(FRAME_TIME_MILLISEC - deltaTime);
		}
	}
}

void Game::GameEnd()
{

}
