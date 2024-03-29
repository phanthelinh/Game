#pragma once
#include "Weapon.h"
#include "../../../Framework/Collision.h"
#include "../../Player/Player.h"


class DMBullet : public Weapon
{
	D3DXVECTOR3		startingPoint;
public:
	//posX, posY is the left, top of weapon
	DMBullet(float posX, float posY, bool direction, float speedmultiplier = 1);

	void OnCollision(GameObject* object, float deltaTime = 0);
	RECT GetBound();
	BoundingBox GetBoundingBox();
	void Update(float deltaTime);
	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//Draw at its position
	void Draw();
	void Release();
};
