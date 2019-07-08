#pragma once
#include "../DynamicObject.h"
#include "../Items/SmallHeart.h"
class Candle : public DynamicObject
{
public:
	Candle();
	Candle(int x, int y);
	~Candle();

	virtual void Update(float deltaTime);
	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());

	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	//get items after this object was destroyed
	virtual GameObject* GetItems();
private:
	D3DXVECTOR3 hittedPosition;
	GameObject * heart;
};