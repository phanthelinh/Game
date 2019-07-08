#include "SceneManager.h"


SceneManager* SceneManager::_instance = NULL;

SceneManager::SceneManager()
{
	_currentScene = nullptr;
}


SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
	if (!_instance)
		_instance = new SceneManager();
	return _instance;
}

Scene * SceneManager::GetCurrentScene()
{
	return _currentScene;
}

void SceneManager::Update(float deltaTime)
{
	_currentScene->Update(deltaTime);
}

void SceneManager::ReplaceScene(Scene * scene)
{
	Memory::SafeDelete(_currentScene);
	_currentScene = scene;
}

void SceneManager::Release()
{
	Memory::SafeDelete(_currentScene);
	Memory::SafeDelete(_instance);
}
