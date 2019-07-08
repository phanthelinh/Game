#include "RedSkeleton.h"
#include <math.h>

RedSkeleton::RedSkeleton()
{
}

RedSkeleton::RedSkeleton(int x, int y)
{
	posX = x;
	posY = y;
	isLeft = true;
	Tag = GameObjectTypes::RedSkeletonObj;
	animObject = new Animation("Resources/enemies/redskeleton_18_32.png", 4, 1, 4);
	frameReset = -2;
	sleepTime = 0;
	step = 0;
}

RedSkeleton::~RedSkeleton()
{
}

void RedSkeleton::Update(float deltaTime)
{
	
	float now = (float) GetTickCount();
	if (prevTime == 0)
	{
		prevTime = now;
	}
	if (sleepTime == 0) //must not sleep
	{
		if ((now - prevTime) / 1000.0f >= 0.2f)
		{
			//do not move at sprite 0 and 1
			ResetFrame(frameReset + 2);
			//start moving at sprtite 2 and 3
			if (frameReset >= 0)
			{
				//isLeft = (posX > playerPos.x);
				if (isLeft)
				{
					animObject->FlipHorizontal(false);
					SetVx(-ACCELERATE_X_REDSKELETON);
				}
				else
				{
					animObject->FlipHorizontal(true);
					SetVx(ACCELERATE_X_REDSKELETON);
				}
				if (step == 2)
				{
					SetVx(0);
				}
				//only update when moving
				DynamicObject::Update(deltaTime);
				step = (step + 1) % 3;
				
				if (abs(posX - playerPos.x) >= 30) //always keep distance with player 30
				{
					
				}
			}
			//increase frameset
			frameReset = (frameReset + 1) % 2;		
			prevTime = now;
		}
		else
		{
			Sleep(0.2f - (now - prevTime) / 1000.0f);
		}
	}
	else //sleepTime
	{
		if ((now - prevTime) / 1000.0f >= 1.0f)
		{
			sleepTime--;
			prevTime = now;
		}
		else
		{
			Sleep(1.0f - (now - prevTime) / 1000.0f);
		}
		if (sleepTime < 0)
		{
			sleepTime = 0;
		}
	}
}

void RedSkeleton::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible)
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, sourceRect, center);
}

void RedSkeleton::SetPlayerPosition(D3DXVECTOR3 player)
{
	playerPos = player;
}

Box RedSkeleton::getBox()
{
	Box b;
	b.left = GetPosition().x;
	b.top = GetPosition().y;
	b.right = b.left + animObject->GetWidth();
	b.bottom = b.top + animObject->GetHeight();
	b.vx = GetVx();
	b.vy = GetVy();
	return b;
}

void RedSkeleton::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->Tag == GameObjectTypes::WhipObj) //was attacked by player
	{
		//reset to frame 0
		frameReset = -2;
		//sleep for a while before get up and walking
		sleepTime = 3; //3 seconds
	}
}

void RedSkeleton::ResetFrame(int index)
{
	RECT rect;
	
	rect.left = index * 18;
	rect.right = rect.left + 18;
	rect.top = 0;
	rect.bottom = 32;
	animObject->SetSourceRect(rect);
}
