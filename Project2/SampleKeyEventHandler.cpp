#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Player.h"
#include "dinput.h"

extern CPlayer* player;

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		player->SetState(PLAYER_STATE_JUMP);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	/*case DIK_S:
		player->SetState(MARIO_STATE_RELEASE_JUMP);
		break;*/
	case DIK_DOWN:
		player->SetState(PLAYER_STATE_LIE_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		
		player->SetState(PLAYER_STATE_RUNNING_RIGHT);
					
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		player->SetState(PLAYER_STATE_RUNNING_LEFT);
	}
	else
		player->SetState(PLAYER_STATE_IDLE);

	// Sitting state has higher priority 
	if (game->IsKeyDown(DIK_DOWN))
	{
		player->SetState(PLAYER_STATE_LIE);
	}

}