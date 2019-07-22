#include "Camera.h"

Camera* Camera::instance = NULL;

Camera::Camera()
{
	camPosition.x = GLOBAL->g_ScreenWidth / 2;
	camPosition.y = (GLOBAL->g_ScreenHeight / 2 + GLOBAL->g_GameUIArea / 2);
	camPosition.z = 0;
	camWidth = GLOBAL->g_ScreenWidth;
	camHeight = GLOBAL->g_ScreenHeight - GLOBAL->g_GameUIArea;
	isFollowY = false;
}

Camera::Camera(int x, int y, int width, int height)
{
	camWidth = width;
	camHeight = height;
	camPosition.x = x;
	camPosition.y = y;
	camPosition.z = 0;
	isFollowY = false;
}


Camera::~Camera()
{
}

Camera* Camera::GetInstance()
{
	if (instance)
		return instance;
	else 
	{
		instance = new Camera();
		return instance;
	}
}

RECT Camera::GetBound()
{
	RECT bound;

	bound.left = camPosition.x - camWidth / 2;
	bound.right = bound.left + camWidth;
	bound.top = camPosition.y - camHeight / 2;
	bound.bottom = bound.top + camHeight;

	return bound;
}

D3DXVECTOR2 Camera::GetTranslateCamera()
{
	return D3DXVECTOR2(GLOBAL->g_ScreenWidth / 2 - camPosition.x, (GLOBAL->g_ScreenHeight / 2 + GLOBAL->g_GameUIArea / 2) - camPosition.y);
}

void Camera::UpdateCamera(D3DXVECTOR3 playerPosition)
{
	if (playerPosition.x > camPosition.x)
	{
		//translate camera position to player
		camPosition.x += playerPosition.x - camPosition.x;
	}
	if (playerPosition.x < camPosition.x)
	{
		//translate camera position to player
		camPosition.x -= camPosition.x - playerPosition.x;
	}
	if (camPosition.x + GLOBAL->g_ScreenWidth / 2 >= GLOBAL->g_WorldMapWidth)
	{
		//Set camera position to end of map
		camPosition.x = GLOBAL->g_WorldMapWidth - GLOBAL->g_ScreenWidth / 2;
	}
	if (camPosition.x - GLOBAL->g_ScreenWidth / 2 < 0)
	{
		//Set camera position to the first
		camPosition.x = GLOBAL->g_ScreenWidth / 2;
	}
	//
	//set for y
	//
	if (!isFollowY)
	{
		if (camPosition.y + GLOBAL->g_ScreenHeight / 2 >= GLOBAL->g_WorldMapHeight)
		{
			camPosition.y = GLOBAL->g_WorldMapHeight - GLOBAL->g_ScreenHeight / 2;
		}
		if (camPosition.y < 0)
		{
			camPosition.y = GLOBAL->g_ScreenHeight / 2;
		}
		return;
	}
	if (playerPosition.y > camPosition.y)
	{
		camPosition.y += playerPosition.y - camPosition.y;
	}
	if (playerPosition.y < camPosition.y)
	{
		camPosition.y -= camPosition.y - playerPosition.y;
	}
	if (camPosition.y + GLOBAL->g_ScreenHeight / 2 >= GLOBAL->g_WorldMapHeight)
	{
		camPosition.y = GLOBAL->g_WorldMapHeight - GLOBAL->g_ScreenHeight / 2;
	}
	if (camPosition.y < 0)
	{
		camPosition.y = GLOBAL->g_ScreenHeight / 2;
	}
}
