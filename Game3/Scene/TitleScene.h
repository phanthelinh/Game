#pragma once
#include "Scene.h"
#include "../Framework/Animation.h"
#include "SceneManager.h"
#include "IntroScene.h"

class TitleScene
	:public Scene
{
public:
	TitleScene();
	~TitleScene();

	virtual void Update(float deltaTime);
	virtual void LoadContent() override;
	virtual void Draw();
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	virtual void OnMouseDown(float x, float y);
private:
	Animation * castle; //position 183,99 //push start 73,129
	Sprite* textPushToStart;
	Sprite* screenSprite;

};
