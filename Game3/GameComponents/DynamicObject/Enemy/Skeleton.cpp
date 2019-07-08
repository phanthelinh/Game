#include "Skeleton.h"
#include <stdlib.h>
#include <time.h>

Skeleton::Skeleton()
{
}

Skeleton::Skeleton(int x, int y)
{
	posX = x;
	posY = y;
	animObject = new Animation("Resources/enemies/skeleton_18_32.png", 2, 1, 2);
	isLeft = true;
	Tag = GameObjectTypes::SkeletonObj;
	/*bone = NULL;*/
	animIndex = 0;
	prevTime = 0;
	playerPos = { 0,0,0 };
	accelerateX = 30.0f;
	count = 0;
	timeForBone = 0;
	timeBoneUpdate = 0;
	boneIndex = 0;
}

Skeleton::~Skeleton()
{
	bone.clear();
}

void Skeleton::Update(float deltaTime)
{
	srand(time(NULL));
	//check for valid bone
	if (bone.size()!= 0 && CheckAllInvisible())
	{
		bone.clear();
	}
	//update skeleton position
	float now = GetTickCount();
	if (prevTime == 0)
	{
		prevTime = now;
	}
	if ((now - prevTime) / 1000.0f >= 0.1f)
	{
		animObject->Update(deltaTime);
		//player on the right side
		if (playerPos.x > posX)
		{
			isLeft = false; //turn to right
			animObject->FlipHorizontal(true);
			if (playerPos.x - posX <= 70.0f) //keep the distance
			{
				//backward
				SetVx(-accelerateX - (rand()%10 + 9));
			}
			else
			{
				if (playerPos.x - posX > 70.0f &&playerPos.x - posX <= 80.0f)
				{
					if (rand() % 10 > 5)
					{
						SetVx(-accelerateX - (rand() % 10 + 20));
					}
					else
					{
						SetVx(0);
					}
				}
				else
				{
					SetVx(accelerateX + (rand() % 10 + 9));
				}
			}
		}
		else //player on the left side
		{
			isLeft = true;
			animObject->FlipHorizontal(false);
			if (posX - playerPos.x <= 70.0f) //keep the distance
			{
				//backward
				SetVx(accelerateX + (rand() % 10 + 9));
			}
			else
			{
				if (posX - playerPos.x > 70.0f && posX - playerPos.x <= 80.0f)
				{
					//SetVx(0);
					if (rand() % 10 > 5)
					{
						SetVx(-accelerateX - (rand() % 10 + 20));
					}
					else
						SetVx(0);
				}
				else
				{
					SetVx(-accelerateX - (rand() % 10 + 9));
				}
			}
		}
		//update position
		DynamicObject::Update(deltaTime);
		//
		//throw bone after 2 second
		//
		if (timeForBone == 0)
		{
			timeForBone = now;
		}
		if ((now - timeForBone) / 1000.0f >= 0.1f)
		{
			if (bone.size() == 0) //not exist
			{
				count = rand() % 3 + 1;
				boneIndex = 0;
			}
			timeForBone = now;
		}
	}
	else
	{
		Sleep(1/0.1f - (now - prevTime) / 1000.0f);
	}
	//add after 0.2 second
	if (timeBoneUpdate == 0)
		timeBoneUpdate = now;
	if ((now - timeBoneUpdate) / 1000.0f >= 0.3f)
	{
		if (count > 0)
		{
			Bone * obj = NULL;
			obj = new Bone(posX, posY, isLeft);
			bone.push_back(obj);
			count--;
		}
		timeBoneUpdate = now;
	}
	//update bone
	if (bone.size()!=0)
	{
		for (int i = 0; i < bone.size(); i++)
			bone[i]->Update(deltaTime);
	}
	
}

void Skeleton::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible)
	{
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
		//draw bone
		if (bone.size() != 0)
		{
			for (int i = 0; i < bone.size(); i++)
			{
				bone[i]->Draw(position, cameraPosition);
				if (bone[i]->GetPosition().x < cameraPosition.x - GlobalVar::GetScreenWidth() / 2 ||
					bone[i]->GetPosition().x > cameraPosition.x + GlobalVar::GetScreenWidth() / 2 ||
					bone[i]->GetPosition().y < cameraPosition.y - GlobalVar::GetScreenHeight() / 2 - GlobalVar::GetGameUIArea() / 2 ||
					bone[i]->GetPosition().y > GlobalVar::GetScreenHeight())
				{
					bone[i]->isVisible = false;
				}
			}

		}
	}
}

void Skeleton::SetPlayerPosition(D3DXVECTOR3 player)
{
	playerPos = player;
}

Box Skeleton::getBox()
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

void Skeleton::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->Tag == GameObject::WhipObj)
	{
		this->isVisible = false;
	}
}

void Skeleton::ResetFrame(int index)
{
}

bool Skeleton::CheckAllInvisible()
{
	for (int i = 0; i < bone.size(); i++)
		if (bone[i]->isVisible)
			return false;
	return true;
}
