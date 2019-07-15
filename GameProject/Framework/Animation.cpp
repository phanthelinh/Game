#include "Animation.h"

Animation::Animation(const char * filePath, int totalFrames, int rows, int columns, bool infinite, float timePerFrame):Sprite(filePath)
{

	_columns = columns;
	_rows = rows;
	_curIndex = _curCol = _curRow = _curTotalTime = 0;
	_frameWidth = _textureWidth / columns;
	_frameHeight = _textureHeight / rows;
	//Set texture width/height to frame wid/height
	_textureWidth = _frameWidth;
	_textureHeight = _frameHeight;

	_totalFrames = totalFrames;
	_timePerFrame = timePerFrame;
	_infiniteAnim = infinite;
	//set source rect for texture
	_rect.left = 0;
	_rect.top = 0;
	_rect.right = _frameWidth;
	_rect.bottom = _frameHeight;
	_sourceRect = _rect;
	_isFlipHor = true;
	_isFinished = false;
}

void Animation::Update(float deltaTime)
{
	//no update when the number of frames are less than 1
	if (_totalFrames <= 1)
		return;
	//update frame
	if (_curTotalTime >= _timePerFrame)
	{
		_curTotalTime = 0;

		if (_curIndex >= _totalFrames) //is finished
		{
			_isFinished = true;
		}
		else
		{
			_rect.left = (_curIndex%_columns)*_frameWidth;
			_rect.top = (_curIndex%_rows) * _frameHeight;
			_rect.right = _rect.left + _frameWidth;
			_rect.bottom = _rect.top + _frameHeight;
			//Set sourceRect
			_sourceRect = _rect;
		}
		//increase current index
		if (_infiniteAnim)
		{
			_curIndex = (_curIndex + 1) %_totalFrames;
		}
		else
		{
			_curIndex++;
		}
	}
	else
	{
		_curTotalTime += deltaTime;
	}
}

void Animation::ResetAnim()
{
	_curCol = _curIndex = _curRow = 0;
	_rect.left = 0;
	_rect.top = 0;
	_rect.right = _frameWidth;
	_rect.bottom = _frameHeight;
	_sourceRect = _rect;
	_isFinished = false;
}
