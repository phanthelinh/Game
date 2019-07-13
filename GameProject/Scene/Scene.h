#pragma once
#include <map>
class Scene
{
protected:
	std::map<int, bool> keys;
public:
	Scene();

	//Update Scene
	virtual void Update(float deltaTime) = 0;	
	//Draw components in scene
	virtual void Draw() = 0;
	//Handle of key down event
	virtual void OnKeyDown(int keyCode) = 0;
	//Handle of key up event
	virtual void OnKeyUp(int keyCode) = 0;
	//Release memory
	virtual void ReleaseAll() = 0;				
};
