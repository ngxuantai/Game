#include "Game.h"
#include "Rock.h"
#include "debug.h"

CRockMove::CRockMove(float x, float y, float vy) :CGameObject(x, y)
{
	this->vy = vy;
}

void CRockMove::Update(DWORD dt)
{
	y += vy * dt;

	int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (y <= 0 || y >= BackBufferHeight - ROCKMOVE_HEIGHT) {

		vy = -vy;

		if (y <= 0)
		{
			y = 0;
		}
		else if (y >= BackBufferHeight - ROCKMOVE_HEIGHT)
		{
			y = (float)(BackBufferHeight - ROCKMOVE_HEIGHT);
		}
	}
}

void CRockMove::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_ROCKMOVE)->Render(x, y);
}

CRockRoll::CRockRoll(float x, float y, float vx) :CGameObject(x, y)
{
	this->vx = vx;
}

void CRockRoll::Update(DWORD dt)
{
	x += -vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0) {
		x = BackBufferWidth;
	}
}

void CRockRoll::Render()
{
	CAnimations* ani = CAnimations::GetInstance();
	ani->Get(ID_ANI_ROCKROLL)->Render(x, y);
}


