#pragma once
#include "../GameObject.h"
#include "../../Framework/Sprite.h"
#include "../../Framework/Collision.h"
#include "../../Framework/Grid.h"
#include <unordered_set>
#include "PowerStone.h"
class ItemsContainer :public GameObject
{
private:
	Sprite** sprites;
	Sprite* curSprite;
	bool	isStartFallingItems;
	DWORD	startTime;
	std::unordered_set<GameObject*> listDrawItems;
	int		maxItemsNum;
public:
	std::unordered_set<GameObject*> listItems;

	ItemsContainer(int left, int top, int width, int height, bool hasExit = false);
	ItemsContainer(RECT rect);

	void OnCollision(GameObject* object, float deltaTime = 0);
	void Update(float deltaTime);
	//Draw to its left-top position
	void Draw();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) override;
	virtual BoundingBox GetBoundingBox() override;
	void Release();
};
