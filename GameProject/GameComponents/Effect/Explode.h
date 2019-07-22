#pragma once
#include "../../Framework/Animation.h"

#define EXPLODE Explode::GetInstance()

class Explode
{
private:
	Animation* explode;
	static Explode* instance;
	int posX, posY;
	bool isStart;
public:
	Explode();
	static Explode* GetInstance();
	void ExplodeAt(int x, int y);
	void ExplodeAt(D3DXVECTOR3 postion);
	void Update(float deltaTime);
	void Draw();
	void Release();
};