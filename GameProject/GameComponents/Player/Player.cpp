#include "Player.h"

Player* Player::instance = NULL;

Player::Player()
{
	animations[Running] = new Animation("Resources/simon/run_18_32.png", 2, 1, 2);
	animations[Standing] = new Animation("Resources/simon/stand_18_32.png", 1, 1, 1);
	currentAnim = animations[Standing];
	posX = 16;
	posY = 416;
}

Player * Player::GetInstance()
{
	if (instance == NULL)
	{
		instance = new Player();
		instance->ChangeState(new PlayerStandingState());
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

void Player::ChangeState(PlayerState * newState)
{
	delete currentState;
	currentState = newState;
	currentAnim = animations[currentState->GetState()];
}

void Player::CheckCollision(std::unordered_set<GameObject*> colliableObjects)
{
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
	currentState->HandleKeyboard(keys);
}
