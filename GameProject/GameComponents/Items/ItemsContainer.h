#pragma once
#include "../GameObject.h"
#include "../../Framework/Sprite.h"
#include "../../Framework/Collision.h"
#include <unordered_set>

class ItemsContainer :public GameObject
{
private:
	Sprite** sprites;
	Sprite* curSprite;
	bool	isStartFallingItems;
	DWORD	startTime;
public:
	std::unordered_set<GameObject*> listItems;

	ItemsContainer(int left, int top, int width, int height);
	ItemsContainer(RECT rect);

	void ExecuteCollision(GameObject* object);
	void Update(float deltaTime);
	//Draw to its left-top position
	void Draw();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) override;
	virtual BoundingBox GetBoundingBox() override;
};
