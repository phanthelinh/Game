#pragma once
#include "../DynamicObject.h"
#include "../Items/LargeHeart.h"
class Ghouls : public DynamicObject
{
public:
	Ghouls();
	Ghouls(int x, int y);
	~Ghouls();

	virtual void Update(float deltaTime);
	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	//Get box for collision detection
	virtual Box getBox();
	//get items after this object was destroyed
	virtual GameObject* GetItems();
private:
	bool isLeft;
	GameObject* heart;
	D3DXVECTOR3 hittedPosition;
};
