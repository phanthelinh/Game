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
			if (x != 0)
				data.push_back(x);
		}
		file.close();
	}
	return data;
}

void Util::GetObjectInforFromFile(const char* filePath, std::vector<GameObject*>& list, Tag tag, bool isLeft)
{
}
