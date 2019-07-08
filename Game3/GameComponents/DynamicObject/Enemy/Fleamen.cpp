#include "Fleamen.h"

Fleamen::Fleamen()
{
}

Fleamen::Fleamen(int x, int y)
{
	Tag = GameObjectTypes::FleamenObj;
	animObject = new Animation("Resources/enemies/fleamen_16_16.png", 2, 1, 2);
	animObject->SetPosition(x, y);
	posX = x;
	oldX = posX;
	posY = y;
	oldY = posY;
	isVisible = true;
	prevTime = 0;
	isMoveLeft = true;
	vX = 0;
	vY = 0;
	playerPos = { 0,0,0 };
	step = 0;
	accelerateX = 20.0f;
}

Fleamen::~Fleamen()
{
}


void Fleamen::Update(float deltaTime)
{
	animObject->Update(deltaTime);
	//init position
	float now = GetTickCount();
	if (prevTime == 0)
		prevTime = now;
	if ((now - prevTime) / 1000 >= TIME_CHANGE)
	{
		if (step == 2) //high leap
		{
			if ((int)posY >= oldY)
			{
				SetVy(-80);
				step = (step + 1) % 3;
			}
		}
		else
		{
			if ((int)posY >= oldY) //short hop, step =0,1
			{
				SetVy(-50);
				step = (step + 1) % 3;
			}
		}
		if (isMoveLeft) //on the right, go back to the left
		{
			animObject->FlipHorizontal(false);
			SetVx(-FLEAMEN_VX);
			if (posX < playerPos.x - 50)
			{
				isMoveLeft = false;
			}
		}
		else //on the left, go back to the right
		{
			animObject->FlipHorizontal(true);
			SetVx(FLEAMEN_VX);
			if (posX > playerPos.x + 50)
			{
				isMoveLeft = true;
			}
		}
		/*animObject->FlipHorizontal(false);
		SetVx(-FLEAMEN_VX);*/
		prevTime = now;
	}
	else
	{
		Sleep(1/TIME_CHANGE - (now - prevTime) / 1000.0f);
	}
	
	AddVy(ACCELARATE_Y);
	DynamicObject::Update(deltaTime);
	if (posY >= oldY)
	{
		posY = oldY;
		SetVx(0); //already on ground
	}
	
}

void Fleamen::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible)
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, sourceRect, center);
	if (posX < cameraPosition.x - GlobalVar::GetScreenWidth() / 2 || posX >  cameraPosition.x + GlobalVar::GetScreenWidth() / 2)
	{
		isVisible = false;
	}
}

void Fleamen::SetPlayerPosition(D3DXVECTOR3 player)
{
	playerPos = player;
}

Box Fleamen::getBox()
{
	//position at 0,0
	Box b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + animObject->GetWidth();
	b.bottom = b.top + animObject->GetHeight();
	return b;
}

void Fleamen::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->Tag == GameObjectTypes::Simon)
	{
		//this->isVisible = false;
	}
}
