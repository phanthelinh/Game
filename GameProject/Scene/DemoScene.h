#pragma once
#include "Scene.h"
#include "../Framework/Animation.h"
#include "../Framework/GameMap.h"
#include "../GameComponents/Player/Player.h"
#include <vector>
#include "../Framework/Grid.h"
#include<vector>
#include "../Framework/Animation.h"

class DemoScene:public Scene
{
private:
	Sprite*		back;
	GameMap*	map;
	Grid* grid;
	std::vector<GameObject*> listObject;
public:
	DemoScene();
	~DemoScene();

	// Inherited via Scene
	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

	virtual void OnKeyDown(int keyCode) override;

	virtual void OnKeyUp(int keyCode) override;

	virtual void ReleaseAll() override;
	void CheckCollision(BoundingBox player, std::vector<GameObject*> listObj, float deltaTime);
};
