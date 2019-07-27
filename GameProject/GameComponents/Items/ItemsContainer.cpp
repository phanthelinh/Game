#include "ItemsContainer.h"

ItemsContainer::ItemsContainer(int left, int top, int width, int height)
{
	sprites = new Sprite*[2];
	sprites[0] = curSprite = new Sprite("Resources/items/itemcontainer_32_16.png", { 0,0,16,16 });
	sprites[1] = new Sprite("Resources/items/itemcontainer_32_16.png", { 16,0,32,16 });

	posX = left;
	posY = top;
	this->width = width;
	this->height = height;
	this->isReverse = false;
	this->tag = Tag::ItemContainerTag;
}

ItemsContainer::ItemsContainer(RECT rect):ItemsContainer(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top)
{
	
}

void ItemsContainer::OnCollision(GameObject* object, float deltaTime)
{
	auto collideRes = COLLISION->SweptAABB(object->GetBoundingBox(), this->GetBoundingBox());
	if (collideRes.isCollide)
	{
		//start falling down other items objects
		isStartFallingItems = true;
		startTime = GetTickCount() + collideRes.entryTime;
	}
}

void ItemsContainer::Update(float deltaTime)
{
	if (isStartFallingItems)
	{
		curSprite = sprites[1];
		auto now = GetTickCount();
		if (now - startTime >= 0.3)
		{
			curSprite = sprites[0];
			isStartFallingItems = false;
			startTime = 0;
		}

	}
}

void ItemsContainer::Draw()
{
	Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition,RECT(),D3DXVECTOR3(0,0,0));
}

void ItemsContainer::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	curSprite->Draw(position, cameraPosition, sourceRect, center);
}

BoundingBox ItemsContainer::GetBoundingBox()
{
	BoundingBox b;
	b.left = posX - width / 2;
	b.top = posY - height / 2;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vX = b.vY = 0;
	return b;
}

void ItemsContainer::Release()
{
	if (sprites != nullptr)
	{
		delete sprites[0];
		delete sprites[1];
		delete[] sprites;
	}
	if (listItems.size() > 0)
	{
		for (auto item : listItems)
		{
			listItems.erase(item);
		}
	}
}
