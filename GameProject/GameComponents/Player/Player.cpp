#include "Player.h"

Player* Player::instance = NULL;

Player::Player()
{
	animations[Running] = new Animation("Resources/simon/run_18_32.png", 2, 1, 2);
	animations[Standing] = new Animation("Resources/simon/stand_18_32.png", 1, 1, 1);
	animations[Jumping] = new Animation("Resources/simon/Jumping.png", 1, 1, 1);
	animations[Falling] = new Animation("Resources/simon/Jumping.png", 1, 1, 1);
	animations[Spinning] = new Animation("Resources/simon/Spinning.png", 2, 1, 2);
	animations[Kicking] = new Animation("Resources/simon/Kicking.png", 4, 1, 1);
	currentAnim = animations[Standing];
	LastKeyState[Z] = false;
	LastKeyState[X] = false;
	LastKeyState[C] = false;
	LastKeyState[LEFT] = false;
	LastKeyState[RIGHT] = false;
	LastPressTime[Z] = LastPressTime[X] = LastPressTime[C] 
		= LastPressTime[LEFT] = LastPressTime[RIGHT] = 0.0f;
	KeyHoldTime[Z] = KeyHoldTime[X] = KeyHoldTime[C]
		= KeyHoldTime[LEFT] = KeyHoldTime[RIGHT] = 0.0f;
	posX = 16;
	posY = 416;
}

Player * Player::GetInstance()
{
	if (instance == NULL)
	{
		instance = new Player();
		instance->ChangeState(Standing);
	}
	return instance;
}

void Player::Update(float deltaTime)
{
	CAMERA->UpdateCamera(D3DXVECTOR3(PLAYER->posX, PLAYER->posY, 0));
	currentState->Update(deltaTime);
	currentAnim->Update(deltaTime);
}

void Player::Draw()
{
	currentAnim->_isFlipHor = isReverse;
	currentAnim->Draw(posX, posY);
}

//cach viet nay khong phu hop viet viec phai kiem tra state truoc do la gi
//void Player::ChangeState(PlayerState * newState)
//{
//	delete currentState;
//	currentState = newState;
//	currentAnim = animations[currentState->GetState()];
//}
void Player::ChangeState(StateName stateName)
{
	if (currentState != nullptr)
		PreviousState = currentState->GetState();
	PlayerState* newState = nullptr;
	switch (stateName)
	{
	case Standing:
		newState = new PlayerStandingState();
		break;
	case Jumping:
		newState = new PlayerJumpingState();
		break;
	case Falling:
		newState = new PlayerFallingState();
		break;
	case Kicking:
		newState = new PlayerKickingState();
		break;
	case Running:
		newState = new PlayerRunningState();
		break;
	case Spinning:
		newState = new PlayerSpinningState();
		break;
	}
	delete currentState;
	currentState = newState;
	currentAnim = animations[currentState->GetState()];
}

void Player::CheckCollision(std::unordered_set<GameObject*> colliableObjects)
{
}

void Player::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	currentState->HandleKeyboard(keys, deltaTime);
}
