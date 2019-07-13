#pragma once
#include "Global.h"
#include "Camera.h"


class Sprite
{
public:
	LPDIRECT3DTEXTURE9  _texture;
	RECT				_sourceRect;	//Source rectangle for drawing
	D3DXVECTOR3			_position;		//Drawing position
	int					_textureWidth;	
	int					_textureHeight;
	bool				_isFlipHor;		//Flip horizontal
	bool				_isFlipVer;		//Flip vertical
	float				_rotationAngle; //angle of rotation, in radian
	D3DXVECTOR2			_scale;			//Zoom in or out sprite
	D3DXVECTOR2			_translation;	//Translate sprite to another position
	D3DXVECTOR3			_center;		//Center point of sprite to be drawn

	Sprite();
	Sprite(const char* filePath, RECT sourcRect = RECT());
	//Check for rect is a valid reactangle or not
	bool IsRect(RECT rect);
	//Draw sprite
	void Draw(int x, int y, int viewportX = CAMERA->camPosition.x, int viewportY = CAMERA->camPosition.y, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());

	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
};
