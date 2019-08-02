#include "Player.h"

Player* Player::instance = NULL;

Player::Player()
{
	tag = Tag::Captain;

	animations[Running] = new Animation("Resources/player/player_run_128_48.png", 4, 1, 4, true, 0.65);
	animations[Standing] = new Animation("Resources/player/player_stand_32_48.png", 1, 1, 1);
	animations[Sitting] = new Animation("Resources/player/player_sit_32_32.png", 1, 1, 1);
	animations[Jumping] = new Animation("Resources/player/Jumping.png", 1, 1, 1);
	animations[Falling] = new Animation("Resources/player/Jumping.png", 1, 1, 1);
	animations[Kicking] = new Animation("Resources/player/Kicking.png", 1, 1, 1);
	animations[Spinning] = new Animation("Resources/player/Spinning.png", 2, 1, 2, true);
	animations[OnShield] = new Animation("Resources/player/OnShield.png", 1, 1, 1);
	animations[Dashing] = new Animation("Resources/player/Dashing.png", 3, 1, 3, false, 0.5);
	animations[WaterStand] = new Animation("Resources/player/PlayerWaterStand.png", 1, 1, 1);
	animations[WaterRun] = new Animation("Resources/player/PlayerWaterRun.png", 2, 1, 2, true);
	animations[Hurt] = new Animation("Resources/player/PlayerHurt2.png", 6, 1, 2, false, 0.25f);

	animations[Attacking_Shield] = new Animation("Resources/player/player_standthrow_96_32.png", 2, 1, 2, false);
	animations[Attacking_StandBump] = animations[Attacking] = new Animation("Resources/player/player_standbump_96_48.png", 2, 1, 2, false);
	animations[Attacking_SitBump] = new Animation("Resources/player/player_sitbump_80_28.png", 2, 1, 2, false);

	animations[LookUpward] = new Animation("Resources/player/player_lookup_32_48.png", 1, 1, 1, false);
	animations[Die] = new Animation("Resources/player/player_died_64_32.png", 2, 1, 2, false, 0.95);
	animations[Injuring] = new Animation("Resources/player/Injuring.png", 2, 1, 2, true, 0.95);
	currentAnim = animations[Falling];
	allow[Attacking_Shield] = true;
	LastKeyState[Z] = false;
	LastKeyState[X] = false;
	LastKeyState[C] = false;
	LastKeyState[LEFT] = false;
	LastKeyState[RIGHT] = false;
	isReverse = true;
	isOnGround = false;
	isImmu = false;
	shield = new Shield();
	shieldFlying = false;

	health = 10;
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
	CAMERA->UpdateCamera(D3DXVECTOR3(posX, posY, 0));
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
	//
	//assign position for shield
	//
	if (!shieldFlying)
	{
		shield->SetPosition(GetPosition());
		shield->SetTranslationToPlayer(isReverse, shield->curState, currentAnim->_curIndex);
		if (shield->curState == ShieldState::Flying && currentAnim->_isFinished)
		{
			shieldFlying = true;

		}
	}
	else
	{
		shield->playerVy = vY;
		shield->playerPos = GetPosition();
		shield->Update(deltaTime);
		//check collision for catch shield
		auto colRes = COLLISION->SweptAABB(shield->GetBoundingBox(), GetBoundingBox());
		if (colRes.isCollide)
		{
			shield->posX += shield->vX*colRes.entryTime;
			shield->posY += shield->vY*colRes.entryTime;
			shieldFlying = false;
			shield->SetState(Normal);
		}
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
	case Dashing:
		newState = new PlayerDashingState();
		break;
	case OnShield:
		newState = new PlayerOnShieldState();
		break;
	case Hurt:
		newState = new PlayerHurt();
		break;
	case WaterRun:
		newState = new PlayerWaterRun();
		break;
	case WaterStand:
		newState = new PlayerWaterStand();
		break;
	case Die:
		newState = new PlayeDiedState();
		break;
	case Injuring:
		newState = new PlayerInjuringState();
		break;
	case Attacking:
	case Attacking_Shield:
	case Attacking_SitBump:
	case Attacking_StandBump:

		newState = new PlayerAttackingState();
		break;
	}
	delete currentState;
	currentState = newState;
	if (currentState->GetState() != Attacking)
	{
		currentAnim = animations[currentState->GetState()];
		width = currentAnim->_frameWidth;
		height = currentAnim->_frameHeight;
		currentAnim->ResetAnim();
	}
}

void Player::CheckCollision(std::unordered_set<GameObject*> lstCollideable, float deltaTime)
{
	for (auto entity = lstCollideable.begin(); entity != lstCollideable.end(); ++entity)
	{
		currentState->OnCollision((*entity), deltaTime);
	}
}

void Player::OnCollision(GameObject * object, float deltaTime)
{
	currentState->OnCollision(object, deltaTime);
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
		if (allow[Attacking_Shield] && currentState->GetState() != Jumping && currentState->GetState() != Falling && 
			currentState->GetState() != Spinning)
		{
			allow[Attacking_Shield] = false;
			ChangeState(Attacking);
		}
		break;
	case VK_RETURN:
		ChangeState(StateName::Die);
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
		if (currentState->GetState() != Jumping && currentState->GetState() != Falling && 
			currentState->GetState() != Spinning && currentState->GetState() != Die)
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

void Player::Release()
{
	if (animations.size() > 0)
	{
		for (auto anim : animations)
		{
			if (&anim.second != NULL && anim.first != Attacking_StandBump)
			{
				delete anim.second;
			}
		}
		animations.clear();
		
	}
	if (allow.size() > 0)
	{
		allow.clear();
	}
	if (shield != nullptr)
		delete shield;
	LastKeyState.clear();
}

void Player::JumpBack()
{
	this->vY = -0.01f;

	if (vX > 0)
		this->vX = 2.0f;
	else
		this->vX = -2.0f;
	health--;
	ChangeState(StateName::Jumping);
}
