#include "QuadTree.h"


QuadTree::QuadTree(int level, RECT region)
{
	this->level = level;
	this->region = region;
}

QuadTree::~QuadTree()
{
}

void QuadTree::Clear() 
{
	if (node) {
		for (int i = 0; i < 4; ++i)
		{
			node[i]->Clear();
			delete node[i];
			node[i] = NULL;
		}
		ObjectList.clear();
		delete []node;
	}
}

bool QuadTree::isContain(GameObject* obj)
{
	RECT bound = obj->GetBound();

	if (bound.right < region.left ||
		bound.left > region.right ||	
		bound.bottom < region.top ||
		bound.top > region.bottom)
		return false;
	else return true;
}

void QuadTree::Split()
{
	node = new QuadTree*[4];
	RECT rect;
	int halfWidth = (region.right - region.left) / 2;
	int halfHeight = (region.bottom - region.top) / 2;

	//Top Left
	rect.left = region.left;
	rect.top = region.top;
	rect.right = region.left + halfWidth;
	rect.bottom = region.top + halfHeight;
	node[0] = new QuadTree(level + 1, rect);

	//Top Right
	rect.left = region.left + halfWidth;
	rect.top = region.top;
	rect.right = region.right;
	rect.bottom = region.bottom + halfHeight;
	node[1] = new QuadTree(level + 1, rect);

	//Bottom Left
	rect.left = region.left;
	rect.top = region.top + halfHeight;
	rect.right = region.left + halfWidth;
	rect.bottom = region.bottom;
	node[2] = new QuadTree(level + 1, rect);

	//Bottom Right
	rect.left = region.left + halfWidth;
	rect.top = region.top + halfHeight;
	rect.right = region.right;
	rect.bottom = region.bottom;
	node[3] = new QuadTree(level + 1, rect);
}

void QuadTree::InsertNode(GameObject* obj)
{
	
	if (node)
	{
		if (node[0]->isContain(obj))
			node[0]->InsertNode(obj);
		if (node[1]->isContain(obj))
			node[1]->InsertNode(obj);
		if (node[2]->isContain(obj))
			node[2]->InsertNode(obj);
		if (node[3]->isContain(obj))
			node[3]->InsertNode(obj);
		return;
	}

	if (this->isContain(obj))
		ObjectList.push_back(obj);

	//kiem tra neu so luong obj trong vung > 4 thi node tai do se split
	//them lan luot cac obj vao cac node moi dc split
	//dong thoi xoa obj khoi ObjectList cua node cu
	if (ObjectList.size() > MAX_OBJECT_IN_REGION && level < MAX_LEVEL)
	{
		Split();
		while (ObjectList.empty() == false)
		{
			if (node[0]->isContain(ObjectList.back()))
				node[0]->InsertNode(ObjectList.back());
			if (node[1]->isContain(ObjectList.back()))
				node[1]->InsertNode(ObjectList.back());
			if (node[2]->isContain(ObjectList.back()))
				node[2]->InsertNode(ObjectList.back());
			if (node[3]->isContain(ObjectList.back()))
				node[3]->InsertNode(ObjectList.back());

			//sau khi them obj vao node vua split thi se xoa khoi ObjectList cu
			ObjectList.pop_back();
		}
	}
}

void QuadTree::Retrieve(vector<GameObject*> &CollidableObjects, GameObject* player)
{
	if (node)
	{
		//neu player dang nam trong vung cua node 0 thi se lay ra danh sach cac object co the va cham
		if (node[0]->isContain(player))
			node[0]->Retrieve(CollidableObjects, player);
		if (node[1]->isContain(player))
			node[1]->Retrieve(CollidableObjects, player);
		if (node[2]->isContain(player))
			node[2]->Retrieve(CollidableObjects, player);
		if (node[3]->isContain(player))
			node[3]->Retrieve(CollidableObjects, player);
		return;
	}

	//them tat ca object nam cung region voi player vao CollidableObjects list
	if (isContain(player))
	{
		for (int i = 0; i < ObjectList.size(); i++)
		{
			CollidableObjects.push_back(ObjectList[i]);
		}
	}
}