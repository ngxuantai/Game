#include "GameObject.h"
#include <D3DX10.h>
#include "Game.h"
#include "debug.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	state = -1;
}
