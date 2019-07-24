#pragma once
#include "Scene.h"
#include "../Framework/Animation.h"
#include "../Framework/GameMap.h"
#include "../GameComponents/Player/Player.h"
#include "../GameComponents/Items/ItemsContainer.h"
#include "../Framework/Grid.h"
#include <unordered_set>
#include "../Framework/Animation.h"
#include "../Framework/Util.h"

class DemoScene:public Scene
{
private:
	Sprite*		back;
	GameMap*	map;
	std::unordered_set<ItemsContainer*> itemsContainer;
	std::vector<GameObject*> listObject;
	std::vector<RECT> lstItemContainerRect;
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
