#pragma once
#include "../GameObject.h"
#include "../../Framework/Sprite.h"
#include "../../Framework/Collision.h"
#include "../../Framework/Grid.h"
#include <unordered_set>
#include "PowerStone.h"
#include "Five.h"
#include "Energy.h"
#include "KeyCrystals.h"
#include "OneUp.h"
#include "Rescue.h"
#include "BigHeart.h"

class ItemsContainer :public GameObject
{
private:
	Sprite** sprites;
	Sprite* curSprite;
	bool	isStartFallingItems;
	DWORD	startTime;
	std::unordered_set<GameObject*> listDrawItems;
	
	bool isSpawnExit;	// is exit spawned
public:
	std::unordered_set<GameObject*> listItems;
	int hasExit;
	std::string strItems; //save string items 

	ItemsContainer(int left, int top, int width, int height, std::string items,int hasExit = 0);
	ItemsContainer(RECT rect);

	static void InsertFromFile(int level);
	void OnCollision(GameObject* object, float deltaTime = 0);
	void Update(float deltaTime);
	//Draw to its left-top position
	void Draw();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) override;
	virtual BoundingBox GetBoundingBox() override;
	void Release();
};
