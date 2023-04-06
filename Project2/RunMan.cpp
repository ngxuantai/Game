#include "Game.h"
#include "RunMan.h"
#include "debug.h"

CRunMan::CRunMan(float x, float y, float vx):CGameObject(x, y)
{
	this->vx = vx;
}

//void CRunMan::Update(DWORD dt)
//{
//	x += vx * dt;
//	y += vy * dt;
//
//	// simple fall down
//	vy += RUNMAN_GRAVITY * dt;
//
//	vx += ax * dt;
//
//	if (abs(vx) > abs(maxVx)) vx = maxVx;
//
//	DebugOutTitle(L"vx = %0.5f", this->vx);
//
//
//	// BAD & sinful platform collision handling, see next sample for correct collision handling
//	if (y > GROUND_Y)
//	{
//		vy = 0; y = GROUND_Y;
//	}
//
//	// simple screen edge collision!!!
//	if (vx > 0 && x > 290) x = 290;
//	if (vx < 0 && x < 0) x = 0;
//}


void CRunMan::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - RUNMAN_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - RUNMAN_WIDTH)
		{
			x = (float)(BackBufferWidth - RUNMAN_WIDTH);
		}
	}
}

void CRunMan::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (vx == 0) {
		if (nx >= 0) {
			aniId = ID_ANI_RUNMAN_IDLE;
		}
		else aniId = ID_ANI_RUNMAN_IDLE;
	}
	else if (vx > 0)
	{
		aniId = ID_ANI_RUNMAN_RUNNING;
	}
	else if (vx < 0)
	{
		aniId = ID_ANI_RUNMAN_RUNNING;
	}

	if (aniId == -1) aniId = ID_ANI_RUNMAN_IDLE;

	float d = 0;
	/*if (isLying) d = PLAYER_LIE_HEIGHT_ADJUST;*/

	animations->Get(aniId)->Render(x, y + d);
}
void CRunMan::SetState(int state) {
	switch (state)
	{
	case RUNMAN_STATE_RUNNING_RIGHT:
		maxVx = RUNMAN_SPEED;
		ax = RUNMAN_ACCEL_RUN_X;
		nx = 1;
		break;
	case RUNMAN_STATE_RUNNING_LEFT:
		maxVx = -RUNMAN_SPEED;
		ax = -RUNMAN_ACCEL_RUN_X;
		nx = -1;
		break;


	case RUNMAN_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;
	}

	CGameObject::SetState(state);
}

