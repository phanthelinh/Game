#pragma once
#include "Enemy.h"
#include "Weapon/Bullet.h"
#include "../Effect/Explode.h"
#include <fstream>

enum TankState
{
	TankStateBottom,
	TankStateRightBottom,
	TankStateRight,
	TankStateRightTop,
	TankStateTop,
	TankStateLeftTop,
	TankStateLeft,
	TankStateLeftBottom
};

class Tank : public Enemy
{
private:
	std::unordered_map<TankState, Sprite*>	sprites;
	std::vector<GameObject*> bullets;
	Sprite*		curSprite;
	int			curNumSprite;
	bool		onChangingState;
	DWORD		timeCount;

	TankState GetStateNameFromNumber(int num);
public:
	int	initState;
	//x, y is the left-top corner
	Tank(float x, float y, int type);

	static void InsertFromFile(int level);

	void ChangeTankState();

	void OnCollision(GameObject* object, float deltaTime = 0);
	void Update(float deltaTime);
	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//Draw at its position
	void Draw();
	RECT GetBound();
	BoundingBox GetBoundingBox();
	void Release();
};