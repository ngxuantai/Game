#include "Ground.h"

void CGround::Render()
{
	CAnimations* ani = CAnimations::GetInstance();
	ani->Get(ID_ANI_GROUND)->Render(x, y);
}