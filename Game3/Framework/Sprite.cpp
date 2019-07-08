#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(const char* filePath, RECT sourceRect, int width, int height, D3DCOLOR colorKey)
{    
    this->InitWithSprite(filePath, sourceRect, width, height, colorKey);
}

Sprite::~Sprite()
{
	Memory::SafeRelease(mTexture);
}

void Sprite::InitWithSprite(const char* filePath, RECT sourceRect, int width, int height, D3DCOLOR colorKey)
{
    HRESULT result;
    mPosition = D3DXVECTOR3(0, 0, 0);
    mRotation = 0;
    mRotationCenter = D3DXVECTOR2(mPosition.x, mPosition.y);
    mTranslation = D3DXVECTOR2(0, 0);
    mScale = D3DXVECTOR2(1, 1);
    mSourceRect = sourceRect;

    D3DXGetImageInfoFromFileA(filePath, &mImageInfo);

    if (width == NULL)
    {
        if (!isRect(sourceRect))
            mWidth = mImageInfo.Width;
        else
            mWidth = sourceRect.right - sourceRect.left;
    }
    else
        mWidth = width;

    if (height == NULL)
    {
        if (!isRect(sourceRect))
            mHeight = mImageInfo.Height;
        else
            mHeight = sourceRect.bottom - sourceRect.top;
    }
    else
        mHeight = height;

    if (!isRect(sourceRect))
    {
        mSourceRect.left = 0;
        mSourceRect.right = mWidth;
        mSourceRect.top = 0;
        mSourceRect.bottom = mHeight;            
    } 
	
	if (FAILED(D3DXCreateTextureFromFileExA(
		GlobalVar::GetDevice(),
		filePath,
		mImageInfo.Width,
		mImageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&mImageInfo,
		NULL,
		&mTexture)))
	{
		MessageBox(NULL, "Cannot create texture from file", "Error", MB_OK);
	}
}

bool Sprite::isRect(RECT rect)
{
    if (rect.left == rect.right)
        return false;

    if (rect.top == rect.bottom)
        return false;

    return true;
}

int Sprite::GetWidth()
{
    return mWidth;
}

int Sprite::GetHeight()
{
    return mHeight;
}
//Viewport = campos
void Sprite::Draw(int x, int y, int viewportX, int viewportY, RECT sourceRect, D3DXVECTOR3 center)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._41 = -(float)(viewportX - GlobalVar::GetScreenWidth() / 2);
	mt._42 = -(float)(viewportY - ((GlobalVar::GetScreenHeight() - GlobalVar::GetGameUIArea()) / 2)) + GlobalVar::GetGameUIArea();
	

	D3DXVECTOR4 viewportPosition;
	D3DXVECTOR3 position((float)x, (float)y, 0);
	D3DXVec3Transform(&viewportPosition, &position, &mt);

	D3DXVECTOR3 p = { viewportPosition.x,viewportPosition.y, 0 };

	//Center
	D3DXVECTOR3 inCenter;
	if (center != D3DXVECTOR3())
	{
		inCenter = center;
	}
	else
	{
		inCenter = { (float)mWidth / 2,(float) mHeight,0 };
	}
	RECT inSourceRect = mSourceRect;
	if (isRect(sourceRect))
	{
		inSourceRect = sourceRect;
	}
	D3DXMATRIX old, m; //add
	GlobalVar::GetSprite()->GetTransform(&old); //add
	//add
	if (mIsFlipHorizontal)
	{
		D3DXMatrixScaling(&m, -1, 1, 1);
		p.x *= -1.0f;
		GlobalVar::GetSprite()->SetTransform(&m);
		//opposite center point
		if (center != D3DXVECTOR3()) //render for object, not player
			inCenter.x = inCenter.x + mWidth;
	}
	if (mIsFlipVertical)
	{
		D3DXMatrixScaling(&m, 1, -1, 1);
		p.y *= -1.0f;
		GlobalVar::GetSprite()->SetTransform(&m);
		if (center != D3DXVECTOR3()) //render for object, not player
			inCenter.y = inCenter.y + mWidth;
	}
	//old
	GlobalVar::GetSprite()->Draw(mTexture,
		&inSourceRect,
		&inCenter,
		&p,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	GlobalVar::GetSprite()->SetTransform(&old); //add
}
//Add moi
void Sprite::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	Draw(position.x, position.y, cameraPosition.x, cameraPosition.y, sourceRect, center);
}

void Sprite::SetSourceRect(RECT rect)
{
    mSourceRect = rect;
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture()
{
    return mTexture;
}

void Sprite::SetPosition(D3DXVECTOR3 pos)
{
    mPosition = pos;
}

void Sprite::SetPosition(float x, float y)
{
    mPosition = D3DXVECTOR3(x, y, 0);
}

void Sprite::SetPosition(D3DXVECTOR2 pos)
{
    this->SetPosition(pos.x, pos.y);
}

D3DXVECTOR3 Sprite::GetPosition()
{
    return mPosition;
}

D3DXVECTOR2 Sprite::GetScale()
{
    return mScale;
}

void Sprite::SetScale(D3DXVECTOR2 scale)
{
    mScale = scale;
}

D3DXVECTOR2 Sprite::GetTranslation()
{
    return mTranslation;
}

void Sprite::SetTranslation(D3DXVECTOR2 translation)
{
    mTranslation = translation;
}

D3DXVECTOR2 Sprite::GetRotationCenter()
{
    return mRotationCenter;
}

void Sprite::SetRotationCenter(D3DXVECTOR2 rotationCenter)
{
    mRotationCenter = rotationCenter;
}

float Sprite::GetRotation()
{
    return mRotation;
}

void Sprite::SetRotation(float rotation) 
{
    mRotation = rotation;
}

D3DXIMAGE_INFO Sprite::GetImageInfo()
{
    return mImageInfo;
}

void Sprite::FlipHorizontal(bool flag)
{
    if (mIsFlipHorizontal != flag)
    {
        mIsFlipHorizontal = flag;
        //mScale = D3DXVECTOR2(-mScale.x, mScale.y);
    }
        
}

void Sprite::FlipVertical(bool flag)
{
    if (mIsFlipVertical != flag)
    {
        mIsFlipVertical = flag;
        mScale = D3DXVECTOR2(mScale.x, -mScale.y);
    }        
}

bool Sprite::IsFlipHorizontal()
{
    return mIsFlipHorizontal;
}

bool Sprite::IsFlipVertical()
{
    return mIsFlipVertical;
}

void Sprite::SetWidth(int width)
{
    mWidth = width;
}

void Sprite::SetHeight(int height)
{
    mHeight = height;
}