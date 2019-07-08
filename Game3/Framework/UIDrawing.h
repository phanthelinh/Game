#pragma once
#include "../GlobalVar.h"

class UIDrawing
{
public:
	UIDrawing();
	~UIDrawing();
	struct vertex
	{
		FLOAT x, y, z, rhw;
		DWORD color;
	};
	static void DrawingText(const char* text, RECT rect, DWORD format = DT_CENTER);
	static void DrawFilledBox(float x, float y, float w, float h, DWORD color);
};