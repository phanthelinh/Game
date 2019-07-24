#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "../GameComponents/GameObject.h"

class Util
{
	
public:
	static std::vector<int> GetMapDataFromFile(const char* filePath);
	static void GetObjectInforFromFile(const char* filePath, std::vector<GameObject*>& list, Tag tag, bool isLeft = false);
};
