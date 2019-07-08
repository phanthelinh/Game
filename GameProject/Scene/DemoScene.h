#pragma once
#include "Scene.h"
#include "../Framework/Animation.h"
#include "../Framework/GameMap.h"

class DemoScene:public Scene
{
private:
	Sprite*		back;
	Animation*	simon;
	GameMap*	map;
public:
	DemoScene();
	~DemoScene();

	// Inherited via Scene
	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

	virtual void OnKeyDown(int keyCode) override;

	virtual void OnKeyUp(int keyCode) override;

	virtual void ReleaseAll() override;

};
