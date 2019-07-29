#pragma once
#include <vector>
#include <unordered_set>
#include "Scene.h"
#include "../Framework/Animation.h"
#include "../Framework/GameMap.h"
#include "../GameComponents/Player/Player.h"
#include "../GameComponents/Items/ItemsContainer.h"
#include "../Framework/Grid.h"
#include "../Framework/Util.h"
#include "../Framework/Grid.h"
#include "../GameComponents/Enemy/WizardBoss.h"

class DemoScene:public Scene
{
private:
	GameMap*	map;
	std::unordered_set<GameObject*> itemsContainer;
	std::vector<GameObject*> listObject;
	std::vector<RECT> lstItemContainerRect;
	WizardBoss* boss;
public:
	DemoScene();
	~DemoScene();

	// Inherited via Scene
	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

	virtual void OnKeyDown(int keyCode) override;

	virtual void OnKeyUp(int keyCode) override;

	virtual void ReleaseAll() override;
	void CheckCollision(BoundingBox player, std::unordered_set<GameObject*> listObj, float deltaTime);
};
