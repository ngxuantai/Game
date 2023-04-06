#pragma once


#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"

#define ID_ANI_GROUND 1000

#define GROUND 160.0F

class CGround : public CGameObject
{
public:
	CGround(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};