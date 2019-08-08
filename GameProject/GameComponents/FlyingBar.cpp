#include "FlyingBar.h"

FlyingBar::FlyingBar(float posX, float posY, float endX, float endY, float type):GameObject(posX,posY,0,0, FlyingBarTag)
{
	barsprite = new Sprite("Resources/map/flyingbar_32_16.png");
	width = 14;
	height = 16;
	//init for 4 flames
	flameDown1 = new Animation("Resources/map/flameup_12_10.png", 2, 1, 2);
	flameDown2 = new Animation("Resources/map/flameup_12_10.png", 2, 1, 2);
	flameLeft = new Animation("Resources/map/flameleft_16_8.png", 2, 1, 2);
	flameRight = new Animation("Resources/map/flameleft_16_8.png", 2, 1, 2);
	isFlying = false;
	startime = 0;
	endPoint = { endX,endY,0 };
	startPoint = { posX,posY,0 };
	lowPos = endY >= posY ? (D3DXVECTOR3(endX,endY,0)) : D3DXVECTOR3(posY,posY,0);
	highPos = endY < posY ? (D3DXVECTOR3(endX,endY,0)) : D3DXVECTOR3(posY,posY,0);
	this->type = type;
	isGoingUp = startPoint.y > endPoint.y;
	leftPos = posX <= endX ? (D3DXVECTOR3(posX, posY, 0)) : (D3DXVECTOR3(endX, endY, 0));
	rightPos = posX > endX ? (D3DXVECTOR3(posX, posY, 0)) : (D3DXVECTOR3(endX, endY, 0));
	isGoingToRight = startPoint.x < endPoint.x;
	angle = PI / 3;
}

void FlyingBar::InsertFromFile(int level)
{
	std::unordered_set<GameObject*> rs;
	std::string filename = "Resources/map/lv" + std::to_string(level) + "_gameobject_flyingbar.txt";
	std::ifstream file(filename);
	//insert to grid

	if (file.good())
	{
		while (!file.eof())
		{
			int st, sy,ex,ey, t;
			file >> st >> sy >> ex >> ey >> t;
			GameObject* obj = new FlyingBar(st, sy, ex, ey, t);
			if (obj)
			{
				rs.insert(obj);
			}
		}
		file.close();
	}
	if (rs.size() > 0)
		GRID->InsertToGrid(rs);
	rs.clear();
}

void FlyingBar::OnCollision(GameObject * object, float deltaTime)
{
	if (object == NULL)
		return;
	if (object->tag == Captain)
	{
		auto res = COLLISION->SweptAABB(object->GetBoundingBox(), GetBoundingBox(), deltaTime);
		if (res.isCollide && res.sideCollided == CollisionSide::Bottom)
		{
			PLAYER->isStandOnFlyingBar = true;
			PLAYER->barObject = this;
			PLAYER->posY = posY - PLAYER->currentAnim->_frameHeight / 2 + 1;
			PLAYER->vX = vX;
			PLAYER->vY = vY;
			PLAYER->ChangeState(Standing);
		}
	}
}

RECT FlyingBar::GetBound()
{
	RECT r;
	r.left = posX + 9;
	r.top = posY;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox FlyingBar::GetBoundingBox()
{
	BoundingBox r;
	r.left = posX + 9;
	r.top = posY;
	r.right = r.left + width;
	r.bottom = r.top + height;
	r.vX = r.vY = 0;
	return r;
}

void FlyingBar::Update(float deltaTime)
{
	
	auto now = GetTickCount();
	if (startime == 0)
		startime = now;
	if (type == 1) //go left/right
	{
		if (isFlying)
		{
			posX += vX * deltaTime;
			posY += vY * deltaTime;
			if (isGoingToRight)
			{
				vX = 5.0f;
				if (posX > rightPos.x)
				{
					vX = 0;
					isGoingToRight = !isGoingToRight;
					isFlying = false;
					startime = now;
				}
			}
			else
			{
				vX = -5.0f;
				if (posX < leftPos.x)
				{
					vX = 0;
					isGoingToRight = !isGoingToRight;
					isFlying = false;
					startime = now;
				}
			}
		}
		else
		{
			isFlying = (now - startime) / 1000.0f >= 2.0f;
		}
	}
	else //go straight ahead
	{
		if (isFlying)
		{
			posX += vX * deltaTime;
			posY += vY * deltaTime;
			if (isGoingUp)
			{
				vY = -5.0f;
				if (posY < highPos.y)
				{
					vY = 0;
					isGoingUp = !isGoingUp;
					isFlying = false;
					startime = now;
				}
			}
			else
			{
				vY = 5.0f;
				if (posY > lowPos.y)
				{
					vY = 0;
					isGoingUp = !isGoingUp;
					isFlying = false;
					startime = now;
				}
			}
		}
		else
		{
			isFlying = (now - startime) / 1000.0f >= 2.0f;
		}
	}

}

void FlyingBar::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	barsprite->Draw(position, cameraPosition, sourceRect, center);
}

void FlyingBar::Draw()
{
	Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
}

void FlyingBar::Release()
{
}
