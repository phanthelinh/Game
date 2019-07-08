#pragma once
#include "../GlobalVar.h"
class Camera
{
private:
	int camWidth, camHeight;
	D3DXVECTOR3 camPosition; //position is the center of camera view
public:
	Camera();
	Camera(int x , int y, int width , int height);
	~Camera();
	RECT GetBound();
	int GetCameraWidth();
	int GetCameraHeight();
	D3DXVECTOR3 GetCameraPosition();
	D3DXVECTOR2 GetTranslateCamera();
	void SetCameraPosition(D3DXVECTOR3 pos);
	void SetCameraPosition(int x, int y);
};

