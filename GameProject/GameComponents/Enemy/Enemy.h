#pragma once
#include "../GameObject.h"
#include "../Player/Player.h"
#include "Weapon/Weapon.h"

enum EnemyStateName
{
	EnemyStand,
	EnemyRun,
	EnemySit,
	EnemyAttack,
	EnemyDie,
	EnemyJump
};

enum EnemySubTag
{
	DomestoTag,
	RunningManTag,
	WizardBossTag,
	DMBossTag,
	TankTag,
	GigiTag
};

class Enemy: public GameObject
{
public:
	Animation*		currentAnim;
	float			maxHealth, currHealth;
	Weapon*			enemyWeapon;
	float			point;		//score when defeated
	EnemySubTag		enemySubTag;
	Enemy();
	//posX, posY is the left, top of enemies
	Enemy(float posX, float posY, float width, float height);
	Enemy(RECT r);

	virtual void OnCollision(GameObject* object, float deltaTime = 0);
	virtual RECT GetBound();
	virtual BoundingBox GetBoundingBox();
	virtual void Update(float deltaTime);
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) {};
	//Draw at its position
	virtual void Draw();
	virtual void Release();
};