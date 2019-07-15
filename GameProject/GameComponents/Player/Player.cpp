#include "Player.h"

Player* Player::instance = NULL;

Player::Player()
{
	animations[Running] = new Animation("Resources/player/player_run_128_48.png", 4, 1, 4);
	animations[Standing] = new Animation("Resources/player/player_stand_32_48.png", 1, 1, 1);
	animations[Attacking_Shield] = animations[Attacking] = new Animation("Resources/player/player_standthrow_96_32.png", 2, 1, 2, false);
	animations[Attacking_StandBump] = new Animation("Resources/player/player_standbump_96_48.png", 2, 1, 2, false, 0.01);
	
	currentAnim = animations[Standing];
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
		instance->ChangeState(new PlayerStandingState());
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
	if (shield->curState == ShieldState::Normal)
	{
		shield->SetPosition(GetPosition());
		shield->SetTranslationToPlayer(isReverse, ShieldState::Normal);
	}
	if (shield->curState == ShieldState::Flying)
	{
		if (!shieldFlying)
		{
			shield->SetPosition(GetPosition());
			shield->SetTranslationToPlayer(isReverse, ShieldState::Flying, currentAnim->_curIndex);
		}
		else
		{
			shield->Update(deltaTime);
			auto colRes = COLLISION->SweptAABB(shield->GetBoundingBox(), GetBoundingBox(), deltaTime);
			if (colRes.isCollide)
			{
				shieldFlying = false;
				shield->SetState(ShieldState::Normal);
			}
		}
		if (currentAnim->_isFinished)
		{
			shieldFlying = true;
		}
		
	}
}

void Player::Draw()
{
	currentAnim->_isFlipHor = shield->shield->_isFlipHor = isReverse;
	currentAnim->Draw(posX, posY);
	shield->Draw();
}

void Player::ChangeState(PlayerState * newState)
{
	delete currentState;
	currentState = newState;
	currentAnim = animations[currentState->GetState()];
	width = currentAnim->_frameWidth;
	height = currentAnim->_frameHeight;
}

void Player::CheckCollision(std::unordered_set<GameObject*> colliableObjects)
{
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
	currentState->HandleKeyboard(keys);
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
