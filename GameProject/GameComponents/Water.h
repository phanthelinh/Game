#pragma once
#include "GameObject.h"
class Water :
	public GameObject
{
private:
public:
	Water(RECT r);
	Water(float x, float y, float width, float height);
	~Water();
	void Update(float deltaTime);
	void Draw();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) override;
	virtual BoundingBox GetBoundingBox() override;
	void Release();
};