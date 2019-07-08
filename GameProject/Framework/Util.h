#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class Util
{
	
public:
	static std::vector<int> GetMapDataFromFile(const char* filePath);
};
