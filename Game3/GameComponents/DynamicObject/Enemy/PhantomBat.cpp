#include "PhantomBat.h"

PhantomBat::PhantomBat()
{
}

PhantomBat::PhantomBat(int x, int y)
{
	posX = x;
	posY = y;
	Tag = GameObjectTypes::PhantomBatObj;
	animObject = new Animation("Resources/bosses/phntombat_50_25.png", 3, 1, 3);
	frameIndex = 1;
	startTime = 10;
	waitTime = 0;
	hp = 5;
	animDeath = new Animation("Resources/effects/hitbosseffect_26_32.png", 3, 1, 3);
	crystal = NULL;
}

PhantomBat::~PhantomBat()
{
	Memory::SafeDelete(crystal);
	Memory::SafeDelete(cameraBound);
}

void PhantomBat::Update(float deltaTime)
{
	if (crystal != NULL && !crystal->isVisible)
	{
		Memory::SafeDelete(crystal);
	}
	DynamicObject::Update(deltaTime);
	/*Update large heart in demoscene*/
	if (isEnable)
	{
		if (Start(deltaTime))
			return;
		FlyRandom(deltaTime);
	}
}

void PhantomBat::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if(isVisible)
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, sourceRect, center);
	campos = cameraPosition;
	//effect and items
	DynamicObject::Draw(hittedPosition, cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	if (crystal != NULL)
	{
		crystal->Draw(D3DXVECTOR3(), cameraPosition);
	}
}

void PhantomBat::SetPlayerPosition(D3DXVECTOR3 player)
{
	playerPos = player;
}

Box PhantomBat::getBox()
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

void PhantomBat::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->Tag == GameObject::WhipObj)
	{
		GameCollision * collision = new GameCollision();
		if (collision->isCollide(getBox(), entity->getBox()))
		{
			hp--;
			isHurted = true;
			hittedPosition = D3DXVECTOR3(posX, this->getBox().bottom - animHit->GetHeight() - 10, 0);
			if (hp == 0)
			{
				if (isVisible)
				{
					isDead = true;
					isVisible = false;
					crystal = new Crystal(campos.x, campos.y);
				}
			}
		}
	}
}

GameObject * PhantomBat::GetItems()
{
	return crystal;
}

void PhantomBat::Sleep()
{
	SetFrame(0);
	direction = { 0, 0 };
	vX = vY = 0;
}

void PhantomBat::Fly(float deltaTime)
{
	SetFrame(frameIndex++);
	if (frameIndex > 2)
		frameIndex = 1;
}

void PhantomBat::FollowPlayer(float deltaTime)
{
	SetVx(BOSS_VX);
	SetVy(BOSS_VY);
	//GetRandomPosition();
	D3DXVECTOR3 oldPos = GetPosition();

	//vector
	direction.x = playerPos.x - oldPos.x;
	direction.y = playerPos.y - oldPos.y;

	posX += direction.x*deltaTime * vX;
	posY += direction.y*deltaTime * vY;
	Fly(deltaTime);
}

void PhantomBat::GetRandomPosition()
{
	random.x = std::rand()%(2816-2595+1) + 2595;
	random.y = std::rand()%(370-199+1)+199;
}

void PhantomBat::FlyRandom(float deltaTime)
{
	SetVx(BOSS_VX);
	SetVy(BOSS_VY);
	GetRandomPosition();
	D3DXVECTOR3 oldPos = GetPosition();

	//vector
	direction.x = random.x - oldPos.x;
	direction.y = random.y - oldPos.y;

	posX += direction.x*deltaTime * vX;
	posY += direction.y*deltaTime * vY;
	Fly(deltaTime);
}

bool PhantomBat::Start(float deltaTime)
{
	if (startTime > 0) //when simon meet boss
	{
		if (startTime > 2.5)
			Sleep();
		startTime -= deltaTime;
		return true;
	}
	else
		return false;
}

void PhantomBat::SetFrame(int index)
{
	RECT rect;

	rect.left = index * 50;
	rect.right = rect.left + 50;
	rect.top = 0;
	rect.bottom = 25;
	animObject->SetSourceRect(rect);
}
