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

	//init list items
	
	/*for (int i = 0; i < 1; i++) {
		srand(time(0));
		int rnd = rand() % 5 + 1;
		GameObject* obj = NULL;

		obj = new PowerStone(left + width/2, top + height/2, 16, 16, true);
		if(obj != NULL)
			listItems.insert(obj);
	}*/
	//listItems.insert(new PowerStone(left + width / 2, top + height / 2, 16, 16, false));
}

ItemsContainer::ItemsContainer(RECT rect):ItemsContainer(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top)
{
	
}

void ItemsContainer::OnCollision(GameObject* object, float deltaTime)
{
	GameObject* item = NULL;
	auto collideRes = COLLISION->SweptAABB(object->GetBoundingBox(), this->GetBoundingBox(), deltaTime);
	if (collideRes.isCollide)
	{
		//start falling down other items objects
		isStartFallingItems = true;
		startTime = GetTickCount() + collideRes.entryTime;
		if (0)
		{
			/*if (isSpawnExit)
				return;*/
			srand(time(NULL));
			int randNum = rand() % 5 + 1;
			switch (randNum)
			{
				case 1:
				{
					item = new Energy(posX + width / 2, posY - height / 2, 16, 16);
					break;
				}
				case 2:
				{
					item = new Five(posX + width / 2, posY - height / 2, 16, 16);
					break;
				}
				case 3:
				{
					item = new KeyCrystals(posX + width / 2, posY - height / 2, 16, 16);
					isSpawnExit = true;
					break;
				}
				case 4:
				{
					item = new OneUp(posX + width / 2, posY - height / 2, 16, 16);
					break;
				}
				case 5:
				{
					item = new PowerStone(posX + width / 2, posY - height / 2, 16, 16, true);
					break;
				}
				case 6:
				{
					item = new Rescue(posX + width / 2, posY - height / 2, 16, 16);
				}
			}
			
			listDrawItems.insert(item);
			listItems.erase(item);

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
