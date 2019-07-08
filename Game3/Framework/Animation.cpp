#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(const char * filePath, int totalFrame, int rows, int columns, float timePerFrame, D3DCOLOR colorKey)
{
	InitWithAnimation(filePath, totalFrame, rows, columns, timePerFrame, colorKey);
}

Animation::~Animation()
{
}

void Animation::Update(float deltaTime)
{
	if (totalFrame <= 1)
		return;

	if (curTotalTime >= timePerFrame)
	{
		curTotalTime = 0;
		curIndex++;
		curColumn++;

		if (curIndex >= totalFrame)
		{
			curIndex = 0;
			curColumn = 0;
			curRow = 0;
			isFinished = true;
		}

		if (curColumn >= columns)
		{
			curColumn = 0;
			curRow++;

			if (curRow >= rows)
				curRow = 0;
		}

		rect.left = curColumn * frameWidth;
		rect.right = rect.left + frameWidth;
		rect.top = curRow * frameHeight;
		rect.bottom = rect.top + frameHeight;

		SetSourceRect(rect);
	}
	else
	{
		curTotalTime += deltaTime;
	}
}

bool Animation::isFinishedAnim()
{
	return isFinished;
}

void Animation::ResetAnim()
{
	curIndex = 0;
	curColumn = 0;
	curRow = 0;
	isFinished = false;
}

int Animation::GetCurrentIndex()
{
	return curIndex;
}

void Animation::InitWithAnimation(const char * filePath, int totalFrame, int rows, int columns, float timePerFrame, D3DCOLOR colorKey)
{
	InitWithSprite(filePath);
	curColumn = 0;
	curRow = 0;
	this->timePerFrame = timePerFrame;
	this->totalFrame = totalFrame;
	this->rows = rows;
	this->columns = columns;
	isFinished = false;

	//width va height cua SpriteSheet
	this->frameWidth = GetWidth() / this->columns;
	this->frameHeight = GetHeight() / this->rows;

	SetWidth(this->frameWidth);
	SetHeight(this->frameHeight);

	rect.top = 0;
	rect.left = 0;
	rect.right = this->frameWidth;
	rect.bottom = this->frameHeight;
	SetSourceRect(rect);
}
