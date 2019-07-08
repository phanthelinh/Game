#pragma once
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	static SceneManager* GetInstance();
	Scene* GetCurrentScene();
	void Update(float deltaTime);
	void ReplaceScene(Scene* scene);
	void Release();
private:
	static SceneManager* _instance;
	Scene* _currentScene;
};

