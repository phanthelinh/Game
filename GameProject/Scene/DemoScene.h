#pragma once
#include <vector>
#include <unordered_set>
#include "Scene.h"
#include "../Framework/Animation.h"
#include "../Framework/GameMap.h"
#include "../GameComponents/Player/Player.h"
#include "../GameComponents/Items/ItemsContainer.h"
#include "../Framework/Util.h"
#include "../GameComponents/Effect/Explode.h"

class DemoScene:public Scene
{
private:
	GameMap*	map;
	std::unordered_set<ItemsContainer*> itemsContainer;
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

};
