#pragma once
#include <Windows.h>
#include <vector>
#include "GameComponents/GameObject.h"

#define MAX_LEVEL 32
#define MAX_OBJECT_IN_REGION 4

using namespace std;

class QuadTree
{
private:
	vector<GameObject*> ObjectList;
	QuadTree** node;
	int level;
	RECT region; 
public:
	QuadTree(int level, RECT region);
	~QuadTree();

	//check game object co nam trong vung hien tai hay ko
	bool isContain(GameObject* obj);

	//chia thanh 4 vung tuong ung 4 node cho quad tree 
	void Split();

	//giai phong vung nho cho leaf node den root
	void Clear();

	void InsertNode(GameObject* obj);

	//return a list contains objects can collide with player
	void Retrieve(vector<GameObject*> &CollidableObjects, GameObject* player);
};

