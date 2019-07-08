#pragma once
#include "DynamicObject.h"
class Door : public DynamicObject
{
public:
	Door();
	Door(int x, int y);
	~Door();

	virtual void Update(float deltaTime);
	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//player position to enable animation
	virtual void SetPlayerPosition(D3DXVECTOR3 player);
	virtual Box getBox();
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	//only used to invoke Opening the Door
	virtual void OpeningTheDoor(int flag);
private:
	void SetFrame(int index);
	bool opening, closing;
	int indexFrame[4] = { 0,1,2,3};
	int count;
};
