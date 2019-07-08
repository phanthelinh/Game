#pragma once
#include "Scene.h"
#include "../Framework/Sprite.h"

class TitleScene :public Scene
{
	Sprite* back;
public:
	TitleScene();
	

	// Inherited via Scene
	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

	virtual void OnKeyDown(int keyCode) override;

	virtual void OnKeyUp(int keyCode) override;

	virtual void ReleaseAll() override;

};
