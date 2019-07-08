#include "Camera.h"



Camera::Camera()
{
	camPosition.x = GlobalVar::GetScreenWidth() / 2;
	camPosition.y = (GlobalVar::GetScreenHeight() - GlobalVar::GetGameUIArea())/2;
	camWidth = GlobalVar::GetScreenWidth();
	camHeight = GlobalVar::GetScreenHeight() - GlobalVar::GetGameUIArea();
}

Camera::Camera(int x, int y, int width, int height)
{
	camWidth = width;
	camHeight = height;
	camPosition.x = x;
	camPosition.y = y;
	camPosition.z = 0;
}


Camera::~Camera()
{
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


int Camera::GetCameraWidth()
{
	return camWidth;
}

int Camera::GetCameraHeight()
{
	return camHeight;
}

D3DXVECTOR3 Camera::GetCameraPosition()
{
	return camPosition;
}

D3DXVECTOR2 Camera::GetTranslateCamera()
{
	//translate = screen center - camera position
	return D3DXVECTOR2(GlobalVar::GetScreenWidth() / 2 - camPosition.x, (GlobalVar::GetScreenHeight() / 2 + GlobalVar::GetGameUIArea()/2) - camPosition.y);
}

void Camera::SetCameraPosition(D3DXVECTOR3 pos)
{
	camPosition = pos;
}

void Camera::SetCameraPosition(int x, int y)
{
	SetCameraPosition(D3DXVECTOR3(x, y, 0));
}
