#pragma once
#include "../Framework/Global.h"

enum Tag {
	Captain,
	Enemy,
	Ground,
	Weapon,
	ItemContainerTag,
	HeartTag,
	ExitGemTag,
	DiamonTag,
	LifeTag,
	HealthTag,
	FiveTag
};
struct BoundingBox 
{ 
	float left, top, right, bottom;
	float vX, vY;
};

class GameObject
{
public:
	GameObject();
	GameObject(float posX, float posY, float width, float height, Tag tag);
	virtual ~GameObject();

	Tag tag;									
	float spawnX, spawnY;	//spawn position
	float posX, posY;		//center-point of object						
	float vX, vY;								
	int width, height;						
	bool isReverse;			//is flip sprite vertically				
	bool isDead;

	virtual D3DXVECTOR3 GetPosition();
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual RECT GetBound();
	virtual BoundingBox GetBoundingBox();
	virtual void Update(float deltaTime);
	bool IsCollide(RECT r);
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) {};
	void Release();
};