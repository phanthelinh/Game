#pragma once
#include "../GlobalVar.h"
#include "../Framework/GameMap.h"
#include "../Framework/Camera.h"
class Scene
{

public:
	Scene();
	virtual ~Scene();

	virtual void Update(float deltaTime) = 0;
	virtual void LoadContent() = 0;
	virtual void Draw() = 0;
	virtual void OnKeyDown(int keyCode) = 0;
	virtual void OnKeyUp(int keyCode) = 0;
	virtual void OnMouseDown(float x, float y) = 0;

	D3DCOLOR GetBackColor();

protected:
	D3DCOLOR _backColor;
	GameMap* _map;
};

