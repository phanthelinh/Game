#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(const char * filePath, RECT sourcRect)
{
	//initialize
	_position = D3DXVECTOR3(0, 0, 0);
	_rotationAngle = 0;
	_translation = D3DXVECTOR2(0, 0);
	_center = D3DXVECTOR3(0, 0, 0);
	_scale = D3DXVECTOR2(1, 1);
	_sourceRect = sourcRect;

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFileA(filePath, &info);

	_textureWidth = info.Width;
	_textureHeight = info.Height;
	//sourceRect is not a valid rectangle, set sourceRect to full texture size
	if (!IsRect(sourcRect))
	{
		_sourceRect.left = 0;
		_sourceRect.right = info.Width;
		_sourceRect.top = 0;
		_sourceRect.bottom = info.Height;
	}

	if (FAILED(D3DXCreateTextureFromFileExA(
		GLOBAL->g_DirectDevice,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		NULL,
		&info,
		NULL,
		&_texture)))
	{
		MessageBox(NULL, "Cannot create texture from file", "Error", MB_OK);
	}
}

bool Sprite::IsRect(RECT rect)
{
	if (rect.left == rect.right)
		return false;

	if (rect.top == rect.bottom)
		return false;

	return true;
}

void Sprite::Draw(int x, int y, int viewportX, int viewportY, RECT sourceRect, D3DXVECTOR3 center)
{
	D3DXMATRIX mt; //matrix transform
	D3DXMatrixIdentity(&mt);
	mt._41 = -(float)(viewportX - GLOBAL->g_ScreenWidth / 2);
	//mt._42 = -(float)(viewportY - ((GLOBAL->g_ScreenHeight/2)));//-GlobalVar::GetGameUIArea()) / 2));
	mt._42 = -(float)(viewportY - ((GLOBAL->g_ScreenHeight - GLOBAL->g_GameUIArea) / 2)) + GLOBAL->g_GameUIArea;

	D3DXVECTOR4 transformedPos;
	D3DXVECTOR3 drawingPosition((float)x, (float)y, 0);
	D3DXVec3Transform(&transformedPos, &drawingPosition, &mt);

	D3DXVECTOR3 p = { transformedPos.x,transformedPos.y, 0 };

	//Center
	D3DXVECTOR3 inCenter = _center;
	if (center != D3DXVECTOR3())
	{
		inCenter = center;
	}
	else
	{
		inCenter.x = _textureWidth / 2;
		inCenter.y = _textureHeight / 2;
	}
	//Source rect
	RECT inSourceRect = _sourceRect;
	if (IsRect(sourceRect))
	{
		inSourceRect = sourceRect;
	}

	D3DXMATRIX old, m; //temp var
	GLOBAL->g_SpriteHandler->GetTransform(&old); //Save the old matrix
	//Flip image if exist
	if (_isFlipHor)
	{
		D3DXMatrixScaling(&m, -1, 1, 1);
		p.x *= -1.0f;
		GLOBAL->g_SpriteHandler->SetTransform(&m);
	}
	if (_isFlipVer)
	{
		D3DXMatrixScaling(&m, 1, -1, 1);
		p.y *= -1.0f;
		GLOBAL->g_SpriteHandler->SetTransform(&m);
	}
	//Draw sprite
	GLOBAL->g_SpriteHandler->Draw(_texture,
		&inSourceRect,
		&inCenter,
		&p,
		D3DCOLOR_ARGB(255, 255, 255, 255));
	//Reset to old matrix
	GLOBAL->g_SpriteHandler->SetTransform(&old); 
}

void Sprite::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	Draw(position.x, position.y, cameraPosition.x, cameraPosition.y, sourceRect, center);
}
