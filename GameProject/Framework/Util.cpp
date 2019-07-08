#include "Util.h"

std::vector<int> Util::GetMapDataFromFile(const char * filePath)
{
	std::ifstream file(filePath);
	std::vector<int> data = std::vector<int>();
	if (file.good())
	{
		std::string curData = "";
		while (file >> curData)
		{
			int x = atoi(curData.c_str());
			data.push_back(x);
		}
		file.close();
	}
	return data;
}
