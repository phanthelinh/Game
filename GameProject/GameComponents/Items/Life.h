#pragma once
#include "../GameObject.h"
#include "../../Framework/Sprite.h"

class Life :public GameObject
{
private:
	Sprite*		life;
public:
	Life(int left, int top, int width, int height);
	Life(RECT rect);
	void OnCollision(GameObject* object, float deltaTime = 0);
	void Update(float deltaTime);
	//Draw to its left-top position
	void Draw();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) override;
	virtual BoundingBox GetBoundingBox() override;
	void Release();
};