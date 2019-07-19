#pragma once
#include "../GameObject.h"
#include "../../Framework/Sprite.h"


enum ShieldState
{
	Normal,
	Shielded,
	Shield_Upward,
	Flying
};

class Shield :public GameObject
{
private:
	D3DXVECTOR3 startingPos; //starting point of the shield
	
public:
	ShieldState curState;
	Sprite*		shield;
	D3DXVECTOR3 _translationToPlayer;

	Shield();

	void SetState(ShieldState state);
	void SetTranslationToPlayer(bool playerReverse, ShieldState state, int spriteIndex=0);
	void Draw();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) override;
	void Update(float deltaTime);
};