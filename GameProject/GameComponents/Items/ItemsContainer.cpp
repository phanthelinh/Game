#include "ItemsContainer.h"
#include <time.h>
#include <stdlib.h>

ItemsContainer::ItemsContainer(int left, int top, int width, int height, bool hasExit)
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

	maxItemsNum = 3;
	//init list items up to 3 items
	for (int i = 0; i < 1; i++) {
		srand(time(0));
		int rnd = rand() % 5 + 1;
		GameObject* obj = NULL;
		/*switch (rnd)
		{
		case 1:
			obj = new Diamon(left, top, width, height, true);
			break;
		case 2:
			obj = new Five(left, top, width, height);
			break;
		case 3:
			obj = new Health(left, top, width, height);
			break;
		case 4:
			obj = new Heart(left, top, width, height);
			break;
		case 5:
			obj = new Life(left, top, width, height);
			break;
		default:
			break;
		}*/
		obj = new PowerStone(left + width/2, top + height/2, 16, 16, true);
		if(obj != NULL)
			listItems.insert(obj);
	}
	listItems.insert(new PowerStone(left + width / 2, top + height / 2, 16, 16, false));
}

ItemsContainer::ItemsContainer(RECT rect):ItemsContainer(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top)
{
	
}

void ItemsContainer::OnCollision(GameObject* object, float deltaTime)
{
	auto collideRes = COLLISION->SweptAABB(object->GetBoundingBox(), this->GetBoundingBox(), deltaTime);
	if (collideRes.isCollide)
	{
		//start falling down other items objects
		isStartFallingItems = true;
		startTime = GetTickCount() + collideRes.entryTime;
		if (listItems.size() > 0)
		{
			auto item = listItems.begin();
			listDrawItems.insert(*item);
			listItems.erase(*item);
		}
	}
}

void ItemsContainer::Update(float deltaTime)
{
	if (isStartFallingItems)
	{
		curSprite = sprites[1];
		auto now = GetTickCount();
		if ((now - startTime)/1000.0 >= 0.3)
		{
			curSprite = sprites[0];
			isStartFallingItems = false;
			startTime = 0;

		}
	}
	for (auto it : listDrawItems)
	{
		it->Update(deltaTime);
		//collision items and ground
		for (auto g : GRID->GetVisibleGround())
		{
			it->OnCollision(g, deltaTime);
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
	for (auto it : listDrawItems)
	{
		it->Draw();
	}
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
