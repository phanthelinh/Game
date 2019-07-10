#pragma once
#include "Animation.h"
#include "PlayerData.h"
#include "PlayerState.h"
#include "../GameComponents/GameObject.h"


#define PLAYER_MAX_JUMP_VELOCITY		280.0f //van toc nhay lon nhat
#define PLAYER_MIN_JUMP_VELOCITY		-280.0f //van toc nhay thap nhat
#define PLAYER_MAX_RUNNING_SPEED		180.0f //toc do chay nhanh nhat cua player
#define PLAYER_BOTTOM_RANGE_FALLING		8.0f // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong

class Player
	:public GameObject
{
public:
	Player();
	~Player();

	enum MoveDirection
	{
		MoveToLeft,
		MoveToRight,
		None
	};
	RECT GetBound();

	void Update(float deltaTime);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void SetState(PlayerState* newState);
	PlayerState::StateName GetState();

	MoveDirection GetDirection();
	void HandleKeyboard(std::map<int, bool> keys);

	void OnKeyPressed(int key);

	void OnKeyUp(int key);

	//true thi se lat nguoc anh theo truc y
	void SetReverse(bool flag);
private:
	void ChangeAnimation(PlayerState::StateName state);

	PlayerState::StateName curState;
	PlayerData* playerData;
	bool allowJump;
	bool curReverse;
	Animation* curAnim, * standingAnim, * runningAnim;
};
