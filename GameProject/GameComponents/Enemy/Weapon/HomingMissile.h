#pragma once
#include "Weapon.h"
#include "../../../Framework/Collision.h"
#include "../../Player/Player.h"

enum HomingState
{
	down,
	downleft,
	downright,
	downleftup,
	downrightup
};

class HomingMissile : public Weapon
{
	Animation*		currentAnim;
	std::unordered_map<HomingState, Animation*> animations;
	HomingState	currentState, prevState;
	D3DXVECTOR3		startingPoint;
public:
	//posX, posY is the left, top of weapon
	HomingMissile(float posX, float posY, int direction);

	float Dot(float ax, float ay, float bx, float by);
	float perpDot(float ax, float ay, float bx, float by);
	void CalculateHoming();
	void OnCollision(GameObject* object, float deltaTime = 0);
	void Update(float deltaTime);
	RECT GetBound();
	BoundingBox GetBoundingBox();
	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	void Draw();
	void Release();
	void SetState(HomingState state);
};
