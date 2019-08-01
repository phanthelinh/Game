#pragma once
#include "Global.h"
#include "../GameComponents/GameObject.h"
#define CAMERA Camera::GetInstance()

class Camera
{
private:
	static Camera* instance;
public:
	

	int camWidth,	camHeight;
	D3DXVECTOR3		camPosition; //position is the center of camera view
	bool			isFollowY;

	Camera();
	Camera(int x, int y, int width, int height);
	~Camera();
	static Camera* GetInstance();
	RECT GetBound();
	BoundingBox GetBoundingBox();
	D3DXVECTOR2 GetTranslateCamera();
	void UpdateCamera(D3DXVECTOR3 playerPosition);
};
