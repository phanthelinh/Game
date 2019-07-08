#pragma once
#include "Global.h"

class Camera
{
public:
	int camWidth, camHeight;
	D3DXVECTOR3 camPosition; //position is the center of camera view

	Camera();
	Camera(int x, int y, int width, int height);
	~Camera();
	RECT GetBound();
	D3DXVECTOR2 GetTranslateCamera();
	void UpdateCamera(D3DXVECTOR3 playerPosition);
};
