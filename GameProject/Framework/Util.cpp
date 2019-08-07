#include "Util.h"

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
		else if(level == 3)
			data = GetObjectDataFromFile("Resources/items/itemcontainer3.txt");
		break;
	case GroundTag:
	{
		std::string filename = "Resources/map/lv" + std::to_string(level) +"_gameobject_ground.txt";
		data = GetObjectDataFromFile(filename.c_str());
		break;
	}
	case WaterTag:
		if (level == 1)
		{
			data = GetObjectDataFromFile("Resources/map/lv1_water.txt");
		}
		break;
	}
	return data;
}

std::unordered_map<int, std::string> Util::GetItemsList(const char* filePath)
{
	std::unordered_map<int, std::string> mItems;
	std::ifstream file(filePath);
	if (file.good())
	{
		int posX;
		std::string items;
		while (!file.eof())
		{
			file >> posX;
			file >> items;
			mItems[posX] = items;
		}
		file.close();
	}
	return mItems;
}
