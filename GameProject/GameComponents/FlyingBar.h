#pragma once
#include "GameObject.h"
#include <vector>
#include <math.h>
#include <unordered_set>
#include <fstream>
#include <string>
#include "../GameComponents/Player/Player.h"
#include "../Framework/Grid.h"
#include "../Framework/Animation.h"
#include "../Framework/Collision.h"

#define PI 3.14f

class FlyingBar :public GameObject
{
private:
	Animation*	flameLeft, *flameRight, *flameDown1, *flameDown2;
	Sprite*		barsprite;
	bool		isFlying;
	DWORD		startime;
	D3DXVECTOR3	startPoint;
	bool		isGoingUp, isGoingToRight;
	float		angle;
	D3DXVECTOR3	lowPos, highPos, leftPos, rightPos;
public:
	D3DXVECTOR3 endPoint;
	float		type;
	//type == 0 for go straight, type == 1 go round
	FlyingBar(float posX, float posY, float endX, float endY, float type);
	
	static void InsertFromFile(int level);
	void OnCollision(GameObject* object, float deltaTime = 0);
	RECT GetBound();
	BoundingBox GetBoundingBox();
	void Update(float deltaTime);
	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	void Draw();
	void Release();
};
