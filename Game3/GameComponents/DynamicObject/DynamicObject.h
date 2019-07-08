#pragma once
#include "../GameObject.h"
#include "../../Framework/Animation.h"

class DynamicObject
	:public GameObject
{
public:
	DynamicObject();
	DynamicObject(float x, float y);
	virtual ~DynamicObject();
	void GravityAffect(float deltaTime);

	virtual void SetVx(float vx);
	virtual float GetVx();
	virtual void AddVx(float vx);

	virtual void SetVy(float vy);
	virtual float GetVy();
	virtual void AddVy(float vy);

	virtual void Update(float deltaTime);
	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	
protected:
	float vX, vY;

	//angle from the ground, default by PI/3 radian = 60 degree
	float angle;
	//Animation to draw dynamic object
	Animation* animObject;
	//Anim to draw effect
	Animation * animHit, *animDeath;
	//check for it was hurted
	bool isHurted;
	//check for it was dead
	bool isDead;
private:
	float timeHit, timeDead;
};