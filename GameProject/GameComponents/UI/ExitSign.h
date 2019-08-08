#pragma once
#include "../GameObject.h"
#include "../../Framework/Sprite.h"

class ExitSign :public GameObject
{
private:
	D3DXVECTOR3 startingPos; //starting point of the shield
	
public:
	D3DXVECTOR3 _translationToPlayer;
	bool isVisible;
	D3DXVECTOR3 playerPos;
	float		playerVy;
	int			shieldPower;
	ExitSign();

	void Draw();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) override;
	void Update(float deltaTime);
	BoundingBox GetBoundingBox();
};