#include "Player.h"

Player::Player()
{
	standingAnim = new Animation("Resources/simon/stand_18_32.png", 1, 1, 1);
	runningAnim = new Animation("Resources/simon/run_18_32.png", 2, 1, 2);
	sittingAnim = new Animation("Resources/simon/sitting_16_25.png", 1, 1, 1);
	downFightingAnim = new Animation("Resources/simon/down_fight_32_32.png", 3, 1, 3);
	standFightingAnim = new Animation("Resources/simon/fightthrow_32_32.png", 3, 1, 3);
	upStairFightingAnim = new Animation("Resources/simon/onstairup_fight_32_32.png", 3, 1, 3);
	downStairFightingAnim = new Animation("Resources/simon/onstairdown_fight_32_32.png", 3, 1, 3);
	upStairAnim = new Animation("Resources/simon/upstair_16_32.png", 2, 1, 2);
	downStairAnim = new Animation("Resources/simon/downstair_16_32.png", 2, 1, 2);
	whip = NULL;

	Tag = GameObjectTypes::Simon;

	onGround = onStair = false;
	curAnim = standingAnim;
	playerData = new PlayerData();
	playerData->player = this;
	vX = 0;
	vY = 0;
	SetState(new PlayerStandingState(playerData));
	allowJump = true;
	weaponPos = { 0,0,0 };
	isCollideStairBottom = false;
	isEnable = true;
	allowMoveLeft = allowMoveRight = true;

	hp = 20;
}

Player::~Player()
{
	Memory::SafeDelete(standingAnim);
	Memory::SafeDelete(runningAnim);
	Memory::SafeDelete(sittingAnim);
	Memory::SafeDelete(standFightingAnim);
	Memory::SafeDelete(downFightingAnim);
	Memory::SafeDelete(upStairFightingAnim);
	Memory::SafeDelete(downStairFightingAnim);

	Memory::SafeDelete(whip);
}

RECT Player::GetBound()
{
	RECT rect;
	rect.left = posX - curAnim->GetWidth() / 2;
	rect.top = posY - curAnim->GetHeight() / 2;
	rect.right = rect.left + curAnim->GetWidth();
	rect.bottom = rect.top + curAnim->GetHeight();
	return rect;
}

void Player::Update(float deltaTime)
{
	if (!isEnable)
		invicibleTime += deltaTime;
	else
		invicibleTime = 0;
	if (invicibleTime > 3)
		isEnable = true;
	if (!isStopAnim)
	{
		curAnim->Update(deltaTime);
	}
	if (whip != NULL)
	{
		whip->SetPlayerPosition(this->GetPosition());
		whip->Update(deltaTime);
	}

	if (playerData->state)
	{
		playerData->state->Update(deltaTime);
	}
	DynamicObject::Update(deltaTime);
	
}


void Player::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	curAnim->FlipHorizontal(curReverse);
	curAnim->Draw(position, cameraPosition);
	if (whip != NULL)
	{
		whip->SetReverse(curReverse);
		int x = 1;
		if (curReverse && weaponPos.x > 0)
			x = -1;
		else
			x = 1;
		weaponPos.x *= x;
		whip->Draw(D3DXVECTOR3(posX, posY, 0) + weaponPos, cameraPosition);
	}
}

void Player::SetState(PlayerState * newState)
{
	delete this->playerData->state;

	this->playerData->state = newState;

	ChangeAnimation(newState->GetState());

	curState = newState->GetState();
}

void Player::SetState(PlayerState::StateName stateName)
{
	switch (stateName)
	{
	case PlayerState::Standing:
		SetState(new PlayerStandingState(playerData));
		break;
	case PlayerState::Running:
		SetState(new PlayerRunningState(playerData));
		break;
	case PlayerState::Falling:
		SetState(new PlayerFallingState(playerData));
		break;
	case PlayerState::Jumping:
		SetState(new PlayerJumpingState(playerData));
		break;
	case PlayerState::Fighting:
		SetState(new PlayerFightingState(playerData));
		break;
	case PlayerState::Sitting:
		SetState(new PlayerSitdownState(playerData));
		break;
	case PlayerState::UpStair:
		SetState(new PlayerUpStairState(playerData));
		break;
	case PlayerState::DownStair:
		SetState(new PlayerDownStairState(playerData));
		break;
	}
}

PlayerState::StateName Player::GetState()
{
	return curState;
}

PlayerState::StateName Player::GetLastState()
{
	return lastState;
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
		if (!keys[VK_UP] && curState == PlayerState::UpStair || !keys[VK_DOWN] && curState == PlayerState::DownStair)
		{
			isStopAnim = true;
			RECT r = { 16,0,32,32 };
			//stop anim
			curAnim->SetSourceRect(r);
		}
		else
		{
			isStopAnim = false;
		}
		
	}
}

void Player::OnKeyPressed(int key)
{
	if (key == VK_SPACE)
	{
		if (allowJump && onGround || curState == PlayerState::Standing) //cho phep nhay khi dang o tren mat dat
		{	
			if (curState == PlayerState::Running || curState == PlayerState::Standing)
			{
				onGround = false;
				allowJump = false;
				this->SetState(PlayerState::Jumping);
			}
		}
	}

}

void Player::OnKeyUp(int key)
{
	if (key == VK_SPACE)
		allowJump = true;
	if (key == VK_UP)
		allowUpStair = false;
	if (key == VK_DOWN)
		allowDownStair = false;
}

void Player::SetReverse(bool flag)
{
	curReverse = flag;
}

bool Player::GetCurrentReverse()
{
	return curReverse;
}

Animation * Player::GetCurrentAnimation()
{
	return curAnim;
}

GameObject * Player::GetWeaponObject()
{
	return whip;
}

PlayerData * Player::GetPlayerData()
{
	return playerData;
}

void Player::ChangeAnimation(PlayerState::StateName state)
{
	switch (state)
	{
	case PlayerState::Running:
		curAnim = runningAnim;
		break;
	case PlayerState::Standing:
		curAnim = standingAnim;
		Memory::SafeDelete(whip);
		break;
	case PlayerState::Fighting:
		lastState = GetState();
		//Set current Anim
		switch (lastState)
		{
		case PlayerState::Standing:
			curAnim = standFightingAnim;
			break;
		case PlayerState::Sitting:
			curAnim = downFightingAnim;
			break;
		case PlayerState::UpStair: 
			curAnim = upStairFightingAnim;
			break;
		case PlayerState::DownStair:
			curAnim = downStairFightingAnim;
			break;
		}
		//init whip
		whip = new Whip();
		
		break;
	case PlayerState::Sitting:
		curAnim = sittingAnim;
		break;
	case PlayerState::Falling:
		curAnim = standingAnim;
		break;
	case PlayerState::Jumping:
		curAnim = sittingAnim;
		break;
	case PlayerState::UpStair:
		curAnim = upStairAnim;
		break;
	case PlayerState::DownStair:
		curAnim = downStairAnim;
		break;
	}
	curAnim->ResetAnim();
	this->width = curAnim->GetWidth();
	this->height = curAnim->GetHeight();
}

void Player::JumpBack()
{
	isEnable = false;
	this->SetVy(PLAYER_MIN_JUMP_VELOCITY);
	MoveDirection dir = this->GetDirection();
	if (dir == Player::MoveDirection::MoveToLeft)
		this->SetVx(50);
	else
		this->SetVx(50*-1);
	hp--;
	this->SetState(PlayerState::Jumping);
}

Box Player::getBox()
{
	Box b;
	D3DXVECTOR3 v = curAnim->GetPosition();
	b.left = GetPosition().x - GetWidth() / 2;
	b.top = GetPosition().y - GetHeight();
	b.right = b.left + GetWidth();
	b.bottom = GetPosition().y;
	b.vx = GetVx();
	b.vy = GetVy();
	return b;
}

void Player::OnCollision(GameObject * entity, float deltaTime)
{
	playerData->state->OnCollision(entity, deltaTime);
}