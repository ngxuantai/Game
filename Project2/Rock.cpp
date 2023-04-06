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
	int aniId = -1;
	
	aniId = ID_ANI_ROCKMOVE;

	float d = 0;
	/*if (isLying) d = PLAYER_LIE_HEIGHT_ADJUST;*/

	animations->Get(aniId)->Render(x, y + d);
}


