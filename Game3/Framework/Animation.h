#pragma once
#include "Sprite.h"

class Animation 
	:public Sprite
{
public:
	Animation();
	Animation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);
	~Animation();

	virtual void Update(float deltaTime);
	bool isFinishedAnim();
	void ResetAnim();
	int GetCurrentIndex();
	
private:
	void InitWithAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	int columns, rows;
	int curIndex;
	int curColumn, curRow;
	int frameWidth, frameHeight;
	int totalFrame;
	float timePerFrame, curTotalTime;
	bool isFinished;
	RECT rect;
};
