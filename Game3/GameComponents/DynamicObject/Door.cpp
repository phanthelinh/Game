#include "Door.h"

Door::Door()
{
}

Door::Door(int x, int y)
{
	posX = x;
	posY = y;
	Tag = GameObjectTypes::DoorObj;
	animObject = new Animation("Resources/door/door_23_50.png", 4, 1, 4, 0.1);
	opening = closing = false;
	count = 0;
	isEnable = true;
}

Door::~Door()
{
}

void Door::Update(float deltaTime)
{
	SetFrame(indexFrame[count]);
	if (opening)
	{
		count++;
		if (count >= 3)
		{
			count = 3; //finish
		}
	}
	if(closing)
	{
		count--;
		if (count < 0)
		{
			count = 0;
			closing = false; //finish
		}

	}
}

void Door::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (opening || closing)
	{
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	}
}

void Door::SetPlayerPosition(D3DXVECTOR3 player)
{
}

Box Door::getBox()
{
	Box b;
	b.left = posX;
	b.right = b.left + animObject->GetWidth();
	b.top = posY;
	b.bottom = b.top + animObject->GetHeight();
	b.vx = b.vy = 0;
	return b;
}

void Door::OnCollision(GameObject * entity, float deltaTime)
{

}

void Door::OpeningTheDoor(int flag)
{
	if (flag != 2)
	{
		opening = flag;
		closing = !flag;
	}
}

void Door::SetFrame(int index)
{
	RECT rect;

	rect.left = index * 23;
	rect.right = rect.left + 23;
	rect.top = 0;
	rect.bottom = 50;
	animObject->SetSourceRect(rect);
}
