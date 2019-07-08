#include "Panther.h"



Panther::Panther()
{
}

Panther::Panther(float x, float y)
{
	posX = x;
	posY = y;
	this->width = 32;
	this->height = 16;
	isEnable = false;
	Tag = GameObject::PantherObj;
	isVisible = true;
	animObject = new Animation("Resources/enemies/phanthers_32_16.png", 4, 1, 4, 0.1);
	isMoveLeft = true;
	frameIndex = 1;
	isJumped = false;
	onGround = true;

}

Panther::~Panther()
{
}

Panther Panther::getPanther()
{
	return *this;
}

void Panther::Update(float deltaTime)
{	
	if (abs(playerPos.x - posX) > 600)	//player is not in it area
	{
		Stop();
	}
	else
	{
		Run();
		if (!onGround)
		{
			AddVy(10);
			isJumped = true;
		}
		else if (isJumped)
		{
			isMoveLeft = isMoveLeft ? false : true;
			Run();
		}

	}
	DynamicObject::Update(deltaTime);

		
}

void Panther::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible)
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, sourceRect, center);
}

void Panther::SetPlayerPosition(D3DXVECTOR3 player)
{
	playerPos = player;
}

Box Panther::getBox()
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

void Panther::ResetFrame(int index)
{
	RECT rect;
	rect.left = index * 32;
	rect.right = rect.left + 32;
	rect.top = 0;
	rect.bottom = 16;
	animObject->SetSourceRect(rect);
}

void Panther::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->Tag == GameObject::Ground)
	{
		GameCollision * collision = new GameCollision();
		Box broadPhase = collision->getBroadPhaseRect(getBox(), deltaTime);
		if (collision->isCollide(broadPhase, entity->getBox()))
		{
			float normalX = 0, normalY = 0;
			float collisionTime = collision->sweptAABB(getBox(), entity->getBox(), normalX, normalY);
			if (collisionTime > 0 && collisionTime < 1)
			{
					SetVy(0);
					SetPosition(this->GetPosition().x, posY + collisionTime*vY);
					onGround = true;
			}
		}
		onGround = false;
		Memory::SafeDelete(collision);
	}
}

void Panther::Jump()
{
	onGround = false;
	if (this->isMoveLeft)
	{
		animObject->FlipHorizontal(false);
		SetVx(-PANTHER_VX);
	}
	else
	{
		animObject->FlipHorizontal(true);
		SetVx(PANTHER_VX);
	}
	SetVy(-PANTHER_VY);
	isJumped = true;
	ResetFrame(3);
}

void Panther::Stop()
{
	SetVx(0);
	SetVy(0);
	onGround = true;
	ResetFrame(0);
}

void Panther::Run()
{
	if (frameIndex > 2)
		frameIndex = 1;
	if (isMoveLeft)
	{
		SetVx(-PANTHER_VX);
	}
	else
	{
		animObject->FlipHorizontal(true);
		SetVx(PANTHER_VX);
	}
	frameIndex++;
	ResetFrame(frameIndex);
}
