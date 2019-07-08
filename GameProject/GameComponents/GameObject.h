#pragma once
#include "../Framework/Global.h"

enum Tag{ Simon, Enemy, Ground };

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	Tag tag;									
	float spawnX, spawnY;
	float posX, posY;							
	float vX, vY;								
	int width, height;							
	bool isReverse;								
	bool isDead;

	virtual D3DXVECTOR3 GetPosition();
	virtual RECT GetBound();
	void Update(float deltaTime);
	bool IsCollide(RECT r);
	virtual void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) = 0;
};