#include "Game.h"
#include "Player.h"
#include "debug.h"
#include "Ground.h"

//CPlayer::CPlayer(float x, float y, float vx) :CGameObject(x, y)
//{
//	this->vx = vx;
//};

void CPlayer::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	// simple fall down
	vy += PLAYER_GRAVITY * dt;

	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	DebugOutTitle(L"vx = %0.5f", this->vx);


	// BAD & sinful platform collision handling, see next sample for correct collision handling
	if (y > GROUND)
	{
		vy = 0; y = GROUND;
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;
}

void CPlayer::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (y < GROUND)
	{
		if (nx >= 0) {
			aniId = ID_ANI_PLAYER_JUMP;
		}
		else {
			aniId = ID_ANI_PLAYER_JUMP;
		}
	}
	else if (isLying) {
		if (nx >= 0) {
			aniId = ID_ANI_PLAYER_LIE;
		}
		else {
			aniId = ID_ANI_PLAYER_LIE;
		}
	}
	else if (vx == 0) {
		if (nx >= 0) {
			aniId = ID_ANI_PLAYER_IDLE;
		}
		else aniId = ID_ANI_PLAYER_IDLE;
	}
	else if (vx > 0)
	{
		aniId = ID_ANI_PLAYER_RUNNING;
	}
	else if (vx < 0)
	{
		aniId = ID_ANI_PLAYER_RUNNING;
	}

	if (aniId == -1) aniId = ID_ANI_PLAYER_IDLE;

	float d = 0;
	if (isLying) d = PLAYER_LIE_HEIGHT_ADJUST;

	animations->Get(aniId)->Render(x, y + d);
}
void CPlayer::SetState(int state) {
	switch (state)
	{
	case PLAYER_STATE_RUNNING_RIGHT:
		if (isLying) break;
		maxVx = PLAYER_SPEED;
		ax = PLAYER_ACCEL_RUN_X;
		nx = 1;
		break;
	case PLAYER_STATE_RUNNING_LEFT:
		if (isLying) break;
		maxVx = -PLAYER_SPEED;
		ax = -PLAYER_ACCEL_RUN_X;
		nx = -1;
		break;
	case PLAYER_STATE_JUMP: 
		if (isLying) break;
		if (y == GROUND)
		{
			vy = -PLAYER_JUMP_SPEED_Y;
		}
		break;
			
	/*case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y/2;
		break;*/

	case PLAYER_STATE_LIE: 
		if (y == GROUND) 
		{
			state = PLAYER_STATE_IDLE;
			isLying = true;
			vx = 0; vy = 0;
			y += PLAYER_LIE_HEIGHT_ADJUST;
		}
		break;

	case PLAYER_STATE_LIE_RELEASE:
		isLying = false;
		state = PLAYER_STATE_IDLE;
		y -= PLAYER_LIE_HEIGHT_ADJUST;
		break;

	case PLAYER_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;
	}

	CGameObject::SetState(state);
}

