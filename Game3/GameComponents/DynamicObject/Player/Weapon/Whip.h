#pragma once
#include "../../DynamicObject.h"
#include "../../../../Framework/UIDrawing.h"
class Whip : public DynamicObject
{
public:
	Whip();
	Whip(int x, int y);
	~Whip();
	
	void SetReverse(bool flag);

	virtual void Update(float deltaTime);
	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//player position to enable animation
	virtual void SetPlayerPosition(D3DXVECTOR3 player);
	virtual Box getBox();
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
private:
	void ResetFrame(int index);

	D3DXVECTOR3 playerPos;
	bool reverse;
	int currentIndex;
	bool isFinish;
};
