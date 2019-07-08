#pragma once
#include "Scene.h"
#include "DemoScene.h"

#define SCENES	SceneManager::GetInstance()
class SceneManager
{
private:
	static SceneManager* _instance;
	Scene*				_curScene = new DemoScene();
public:
	//Get current instance SceneManager
	static SceneManager* GetInstance();			

	//Get the current scene of the game
	Scene*	GetCurrentScene();			
	//Change to another scene
	void	ChangeScene(Scene* targetScene);
	//replace current scene with another
	void ReplaceScene(Scene* scene);
};
