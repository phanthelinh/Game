#include "Util.h"
#include "../GameComponents/GameObject.h"

std::vector<int> Util::GetMapDataFromFile(const char * filePath)
{
	std::ifstream file(filePath);
	std::vector<int> data = std::vector<int>();
	if (file.good())
	{
		std::string curData = "";

		int i = 0;
		while (file >> curData)
		{
			i++;
			int x = atoi(curData.c_str());
			data.push_back(x);
		}
		file.close();
	}
	return data;
}

std::vector<RECT> Util::GetObjectDataFromFile(const char * filePath)
{
	std::ifstream file(filePath);
	std::vector<RECT> data = std::vector<RECT>();
	if (file.good())
	{
		int curData;
		while (!file.eof())
		{
			RECT r;
			file >> r.left;
			file >> r.top;
			file >> curData; r.right = r.left + curData;
			file >> curData; r.bottom = r.top + curData;
			data.push_back(r);
		}
		file.close();
	}
	return data;
}

std::vector<RECT> Util::GetAllObjectFromFile(Tag tag, int level)
{
	std::vector<RECT> data = std::vector<RECT>();
	switch (tag)
	{
	case ItemContainerTag:
		if (level == 1)
			data = GetObjectDataFromFile("Resources/items/itemcontainer.txt");
		else
			data = GetObjectDataFromFile("Resources/items/itemcontainer2.txt");
		break;
	case GroundTag:
		if (level == 1)
			data = GetObjectDataFromFile("Resources/map/lv1_gameobject_ground.txt");
		else
			data = GetObjectDataFromFile("Resources/map/lv2_gameobject_ground.txt");
		break;
	}
	return data;
}

