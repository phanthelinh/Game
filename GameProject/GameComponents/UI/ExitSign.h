#pragma once
#include "../GameObject.h"
#include "../../Framework/Sprite.h"
#include "../../Framework/Animation.h"

class ExitSign :public GameObject
{
private:
	D3DXVECTOR3 startingPos; //starting point of the shield
	Animation*		currAnim;
public:
	bool isVisible;
	ExitSign();

	void Draw();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) override;
	void Update(float deltaTime);
	BoundingBox GetBoundingBox();
};