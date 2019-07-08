#pragma once
#include "../DynamicObject.h"
#include "Bone.h"

#define ACCELERATE_X_SKELETON 100.0f

class Skeleton :public DynamicObject
{
public:
	Skeleton();
	Skeleton(int x, int y);
	~Skeleton();

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
	bool CheckAllInvisible();

	std::vector<Bone*> bone;
	int boneIndex;
	int count;
	float prevTime, timeForBone, timeBoneUpdate;
	bool isLeft;
	D3DXVECTOR3 playerPos;
	int animIndex;
	float accelerateX;
};

