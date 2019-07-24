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

void Util::GetObjectInforFromFile(const char* filePath, std::vector<GameObject*>& list, Tag tag, bool isLeft)
{
}
