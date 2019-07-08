#include "Fishmen.h"
#include <time.h>
#include <stdlib.h>

Fishmen::Fishmen()
{
}

Fishmen::Fishmen(int x, int y)
{
	posX = x;
	posY = y;
	SetVy(-250.0f);
	Tag = GameObjectTypes::FishmenObj;
	animObject = new Animation("Resources/enemies/fishmen_16_32.png", 3, 1, 3);
	currentIndex = 0;
	startBullet = startMoving = isLeft = onGround = false;
	bulletTime = 0;
	bullet = NULL;
}

Fishmen::~Fishmen()
{
}

void Fishmen::Update(float deltaTime)
{
	//update bullet was execute at DemoScene
	//
	float now = GetTickCount();
	if (!startBullet) //update frame 0 1
	{
		if (startMoving)
		{
			//update frame
			if (timePerFrame == 0)
				timePerFrame = now;
			if ((now - timePerFrame) / 1000.0f >= 0.1f)
			{
				SetFrame(currentIndex);
				currentIndex = (currentIndex + 1) % 2;
				timePerFrame = now;
			}
			//processing for velocity
			if (isLeft)
			{
				SetVx(-45.0f);
			}
			else
			{
				SetVx(45.0f);
			}
			//processing for left - right
			if (posX < playerPos.x - (rand() % 20 + 70))
			{
				isLeft = false;
				
			}
			if (posX > playerPos.x + (rand() % 20 + 70))
			{
				isLeft = true;
				
			}
			animObject->FlipHorizontal(!isLeft);
			//falling
			if (!onGround)
				SetVy(45.0f); 
			
		}
		else //set to frame 0, just initialize
		{
			SetFrame(0);
			if (!onGround)
			{
				AddVy(16.0f);
				if (GetVy() > 145.0f)
					SetVy(145.0f);
			}
		}
		//update
		DynamicObject::Update(deltaTime);
	}
	else //set frame 2,start to shoot
	{
		currentIndex = 2;
		SetFrame(currentIndex);
		currentIndex = (currentIndex + 1) % 3;
		startBullet = false;
	}
	//set up for bullet
	if (bulletTime == 0)
	{
		bulletTime = now;
	}
	if ((now - bulletTime) / 1000.0f >= 2.0f)
	{
		if (startMoving)
		{
			startBullet = true;
			if (bullet == NULL)
 				bullet = new Bullet(posX + 8, posY + 10, isLeft);
		}
		bulletTime = now;
	}
}

void Fishmen::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible)
	{
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	}
	if (bullet != NULL)
	{
		bullet->Draw(D3DXVECTOR3(), cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
		//out of screen
		if (bullet->GetPosition().x < cameraPosition.x - GlobalVar::GetScreenWidth() / 2 ||
			bullet->GetPosition().x > cameraPosition.x + GlobalVar::GetScreenWidth() / 2)
		{
			Memory::SafeDelete(bullet);
		}
	}
	//effect and items
	DynamicObject::Draw(hittedPosition, cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	if (heart != NULL)
	{
		heart->Draw(D3DXVECTOR3(), cameraPosition);
	}
}

void Fishmen::SetPlayerPosition(D3DXVECTOR3 player)
{
	playerPos = player;
}

Box Fishmen::getBox()
{
	Box b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + animObject->GetWidth();
	b.bottom = b.top + animObject->GetHeight();
	b.vx = GetVx();
	b.vy = GetVy();
	return b;
}

void Fishmen::OnCollision(GameObject * entity, float deltaTime)
{
	GameCollision * collision = new GameCollision();
	Box broadPhase = collision->getBroadPhaseRect(getBox(), deltaTime);

	if (collision->isCollide(broadPhase, entity->getBox()))
	{
		if (entity->Tag != GameObject::Ground && entity->Tag!=GameObject::WhipObj)
			return;

		float normalX = 0, normalY = 0;
		float collisionTime = collision->sweptAABB(getBox(), entity->getBox(), normalX, normalY);
		if (entity->Tag == GameObject::Ground)
		{
			if (collisionTime > 0 && collisionTime < 1)
			{
				if (normalY < 0)
				{
					AddPosition(0, GetVy()*collisionTime);
					SetPosition(GetPosition().x, entity->getBox().top - animObject->GetHeight());
					SetVy(0);
					startMoving = true;
					onGround = true;
				}
			}
			else
			{
				if (onGround && 
					(posX > entity->getBox().right || posX < entity->getBox().left || posY > entity->getBox().top) &&
					entity->getBox().bottom > this->getBox().bottom)
				{
					onGround = false;
				}
			}
		}
		else //whip cillision
		{
			isDead = true;
			isHurted = true;
			this->isVisible = false;
			hittedPosition = D3DXVECTOR3(posX, this->getBox().bottom - animHit->GetHeight() - 10, 0);
			heart = new LargeHeart(posX, posY);
		}
	}
	Memory::SafeDelete(collision);
}

GameObject * Fishmen::GetWeaponObject()
{
	return bullet;
}

GameObject * Fishmen::GetItems()
{
	return heart;
}

void Fishmen::SetFrame(int index)
{
	RECT rect;

	rect.left = index * 16;
	rect.right = rect.left + 16;
	rect.top = 0;
	rect.bottom = 32;
	animObject->SetSourceRect(rect);
}
