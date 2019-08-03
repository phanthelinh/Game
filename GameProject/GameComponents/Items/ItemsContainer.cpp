#include "ItemsContainer.h"
#include <time.h>
#include <stdlib.h>
#include "../../Scene/DemoScene.h"

ItemsContainer::ItemsContainer(int left, int top, int width, int height, std::string items, int hasExit)
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
	this->hasExit = hasExit;
	
	//load string items by posX of container
	this->strItems = items;
}

ItemsContainer::ItemsContainer(RECT rect):ItemsContainer(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, "")
{
	
}

void ItemsContainer::InsertFromFile(int level)
{
	std::unordered_set<GameObject*> rs;
	std::string filename = "Resources/items/lv" + std::to_string(level) + "_itemcontainer.txt";
	std::ifstream file(filename);
	if (file.good())
	{
		while (!file.eof())
		{
			int x, y, w,h;
			std::string strItems;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> strItems;
			GameObject* obj = new ItemsContainer(x, y, w, h, strItems);
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

void ItemsContainer::OnCollision(GameObject* object, float deltaTime)
{
	GameObject* item = NULL;
	if (object->tag == ShieldTag)
	{
		auto collideRes = COLLISION->SweptAABB(object->GetBoundingBox(), this->GetBoundingBox(), deltaTime);
		if (collideRes.isCollide)
		{
			//start falling down other items objects
			isStartFallingItems = true;
			startTime = GetTickCount() + collideRes.entryTime;
			if (strItems.length() > 0)
			{
				switch (strItems.at(0))
				{
				case '1':
				{
					item = new BigHeart(posX + width / 2, posY - height / 2, 16, 16);
					break;
				}
				case '2':
				{
					item = new Energy(posX + width / 2, posY - height / 2, 16, 16);
					break;
				}
				case '3':
				{
					item = new Five(posX + width / 2, posY - height / 2, 16, 16);
					isSpawnExit = true;
					break;
				}
				case '4':
				{
					item = new KeyCrystals(posX + width / 2, posY - height / 2, 16, 16);
					break;
				}
				case '5':
				{
					item = new PowerStone(posX + width / 2, posY - height / 2, 16, 16, true);
					break;
				}
				case '6':
				{
					item = new Rescue(posX + width / 2, posY - height / 2, 16, 16);
					break;
				}
				}

				listDrawItems.insert(item);
				GRID->AddObject(item);
				//listItems.erase(item);
				strItems.pop_back();
			}

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
	Draw(D3DXVECTOR3(posX - 4, posY - 4, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
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
	if (listDrawItems.size() > 0)
	{
		for (auto item : listDrawItems)
		{
			listDrawItems.erase(item);
		}
	}
}
