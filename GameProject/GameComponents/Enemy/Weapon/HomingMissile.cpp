#include "HomingMissile.h"

#define MISSLE_SPEED 5.0f

HomingMissile::HomingMissile(float posX, float posY, int direction): Weapon(posX,posY,0,0)
{
	startingPoint = { posX, posY, 0};
	vX = vY = 0;
	weaponDamage = 2;
	tag = Tag::WeaponTag;

	animations[down] = new Animation("Resources/weapon/missle_down.png", 2, 1, 2);
	animations[downleft] = new Animation("Resources/weapon/missle_down_left.png", 2, 1, 2);
	animations[downleftup] = new Animation("Resources/weapon/missle_down_left_up.png", 3, 1, 3);
	animations[downright] = new Animation("Resources/weapon/missle_down_right.png", 2, 1, 2);
	animations[downrightup] = new Animation("Resources/weapon/missle_down_right_up.png", 3, 1, 3);


	currentState = HomingState::down;
	currAnim = animations[down];
	SetState(HomingState::down);
}

float HomingMissile::Dot(float ax, float ay, float bx, float by)
{
	return (ax * bx) + (ay * by);
}

float HomingMissile::perpDot(float ax, float ay, float bx, float by)
{
	return (ay * bx) - (ax * by);
}


void HomingMissile::Update(float deltaTime)
{
	switch (currentState)
	{
		case down:
		{
			vX = 0;
			vY = MISSLE_SPEED;
			break;
		}
	}

	CalculateHoming();


	posX += vX * deltaTime;
	posY += vY * deltaTime;
	currAnim->Update(deltaTime);
	if (posX < CAMERA->GetBound().left || posX>CAMERA->GetBound().right || posY < CAMERA->GetBound().top || posY > CAMERA->GetBound().bottom)
	{
		isDead = true;
	}
}

void HomingMissile::CalculateHoming()
{
	double d = perpDot(PLAYER->posX - posX, PLAYER->posY - posY, vX, vY);
	if (d < 0)
	{
		// rotate your missile clockwise
		vX = MISSLE_SPEED;
	}
	else if (d > 0)
	{
		// rotate your missile counter-clockwise
		vX = -MISSLE_SPEED;
	}
	else
	{
		// missile is headed either directly towards or directly away from the target.  Find out which:
		d = Dot(PLAYER->posX - posX, PLAYER->posY - posY, vX, vY);
		if (d < 0)
		{
			// headed directly away.  Rotate either CW or CCW -- doesn't matter
			vY = -vY;
		}
		else
		{
			// headed directly towards -- no need to rotate.
			/*vY = 0;*/
		}
	}
}

void HomingMissile::OnCollision(GameObject * object, float deltaTime)
{
	if (object->tag == Tag::ShieldTag)
	{
		auto colRes = COLLISION->SweptAABB(GetBoundingBox(), object->GetBoundingBox(), deltaTime);
		if (colRes.isCollide && PLAYER->shieldFlying == false)
		{
			posX += vX * colRes.entryTime;
			posY += vY * colRes.entryTime;
			this->vY = abs(vX) * -1;
			this->vX = 0.0;
		}
	}
	if (object->tag == Tag::Captain)
	{
		auto colRes = COLLISION->SweptAABB(GetBoundingBox(), object->GetBoundingBox(), deltaTime);
		if (colRes.isCollide && PLAYER->isImmu == false)
		{
			PLAYER->health -= weaponDamage;
			if (PLAYER->health <= 0)
				PLAYER->ChangeState(Die);
			else
				PLAYER->ChangeState(Hurt);
		}
	}
}

void HomingMissile::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		currAnim->_isFlipHor = isReverse;
		currAnim->Draw(position, cameraPosition, sourceRect, center);
	}
}

void HomingMissile::Draw()
{
	if (!isDead)
	{
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	}
}

RECT HomingMissile::GetBound()
{
	RECT r;
	r.left = posX;
	r.top = posY;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox HomingMissile::GetBoundingBox()
{
	BoundingBox r;
	r.left = posX;
	r.top = posY;
	r.right = r.left + width;
	r.bottom = r.top + height;
	r.vX = vX;
	r.vY = vY;
	return r;
}

void HomingMissile::Release()
{
}

void HomingMissile::SetState(HomingState state)
{
	prevState = currentState;
	currentState = state;
	currentAnim = animations[state];
	currentAnim->ResetAnim();
	this->width = animations[state]->_frameWidth;
	this->height = animations[state]->_frameHeight;
}
