#include "GameUtility.h"



GameUtility::GameUtility()
{

}


GameUtility::~GameUtility()
{

}

void GameUtility::GetObjectInforFromFile(const char * filePath, std::vector<GameObject*>& list, GameObject::GameObjectTypes type, bool isLeft)
{
	std::fstream file(filePath, std::ios_base::in);
	if (!file.is_open())
	{
		return;
	}
	while (!file.eof())
	{
		int x = 0, y = 0, width = 0, height = 0, left = 0;
		GameObject* objectInfo = NULL;
		file >> x;
		file >> y;
		file >> width;
		file >> height;
		if (isLeft)
		{
			file >> left;
		}
		switch (type)
		{
		case GameObject::Ground:
			objectInfo = new Ground(x, y, width, height);
			break;
		case GameObject::AxeKnightObj:
			objectInfo = new AxeKnight(x, y);
			break;
		case GameObject::FleamenObj:
			objectInfo = new Fleamen(x, y);
			break;
		case GameObject::SkeletonObj:

			break;
		case GameObject::RedSkeletonObj:
			objectInfo = new RedSkeleton(x, y + 32);
			break;
		case GameObject::BoneTowerObj:
			objectInfo = new BoneTower(x, y, left);
			break;
		case GameObject::StairTopObj:
			objectInfo = new StairTopObj(x, y, width, height, left);
			break;
		case GameObject::StairBottomObj:
			objectInfo = new StairBottomObj(x, y, width, height, left);
			break;
		case GameObject::DoorObj:
			objectInfo = new Door(x, y);
			break;
		case GameObject::WallObj:
			objectInfo = new Wall(x, y, width, height);
			break;
		case GameObject::BigCandleObj:
			objectInfo = new BigCandle(x, y);
			break;
		case GameObject::CandleObj:
			objectInfo = new Candle(x, y);
			break;
		default:
			break;
		}
		if (objectInfo != NULL)
		{
			objectInfo->SetPosition(x, y);
			objectInfo->SetWidth(width);
			objectInfo->SetHeight(height);
			list.push_back(objectInfo);
		}	
	}
	
}
