#pragma once
#include "Weapon.h"
#include "../../../Framework/Collision.h"

enum WizardBulletType
{
	HorizontalBullet,	//ngang
	VerticalBullet,		//doc
	BigVerticalBullet	//bullet when entering boss map
};

class WizardBullet : public Weapon
{
	WizardBulletType		bulletType;
	D3DXVECTOR3		startingPoint;
	DWORD			startTime;
	int				nBigBullet;	//number of big vertical bullet in boss map
public:
	//posX, posY is the left, top of weapon
	WizardBullet(float posX, float posY, WizardBulletType type);

	void OnCollision(GameObject* object, float deltaTime = 0);
	RECT GetBound();
	BoundingBox GetBoundingBox();
	void Update(float deltaTime);
	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//Draw at its position
	void Draw();
	void Release();
};
