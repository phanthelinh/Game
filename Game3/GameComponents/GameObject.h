#pragma once
#include "../GlobalVar.h"
#include "../GameCollision.h"
#include <vector>

#define VK_C							0x43
#define GRAVITY							1000


class GameObject
{
public:
	GameObject();
	GameObject(float x, float y);
	virtual ~GameObject();
	
	enum GameObjectTypes
	{
		None,
		Simon,
		Ground, WhipObj, BigCandleObj, CandleObj,
		NextStage, NextSection,
		StairTopObj, StairBottomObj,SmallHeartObj, LargeHeartObj,
		CrystalObj,
		DoorObj, WallObj,
		AxeKnightObj, AxeObj, FleamenObj, SkeletonObj, BoneObj, RedSkeletonObj, PantherObj, 
		BoneTowerObj, BulletObj, GhoulsObj, FishmenObj,BatObj,
		PhantomBatObj
	};

	GameObjectTypes Tag; //Identify game object types

	virtual RECT GetBound();
	virtual RECT GetBoundTopLeft();

	virtual void SetPosition(int x, int y);
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual void SetPosition(D3DXVECTOR2 pos);
	virtual D3DXVECTOR3 GetPosition();

	virtual void AddPosition(int x, int y);
	virtual void AddPosition(D3DXVECTOR3 pos);
	virtual void AddPosition(D3DXVECTOR2 pos);

	virtual void SetWidth(int w);
	virtual int GetWidth();

	virtual void SetHeight(int h);
	virtual int GetHeight();

	virtual void Update(float deltaTime);
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());

	//get entity type
	virtual GameObjectTypes getTag();
	//Direction of object used for entity
	virtual bool IsLeft();
	
	//set box for object to check collision later
	virtual void setBox(float x, float y, float width, float height, float vx, float vy);
	virtual Box getBox();
	//invisible/visible
	virtual void SetVisible(bool _isVisible);
	//player position to enable animation
	virtual void SetPlayerPosition(D3DXVECTOR3 player);
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	//get waepon of certain object, used to check collision
	virtual GameObject* GetWeaponObject();
	//get items after this object was destroyed
	virtual GameObject* GetItems();
	//survival
	virtual float getReviveTime();
	//only used to invoke Opening the Door
	virtual void OpeningTheDoor(int flag);
protected:
	//This method was automatically called every time SetPosition() executed
	virtual void OnSetPosition(D3DXVECTOR3 pos);
	float posX, posY;
	float width, height;
	Box box;
	float reviveTime;	//thoi gian hoi sinh lai enemy
	float invicibleTime; //can't be attacked
public:
	bool isVisible;	//identify if object is defeated -> visible = false
	bool isEnable;	//activate dynamic object
};

