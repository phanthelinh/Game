#pragma once
#include "GameObject.h"

class Ground : 
	public GameObject 
{
private:
public:
	Ground(RECT r);
	Ground(float x, float y, float width, float height);
	~Ground();
	void Update(float deltaTime);
	void Draw();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) override;
	virtual BoundingBox GetBoundingBox() override;
	RECT GetBound();
	void Release();
};
