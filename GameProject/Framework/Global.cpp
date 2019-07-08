#include "Global.h"

Global* Global::_instance = NULL;

Global* Global::GetInstance()
{
	if (_instance)
	{
		return _instance;
	}
	else
	{
		_instance = new Global();
		return _instance;
	}
}

