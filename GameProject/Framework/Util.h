#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

class Util
{
	
public:
	static std::vector<int> GetMapDataFromFile(const char* filePath);
};
