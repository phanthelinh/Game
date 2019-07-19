#include "Player.h"

Player* Player::instance = NULL;

Player::Player()
{
	animations[Running] = new Animation("Resources/player/player_run_128_48.png", 4, 1, 4, true, 0.65);
	animations[Standing] = new Animation("Resources/player/player_stand_32_48.png", 1, 1, 1);
	animations[Sitting] = new Animation("Resources/player/player_sit_32_32.png", 1, 1, 1);
	animations[Jumping] = new Animation("Resources/simon/Jumping.png", 1, 1, 1);
	animations[Falling] = new Animation("Resources/simon/Jumping.png", 1, 1, 1);
	animations[Kicking] = new Animation("Resources/simon/Kicking.png", 4, 1, 1);
	animations[Spinning] = new Animation("Resources/simon/Spinning.png", 2, 1, 2);

	animations[Attacking_Shield] = animations[Attacking] = new Animation("Resources/player/player_standthrow_96_32.png", 2, 1, 2, false);
	animations[Attacking_StandBump] = new Animation("Resources/player/player_standbump_96_48.png", 2, 1, 2, false);
	animations[Attacking_SitBump] = new Animation("Resources/player/player_sitbump_80_32.png", 2, 1, 2, false);

	animations[LookUpward] = new Animation("Resources/player/player_lookup_32_48.png", 1, 1, 1, false);
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
	isReverse = true;
	shield = new Shield();
	shieldFlying = false;
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
	//player to end of map
	if (posX <= 16)
	{
		SetPosition(D3DXVECTOR3(16, posY, 0));
	}
	else if (posX >= GLOBAL->g_WorldMapWidth - 16)
	{
		SetPosition(D3DXVECTOR3(GLOBAL->g_WorldMapWidth - 16, posY, 0));
	}
	//assign position for shield
	if (shield->curState == ShieldState::Flying) //shield flying is true when start attack shiled state
	{
		if (currentAnim->_isFinished) //if sprite throw is finish, start to throw shield
		{
			shieldFlying = true;
		}
		if (!shieldFlying) //shield is still with player, at sprite no 0 and 1
		{
			shield->SetPosition(GetPosition());
			shield->SetTranslationToPlayer(isReverse, ShieldState::Flying, currentAnim->_curIndex);
		}
		else
		{
			
			auto colRes = COLLISION->SweptAABB(shield->GetBoundingBox(), GetBoundingBox());
			
			if (colRes.isCollide)
			{
				startcheck = true;
			}
			else
			{
				shield->Update(deltaTime);
			}
			if (startcheck)
			{
				if (IsCollide(shield->GetBound()))
				{
					//
					//shield->SetPosition(D3DXVECTOR3(shield->posX + shield->vX*colRes.entryTime, shield->posY + shield->vY*colRes.entryTime, 0));
					shieldFlying = false;
					startcheck = false;
					shield->SetState(ShieldState::Normal);
				}
				else
				{
					shield->Update(deltaTime);
				}
				
			}
		}	
	}
	else
	{
		//set shield position to player position
		shield->SetPosition(GetPosition());
		shield->SetTranslationToPlayer(isReverse, shield->curState);
	}
}

void Player::Draw()
{
	currentAnim->_isFlipHor = isReverse;
	if (!shieldFlying)
	{
		shield->isReverse = isReverse;
	}
	currentAnim->Draw(posX, posY);
	shield->Draw();
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
	case Sitting:
		newState = new PlayerSittingState();
		break;
	case Attacking:
		newState = new PlayerAttackingState();
		break;
	}
	delete currentState;
	currentState = newState;
	currentAnim = animations[currentState->GetState()];
	width = currentAnim->_frameWidth;
	height = currentAnim->_frameHeight;
	currentAnim->ResetAnim();
}

void Player::CheckCollision(std::unordered_set<GameObject*> colliableObjects)
{
}

void Player::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	currentState->HandleKeyboard(keys, deltaTime);
}

void Player::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case VK_Z:
		if (allow[Attacking_Shield] && currentState->GetState() != Jumping && currentState->GetState() != Falling && currentState->GetState() != Spinning)
		{
			allow[Attacking_Shield] = false;
			ChangeState(Attacking);
		}
		break;
	default:
		break;
	}
}

void Player::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case VK_Z:
		if (currentState->GetState() != Jumping && currentState->GetState() != Falling && currentState->GetState() != Spinning)
			allow[Attacking_Shield] = true;
		break;
	case VK_UP:
		shield->SetState(ShieldState::Normal);
		break;
	default:
		break;
	}
}

BoundingBox Player::GetBoundingBox()
{
	BoundingBox b;
	b.left = posX - currentAnim->_frameWidth / 2;
	b.top = posY - currentAnim->_frameHeight / 2;
	b.right = b.left + currentAnim->_frameWidth;
	b.bottom = b.top + currentAnim->_frameHeight;
	b.vX = vX;
	b.vY = vY;
	return b;
}
