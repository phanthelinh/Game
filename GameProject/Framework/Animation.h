#pragma once
#include "Sprite.h"

class Animation :public Sprite
{
public:

	int		_columns;
	int		_rows;
	int		_curIndex;
	int		_curCol;
	int		_curRow;
	int		_frameWidth;
	int		_frameHeight;
	int		_totalFrames;
	float	_timePerFrame;
	float	_curTotalTime;
	bool	_infiniteAnim;
	RECT	_rect;

	Animation(const char* filePath, int totalFrames, int rows, int columns, bool infinite = true, float timePerFrame = 100.0f);
	void Update(float deltaTime);

};
