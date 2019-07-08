#include "SceneManager.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager * SceneManager::GetInstance()
{
	if(_instance)
	{
		return _instance;
	}
	else
	{
		_instance = new SceneManager();
		return _instance;
	}
}

Scene * SceneManager::GetCurrentScene()
{
	return _curScene;
}

void SceneManager::ChangeScene(Scene * targetScene)
{
	_curScene->ReleaseAll();
	_curScene = nullptr;
	_curScene = targetScene;
}

void SceneManager::ReplaceScene(Scene* scene)
{
	delete _curScene;
	_curScene = scene;
}
