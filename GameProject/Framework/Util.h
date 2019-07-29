#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <unordered_set>
#include "../GameComponents/GameObject.h"

class Util
{
	
public:
	static std::vector<int> GetMapDataFromFile(const char* filePath);
	static std::vector<RECT> GetObjectDataFromFile(const char* filePath);
	//get data object with tag and level
	static std::vector<RECT> GetAllObjectFromFile(Tag tag, int level);
};
