#include "Whip.h"

Whip::Whip()
{
	animObject = new Animation("Resources/simon/weapon/whip_84_32.png",3,1,3);
	reverse = false;
	Tag = GameObjectTypes::WhipObj;
	currentIndex = 0;
	isFinish = false;
}

Whip::Whip(int x, int y)
{
	animObject = new Animation("Resources/simon/weapon/whip_84_32.png", 3, 1, 3);
	reverse = false;
	Tag = GameObjectTypes::WhipObj;
	currentIndex = 0;
	isFinish = false;
	posX = x;
	posY = y;
}

Whip::~Whip()
{
}

void Whip::SetReverse(bool flag)
{
	reverse = flag;
}

void Whip::Update(float deltaTime)
{
	if (!animObject->isFinishedAnim())
	{
		animObject->Update(deltaTime);
	}

}

void Whip::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!animObject->isFinishedAnim())
	{
		animObject->FlipHorizontal(reverse);
		animObject->Draw(position, cameraPosition);
		/*RECT r = { 0,0,200,48 };*/
	}	
}

void Whip::SetPlayerPosition(D3DXVECTOR3 player)
{
	playerPos = player;
}

Box Whip::getBox()
{
	Box b = Box();
	if (animObject->GetCurrentIndex() == 2)
	{
		if (!reverse)
		{
			b.left = playerPos.x;
			b.right = b.left + animObject->GetWidth() / 2;
			b.top = playerPos.y - 32;
			b.bottom = b.top + animObject->GetHeight();
			b.vx = b.vy = 0;
		}
		else
		{
			b.left = playerPos.x - animObject->GetWidth() / 2;
			b.right = playerPos.x;
			b.top = playerPos.y - 32;
			b.bottom = b.top + animObject->GetHeight();
			b.vx = b.vy = 0;
		}
	}	
	return b;
}

void Whip::OnCollision(GameObject * entity, float deltaTime)
{
	GameCollision* collision = new GameCollision();

	Box whipBox = this->getBox();
	if (collision->isCollide(whipBox, entity->getBox()))
	{
		if (entity->Tag > 7)
			entity->SetVisible(false);
	}
	Memory::SafeDelete(collision);
}

void Whip::ResetFrame(int index)
{
	RECT rect;

	rect.left = index * 84;
	rect.right = rect.left + 84;
	rect.top = 0;
	rect.bottom = 32;
	animObject->SetSourceRect(rect);
}

