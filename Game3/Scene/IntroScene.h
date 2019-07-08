#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "DemoScene.h"

class IntroScene
	:public Scene
{
public:
	IntroScene();
	~IntroScene();
	// Inherited via Scene
	virtual void LoadContent() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void OnKeyDown(int keyCode) override;
	virtual void OnKeyUp(int keyCode) override;
	virtual void OnMouseDown(float x, float y) override;
private:
	Sprite * screenSprite;
	Animation* playerRun;
	Sprite* playerComingIn;
	bool	changingScene;
	float	previousTime;
};
