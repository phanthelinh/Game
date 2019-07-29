#pragma once
#include "../../GameObject.h"
#include "../../../Framework/Animation.h"
#include <unordered_map>
#include <unordered_set>

class Enemy;
class Weapon : public GameObject
{
protected:
	static Enemy*	currEnemy;
	Animation*		currAnim;
public:
	float weaponDamage;

	Weapon();
	//posX, posY is the left, top of weapon
	Weapon(float posX, float posY, float width, float height);
	Weapon(RECT r);

	virtual void OnCollision(GameObject* object, float deltaTime = 0);
	virtual RECT GetBound();
	virtual BoundingBox GetBoundingBox();
	virtual void Update(float deltaTime);
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) {};
	//Draw at its position
	virtual void Draw();
	virtual void Release();
};