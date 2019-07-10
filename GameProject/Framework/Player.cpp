#include "Player.h"

Player::Player()
{
	playerData = new PlayerData();
	playerData->player = this;
	vX = 0;
	vY = 0;

	allowJump = true;
}

Player::~Player()
{

}

RECT Player::GetBound()
{
	RECT rect;
	rect.left = posX - curAnim->_frameWidth / 2;
	rect.top = posY - curAnim->_frameHeight / 2;
	rect.right = rect.left + curAnim->_frameWidth;
	rect.bottom = rect.top + curAnim->_frameHeight;
	return rect;
}

void Player::Update(float deltaTime)
{
	curAnim->Update(deltaTime);
	if (playerData->state)
	{
		playerData->state->Update(deltaTime);
	}
	GameObject::Update(deltaTime);
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{

}

void Player::SetState(PlayerState* newState)
{
	delete this->playerData->state;

	this->playerData->state = newState;

	ChangeAnimation(newState->GetState());

	curState = newState->GetState();
}

PlayerState::StateName Player::GetState()
{
	return curState;
}

Player::MoveDirection Player::GetDirection()
{
	if (this->vX > 0)
	{
		return MoveDirection::MoveToRight;
	}
	else if (this->vX < 0)
	{
		return MoveDirection::MoveToLeft;
	}

	return MoveDirection::None;
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
	if (playerData->state)
	{
		playerData->state->HandleKeyboard(keys);
	}
}

void Player::OnKeyPressed(int key)
{
	if (key == VK_SPACE)
	{
		if (allowJump)
		{
			if (curState == PlayerState::Running || curState == PlayerState::Standing)
			{
				//this->SetState(new PlayerJumpingState(this->playerData));
			}

			allowJump = false;
		}
	}
}

void Player::OnKeyUp(int key)
{
	if (key == VK_SPACE)
		allowJump = true;
}

void Player::SetReverse(bool flag)
{
	curReverse = flag;
}

void Player::ChangeAnimation(PlayerState::StateName state)
{
	switch (state)
	{
	case PlayerState::Die:
		break;
	case PlayerState::Falling:
		break;
	case PlayerState::Jumping:
		break;
	case PlayerState::Running:
		curAnim = runningAnim;
		break;
	case PlayerState::Standing:
		curAnim = standingAnim;
		break;

	}
	this->width = curAnim->_frameWidth;
	this->height = curAnim->_frameHeight;
}
