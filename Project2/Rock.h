#pragma once


#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"

#define ROCKMOVE_HEIGHT 20

#define ROCKMOVE_SPEED 0.1f
#define ROCKMOVE_ACCEL_RUN_Y 0.0005f

#define ROCKMOVE_STATE_MOVE 100

#define ID_ANI_ROCKMOVE 1010


class CRockMove : public CGameObject
{
public:
	CRockMove(float x, float y) : CGameObject(x, y) {}
	CRockMove(float x, float y, float vy);
	void Render();
	void Update(DWORD dt);
};
