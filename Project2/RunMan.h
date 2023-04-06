#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define RUNMAN_WIDTH 20

#define RUNMAN_SPEED 0.1f 
#define RUNMAN_ACCEL_RUN_X  0.0005f

#define RUNMAN_GRAVITY			0.002f

#define RUNMAN_STATE_IDLE 0

#define RUNMAN_STATE_RUNNING_LEFT  100
#define RUNMAN_STATE_RUNNING_RIGHT 200

#define RUNMAN_DIE 300






#pragma region ANIMATION_ID

#define ID_ANI_RUNMAN_IDLE 400

#define ID_ANI_RUNMAN_RUNNING 500
#define ID_ANI_RUNMAN_DIE 600

#pragma endregion

#define GROUND_Y 160.0f

class CRunMan : public CGameObject
{
	boolean isLying;
	float maxVx;
	float ax;
	float vx;
public:
	CRunMan(float x, float y) : CGameObject(x, y)
	{
		isLying = false;
		maxVx = 0.0f;
		ax = 0.0f;
	}

	CRunMan(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};