#pragma once
#include "Weapon.h"
#include "../../../Framework/Collision.h"
#include "../../Player/Player.h"


class DMBarrel : public Weapon
{
	float savedvX;
	D3DXVECTOR3		startingPoint;
public:
	bool isVisible = false;
	//posX, posY is the left, top of weapon
	DMBarrel(float posX, float posY, bool direction);

	void StartFall();
	void StartWait(float posX, float posY, bool isReverse);
	void OnCollision(GameObject* object, float deltaTime = 0);
	RECT GetBound();
	BoundingBox GetBoundingBox();
	void Update(float deltaTime);
	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//Draw at its position
	void Draw();
	void Release();
};
