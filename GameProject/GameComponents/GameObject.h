#pragma once
#include "../Framework/Global.h"

enum Tag {
	Captain,
	ShieldTag,
	EnemyTag,
	WeaponTag,
	GroundTag,
	WaterTag,
	ItemContainerTag,
	EnergyTag,
	KeyCrystalsTag,
	PowerStoneTag,
	OneUpTag,
	RescueTag,
	FiveTag,
	BigHeart,
	Wizard
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
	GameObject(RECT r);
	virtual ~GameObject();

	Tag tag;									
	float spawnX, spawnY;	//spawn position
	float posX, posY;		//center-point of object						
	float vX, vY;								
	int width, height;						
	bool isReverse;			//is flip sprite vertically				
	bool isDead;

	bool IsCollide(RECT r);
	virtual void OnCollision(GameObject* object, float deltaTime = 0);
	virtual D3DXVECTOR3 GetPosition();
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual RECT GetBound();
	virtual BoundingBox GetBoundingBox();
	virtual void Update(float deltaTime);
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) {};
	virtual void Draw();
	virtual void Release();

	//get bound from (0, 0)
	virtual RECT GetBoundFromCorner();
	virtual BoundingBox GetBoundingBoxFromCorner();
};