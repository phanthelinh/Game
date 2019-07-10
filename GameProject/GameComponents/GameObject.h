#pragma once
#include "../Framework/Global.h"

enum Tag{ Simon, Enemy, Ground };
struct BoundingBox 
{ 
	float left, top, right, bottom;
	float vX, vY;
};

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	Tag tag;									
	float spawnX, spawnY;	//spawn position
	float posX, posY;		//center-point of object						
	float vX, vY;								
	int width, height;						
	bool isReverse;			//is flip sprite vertically				
	bool isDead;

	virtual D3DXVECTOR3 GetPosition();
	virtual RECT GetBound();
	virtual BoundingBox GetBoundingBox();
	virtual void Update(float deltaTime);
	bool IsCollide(RECT r);
	virtual void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) = 0;
};