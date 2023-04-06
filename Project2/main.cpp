
#include <windows.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Animation.h"
#include "Animations.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Player.h"
#include "RunMan.h"
#include "Ground.h"
#include "Rock.h"


#include "SampleKeyEventHandler.h"

#define WINDOW_CLASS_NAME L"Contra"
#define MAIN_WINDOW_TITLE L"Contra"
#define WINDOW_ICON_PATH L"mario.ico"


#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255, 0.0f)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_PLAYER_MOVE 0
#define ID_TEX_PLAYER_JUMP 10
#define ID_TEX_PLAYER_STAND 20
#define ID_TEX_RUNMAN 30
#define ID_TEX_GROUND 100
#define ID_TEX_ROCKMOVE 110

//#define ID_SPRITE_BRICK 20001

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_PLAYER_MOVE TEXTURES_DIR "\\bill_move.png"
#define TEXTURE_PATH_PLAYER_JUMP TEXTURES_DIR "\\bill_jump.png"
#define TEXTURE_PATH_PLAYER_STAND TEXTURES_DIR "\\bill_stand.png"
#define TEXTURE_PATH_RUNMAN TEXTURES_DIR "\\run_man.png"
#define TEXTURE_PATH_GROUND TEXTURES_DIR "\\ground.png"
#define TEXTURE_PATH_ROCKMOVE TEXTURES_DIR "\\rock_move.png"

#define PLAYER_START_X 10.0f
#define PLAYER_START_Y 10.0f


#define RUNMAN_START_X 10.0f
#define RUNMAN_START_Y 80.0f
#define RUNMAN_START_VX 0.05f

#define GROUNDX 16.0f
#define GROUNDY GROUND + 32.0f

#define ROCKMOVE_START_X 250.0f
#define ROCKMOVE_START_Y 80.0f
#define ROCKMOVE_START_VY 0.05f

CPlayer* player = NULL;
CRunMan* runMan = NULL;
CGround* ground = NULL;
CRockMove* rockMove = NULL;

CSampleKeyHandler* keyHandler;

vector<LPGAMEOBJECT> objects;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_PLAYER_MOVE, TEXTURE_PATH_PLAYER_MOVE);
	textures->Add(ID_TEX_PLAYER_JUMP, TEXTURE_PATH_PLAYER_JUMP);
	textures->Add(ID_TEX_PLAYER_STAND, TEXTURE_PATH_PLAYER_STAND);
	textures->Add(ID_TEX_RUNMAN, TEXTURE_PATH_RUNMAN);
	textures->Add(ID_TEX_GROUND, TEXTURE_PATH_GROUND);
	textures->Add(ID_TEX_ROCKMOVE, TEXTURE_PATH_ROCKMOVE);

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();


	//TEXPLAYERMOVE
	LPTEXTURE texPlayerMove = textures->Get(ID_TEX_PLAYER_MOVE);

	////RUNNING RIGHT
	sprites->Add(10001, 1, 6, 21, 41, texPlayerMove);
	sprites->Add(10002, 29, 6, 49, 41, texPlayerMove);
	sprites->Add(10003, 58, 6, 78, 41, texPlayerMove);
	sprites->Add(10004, 85, 6, 105, 41, texPlayerMove);
	sprites->Add(10005, 115, 6, 135, 41, texPlayerMove);

	////RUNNING LEFT
	sprites->Add(10011, 1, 6, 21, 41, texPlayerMove);
	sprites->Add(10012, 29, 6, 49, 41, texPlayerMove);
	sprites->Add(10013, 58, 6, 78, 41, texPlayerMove);
	sprites->Add(10014, 85, 6, 105, 41, texPlayerMove);
	sprites->Add(10015, 115, 6, 135, 41, texPlayerMove);

	

	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(ID_ANI_PLAYER_IDLE, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(ID_ANI_PLAYER_IDLE, ani);

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	animations->Add(ID_ANI_PLAYER_RUNNING, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	ani->Add(10015);
	animations->Add(ID_ANI_PLAYER_RUNNING, ani);


	//TEXPLAYERJUMP
	LPTEXTURE texPlayerJump = textures->Get(ID_TEX_PLAYER_JUMP);
	
	////JUMP
	sprites->Add(10021, 2, 0, 22, 20, texPlayerJump);
	sprites->Add(10022, 23, 0, 43, 20, texPlayerJump);
	sprites->Add(10023, 44, 0, 64, 20, texPlayerJump);
	sprites->Add(10024, 65, 0, 85, 20, texPlayerJump);

	ani = new CAnimation(100);
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	ani->Add(10024);
	animations->Add(ID_ANI_PLAYER_JUMP, ani);

	//TEXPLAYERSTAND
	LPTEXTURE texPlayerStand = textures->Get(ID_TEX_PLAYER_STAND);

	////LIE
	sprites->Add(10031, 134, 29, 169, 46, texPlayerStand);

	ani = new CAnimation(100);
	ani->Add(10031);
	animations->Add(ID_ANI_PLAYER_LIE, ani);

	//TEXRUNMAN
	LPTEXTURE texRunMan = textures->Get(ID_TEX_RUNMAN);

	sprites->Add(10041, 4, 0, 24, 35, texRunMan);
	sprites->Add(10042, 25, 0, 45, 35, texRunMan);
	sprites->Add(10043, 48, 0, 68, 35, texRunMan);
	sprites->Add(10044, 74, 0, 94, 35, texRunMan);
	sprites->Add(10045, 97, 0, 117, 35, texRunMan);
	sprites->Add(10046, 121, 0, 141, 35, texRunMan);
	/*sprites->Add(10047, 146, 0, 166, 35, texRunMan);
	sprites->Add(10048, 169, 0, 189, 35, texRunMan);*/

	ani = new CAnimation(100);
	ani->Add(10041);
	ani->Add(10042);
	ani->Add(10043);
	ani->Add(10044);
	ani->Add(10045);
	ani->Add(10046);
	/*ani->Add(10047);
	ani->Add(10048);*/
	animations->Add(ID_ANI_RUNMAN_RUNNING, ani);

	//TEXGROUND
	LPTEXTURE texGround = textures->Get(ID_TEX_GROUND);

	sprites->Add(10051, 0, 0, 31, 31, texGround);

	ani = new CAnimation(100);
	ani->Add(10051);
	animations->Add(ID_ANI_GROUND, ani);


	//TEXROCKMOVE

	LPTEXTURE texRockMove = textures->Get(ID_TEX_ROCKMOVE);

	sprites->Add(10061, 0, 0, 31, 31, texRockMove);

	ani = new CAnimation(100);
	ani->Add(10061);
	animations->Add(ID_ANI_ROCKMOVE, ani);



	for (int i = 0; i < 50; i++)
	{
		ground = new CGround(GROUNDX + i * 31, GROUNDY);
		objects.push_back(ground);
	}

	/*int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	for (int i = 0; i < 50; i++)
	{
		if (i * 31 > BackBufferWidth)
			break;
		ground = new CGround(RUNMAN_START_X + i * 31 + 100, RUNMAN_START_Y + 35);
		objects.push_back(ground);
	}*/

	player = new CPlayer(PLAYER_START_X, PLAYER_START_Y);
	objects.push_back(player);
	runMan = new CRunMan(RUNMAN_START_X, RUNMAN_START_Y, RUNMAN_START_VX);
	objects.push_back(runMan);
	rockMove = new CRockMove(ROCKMOVE_START_X, ROCKMOVE_START_Y, ROCKMOVE_START_VY);
	objects.push_back(rockMove);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Update(dt);
	}
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render();
	}

	spriteHandler->End();
	pSwapChain->Present(0, 0);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			CGame::GetInstance()->ProcessKeyboard();
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDebugWindow(hWnd);

	CGame* game = CGame::GetInstance();
	game->Init(hWnd, hInstance);

	keyHandler = new CSampleKeyHandler();
	game->InitKeyboard(keyHandler);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	LoadResources();

	Run();

	return 0;
}