#include "Scene.h"



Scene::Scene()
{
	_backColor = 0x000000;
}


Scene::~Scene()
{
	Memory::SafeDelete(_map);
}

D3DCOLOR Scene::GetBackColor()
{
	return _backColor;
}
