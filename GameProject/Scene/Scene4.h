#pragma once
#include <vector>
#include <unordered_set>
#include <iostream>
#include "Scene.h"
#include "../Framework/Animation.h"
#include "../Framework/GameMap.h"
#include "../GameComponents/Player/Player.h"
#include "../GameComponents/Items/ItemsContainer.h"
#include "../Framework/Grid.h"
#include "../Framework/Util.h"
#include "../GameComponents/Enemy/Domesto.h"
#include "../GameComponents/Enemy/WizardBoss.h"
#include "../GameComponents/Enemy/RunningMan.h"
#include "../GameComponents/Enemy/Tank.h"
#include "../GameComponents//Enemy/DynamiteNapalm.h"

class Scene4:public Scene
{
private:
	GameMap*	map;
	std::unordered_set<GameObject*> visibleObject;
	std::vector<GameObject*> listObject;
	DynamiteNapalm* boss;
	bool isSpawned = false;
	bool		shieldInserted;
	int			currentLevel;
	DWORD		timePause;
	bool		isGamePause;
public:
	Scene4();
	~Scene4();

	// Inherited via Scene
	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

	virtual void OnKeyDown(int keyCode) override;

	virtual void OnKeyUp(int keyCode) override;

	virtual void ReleaseAll() override;
	void CheckCollision(BoundingBox player, std::unordered_set<GameObject*> listObj, float deltaTime);
	void ReloadResources(int level);

	void SaveGridToFile(int level);
	void LoadGridFromFile(int level);


	
};
