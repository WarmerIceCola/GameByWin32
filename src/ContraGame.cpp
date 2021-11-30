// ContraGame.cpp : 定义应用程序的入口点。
//
#define _CRT_SECURE_NO_WARNINGS

#include "ContraGame.h"

using namespace std;

#pragma region 全局变量

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;					 // 当前窗体实例
WCHAR szTitle[MAX_LOADSTRING];		 // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING]; // 主窗口类名

HBITMAP bmp_Grass;		 //背景图像资源
HBITMAP bmp_SnowGround;	 //雪山背景图象资源Stage1
HBITMAP bmp_BGStage2;	 //Stage2背景图像资源
HBITMAP bmp_StartButton; //开始按钮图像资源
HBITMAP bmp_IceBlock;	 //冰块障碍块资源
HBITMAP bmp_LevelMenu;	 //关卡选择图像资源
HBITMAP bmp_BGStage3;	 //Stage3BG
HBITMAP bmp_BGStage4;	 //Stage4BG

HBITMAP bmp_Unit_ice1;	 //小王Stage1图像资源
HBITMAP bmp_Unit_ice2;	 //小王Stage1图像资源
HBITMAP bmp_Unit_PTFISH; //胖头鱼图像资源
HBITMAP bmp_Bullet;		 //子弹图像资源

HBITMAP bmp_Background;				 //生成的背景图像
HBITMAP bmp_Background_SnowMountain; //生成雪山背景图像
HBITMAP bmp_Background_LevelMenu;	 //生成关卡选择背景图像
HBITMAP bmp_Background_Stage2;		 //Stage2背景图像

//生成关卡对应图片
HBITMAP bmp_Button_Level1;
HBITMAP bmp_Button_Level2;
HBITMAP bmp_Button_Level3;
HBITMAP bmp_Button_Level4;

//暂停游戏界面按钮图片
HBITMAP bmp_Button_Home;
HBITMAP bmp_Button_Resume;
HBITMAP bmp_Button_Replay;

//主角生命值圆环图片
HBITMAP bmp_Health_20;
HBITMAP bmp_Health_40;
HBITMAP bmp_Health_60;
HBITMAP bmp_Health_80;
HBITMAP bmp_Health_100;

//对话框图片
HBITMAP bmp_Dialog_Stage1;
HBITMAP bmp_Dialog_Stage2;
HBITMAP bmp_Dialog_Stage3;
HBITMAP bmp_Dialog_Stage4;

//Stage2
HBITMAP bmp_Iceball;
HBITMAP bmp_MemoryStage2;
//Stage3
HBITMAP bmp_Background_Stage3;
HBITMAP bmp_FishStage3;
HBITMAP bmp_Unit_ice3;
HBITMAP bmp_Stage3Pointer;

//Stage4
HBITMAP bmp_Background_Stage4;
HBITMAP bmp_Unit_Parrot;
HBITMAP bmp_Unit_GreenPepper;
HBITMAP bmp_Block_Stage4;
HBITMAP bmp_Unit_ice4;

//HelpStage
HBITMAP bmp_HelpButton;
HBITMAP bmp_NextButton;
HBITMAP bmp_PrevButton;
HBITMAP bmp_ReturnButton;
HBITMAP bmp_HelpStage;

Stage *currentStage = NULL;	   //当前场景状态
vector<Unit *> units;		   //单位
vector<Button *> buttons;	   //按钮
vector<Bullet *> bullets;	   //子弹
vector<Block *> BlockOfStage1; //关卡1障碍块
vector<Block *> BlockOfStage2; //关卡2障碍块
vector<Block *> BlockOfStage4; //关卡4障碍块
vector<Event *> Event_Stage1;  //关卡1事件
vector<Event *> Event_Stage2;  //关卡2事件
vector<Event *> Event_Stage3;  //关卡3事件
vector<Event *> Event_Stage4;  //关卡4事件

int mouseX = 0;
int mouseY = 0;
int timeRecordJumpIce = 0;	  //Record Jump Time
int timeRecordJumpPTFish = 0; //Record Jump Time
int timeRec_Shoot_Stage2 = 0; //控制PTFish射击子弹

bool mouseDown = false;
bool keyUpDown = false;
bool keyDownDown = false;
bool keyLeftDown = false;
bool keyRightDown = false;

bool WhetherStop = false; //record whether the game is stopped.

bool UnitInited = false;   //避免人物重复初始化
bool Stage1Inited = false; //避免关卡中障碍块等元素重复初始化
bool Stage2Inited = false; //避免关卡中障碍块等元素重复初始化
bool Stage3Inited = false; //避免关卡中障碍块等元素重复初始化
bool Stage4Inited = false; //避免关卡中障碍块等元素重复初始化
bool Stage5Inited = false; //避免关卡中障碍块等元素重复初始化

bool EventStage1Finished = false;
bool EventStage2Finished = false;
bool EventStage3Finished = false;
bool EventStage4Finished = false;

bool UnitHealth = true;
bool BossHealth = true;

//音乐播放控制
bool LowHealthMPlayed = false;
//对话帧
int Stage1_Dialog_Row = 0;
int Stage2_Dialog_Row = 0;
int Stage3_Dialog_Row = 0;
int Stage4_Dialog_Row = 0;
int HelpStage_Dialog_Row = 1;
//全局运行时间记录
int TimeSum = 0;
//帧

int FRAMES_HOLD[] = {0};
int FRAMES_HOLD_COUNT = 1;
int FRAMES_WALK[] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2};
int FRAMES_WALK_COUNT = 16;
int FRAMES_ATTACK[] = {3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
int FRAMES_ATTACK_COUNT = 24;

//文件流
FILE *txt_Block_Stage1 = fopen("BlockOfStage1.txt", "r");
FILE *txt_Block_Stage2 = fopen("BlockOfStage2.txt", "r");
FILE *txt_Block_Stage4 = fopen("BlockOfStage4.txt", "r");
// TODO: 在此添加其它全局变量

double const PI = acos(double(-1));

#pragma endregion

#pragma region Win32程序框架

// 此代码模块中包含的函数的前向声明:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPWSTR lpCmdLine,
					  _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CONTRAGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONTRAGAME));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CONTRAGAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindow(szWindowClass, szTitle,
							 WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 设置窗口样式，不可改变大小，不可最大化,
							 CW_USEDEFAULT,
							 CW_USEDEFAULT,
							 WINDOW_WIDTH,
							 WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT,
							 nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		// 初始化游戏窗体
		InitGame(hWnd, wParam, lParam);
		break;
	case WM_KEYDOWN:
		// 键盘按下事件
		KeyDown(hWnd, wParam, lParam);
		break;
	case WM_KEYUP:
		// 键盘松开事件
		KeyUp(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		// 鼠标移动事件
		MouseMove(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		// 鼠标左键按下事件
		LButtonDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		// 鼠标左键松开事件
		LButtonUp(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		// 定时器事件
		TimeSum += 20;
		if (currentStage->stageID != STAGE_3)
		{
			if (timeRecordJumpIce != 0 && !WhetherStop)
			{
				timeRecordJumpIce += 30;
				if (timeRecordJumpIce == 481)
				{
					units[0]->vy = UNIT_JUMPINGSPEED;
					keyUpDown = false;
					timeRecordJumpIce = 0;
				}
			}
			if (timeRecordJumpPTFish != 0 && !WhetherStop)
			{
				timeRecordJumpPTFish += 30;
				if (timeRecordJumpPTFish == 481)
				{
					for (int i = 0; i < units.size(); i++)
					{
						if (units[i]->side == UNIT_SIDE_PTFISH)
						{
							units[i]->vy = UNIT_JUMPINGSPEED;
						}
					}
					timeRecordJumpPTFish = 0;
				}
			}
			if (!WhetherStop && bullets.size() != 0)
			{
				for (int i = 0; i < bullets.size(); i++)
				{
					if (bullets[i]->timeRecordOfBullet < 1101)
					{
						bullets[i]->timeRecordOfBullet += 20;
					}
					else
					{
						bullets.erase(bullets.begin() + i, bullets.begin() + i + 1);
					}
				}
			}
		}

		if (currentStage != NULL && currentStage->timerOn)
			TimerUpdate(hWnd, wParam, lParam);
		break;
	case WM_PAINT:
		// 绘图
		Paint(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		fclose(txt_Block_Stage1);
		fclose(txt_Block_Stage2);
		fclose(txt_Block_Stage4);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

#pragma endregion

#pragma region 事件处理函数

// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//加载图像资源
	bmp_Grass = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_GRASS)); //背景图片已更换，为方便保留原名
	bmp_StartButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_START));
	bmp_HelpButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HELP));

	bmp_IceBlock = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_IceBlock));
	bmp_Block_Stage4 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_Block_Stage4));
	bmp_Unit_ice1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ICEUNIT1));
	bmp_Unit_ice2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ICEUNIT2));
	bmp_Unit_ice3 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ICEUNIT3));
	bmp_Unit_ice4 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ICEUNIT4));
	bmp_SnowGround = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SNOWMOUNTAIN)); //BGSTAge1
	bmp_BGStage2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BGStage2));		//BgStage2
	bmp_LevelMenu = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_LEVELMENU));

	bmp_Button_Level1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_LEVEL1));
	bmp_Button_Level2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_LEVEL2));
	bmp_Button_Level3 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_LEVEL3));
	bmp_Button_Level4 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_LEVEL4));

	bmp_Button_Home = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HOME));
	bmp_Button_Resume = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RESUME));
	bmp_Button_Replay = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_REPLAY));

	bmp_Bullet = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BULLET));
	bmp_Unit_PTFISH = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PTFISH));

	bmp_Health_20 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HEALTH20));
	bmp_Health_40 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HEALTH40));
	bmp_Health_60 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HEALTH60));
	bmp_Health_80 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HEALTH80));
	bmp_Health_100 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HEALTH100));

	bmp_Dialog_Stage1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_Stage1Dialog));
	bmp_Dialog_Stage2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_Stage2Dialog));
	bmp_Dialog_Stage3 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_Stage3Dialog));
	bmp_Dialog_Stage4 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_Stage4Dialog));
	//Stage2
	bmp_Iceball = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ICEBALL));
	bmp_MemoryStage2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MemoryStage2));
	//Stage3
	bmp_FishStage3 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_FISHSTAGE3));
	bmp_BGStage3 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BGStage3)); //BgStage3
	bmp_Stage3Pointer = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_Stage3Pointer));
	//Stage4
	bmp_BGStage4 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BGStage4));
	bmp_Unit_GreenPepper = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_GreenPepper));
	bmp_Unit_Parrot = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_Parrot));
	//HelpStage
	bmp_NextButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_NEXT));
	bmp_PrevButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PREV));
	bmp_HelpStage = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HELPSTAGE));
	bmp_ReturnButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RETURN));
	//添加按钮

	Button *startButton = CreateButton(BUTTON_STARTGAME, bmp_StartButton, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
									   100, (WINDOW_HEIGHT - BUTTON_STARTGAME_HEIGHT) / 2);
	Button *HelpButton = CreateButton(BUTTON_HELP, bmp_HelpButton, BUTTON_HELP_WIDTH, BUTTON_HELP_HEIGHT,
									   980, (WINDOW_HEIGHT - BUTTON_HELP_HEIGHT) / 2);
	Button *NextButton = CreateButton(BUTTON_NEXT, bmp_NextButton, NEXT_WIDTH, NEXT_HEIGHT,
									  WINDOW_WIDTH - NEXT_WIDTH - 10, (WINDOW_HEIGHT - NEXT_HEIGHT) / 2);
	Button *PrevButton = CreateButton(BUTTON_PREV, bmp_PrevButton, NEXT_WIDTH, NEXT_HEIGHT,
									  0, (WINDOW_HEIGHT - NEXT_HEIGHT) / 2);
	Button *ReturnButton = CreateButton(BUTTON_RETURN, bmp_ReturnButton, RETURN_WIDTH, RETURN_HEIGHT,
										0, 0);
	Button *Level1button = CreateButton(BUTTON_STAGE1, bmp_Button_Level1, BUTTON_LEVEL_WIDTH, BUTTON_LEVEL_HEIGHT, 110, 138);
	Button *Level2button = CreateButton(BUTTON_STAGE2, bmp_Button_Level2, BUTTON_LEVEL_WIDTH, BUTTON_LEVEL_HEIGHT, 360, 138);
	Button *Level3button = CreateButton(BUTTON_STAGE3, bmp_Button_Level3, BUTTON_LEVEL_WIDTH, BUTTON_LEVEL_HEIGHT, 110, 430);
	Button *Level4button = CreateButton(BUTTON_STAGE4, bmp_Button_Level4, BUTTON_LEVEL_WIDTH, BUTTON_LEVEL_HEIGHT, 360, 430);

	Button *HomeButton = CreateButton(BUTTON_HOME, bmp_Button_Home, BUTTON_STOP_WIDTH, BUTTON_STOP_HEIGHT,
									  (WINDOW_WIDTH - BUTTON_STOP_WIDTH) / 2, 100);
	Button *ResumeButton = CreateButton(BUTTON_RESUME, bmp_Button_Resume, BUTTON_STOP_WIDTH, BUTTON_STOP_HEIGHT,
										(WINDOW_WIDTH - BUTTON_STOP_WIDTH) / 2, 270);
	Button *ReplayButton = CreateButton(BUTTON_REPLAY, bmp_Button_Replay, BUTTON_STOP_WIDTH, BUTTON_STOP_HEIGHT,
										(WINDOW_WIDTH - BUTTON_STOP_WIDTH) / 2, 440);

	Button *MemoryStage2 = CreateButton(BUTTON_MemoryStage2, bmp_MemoryStage2, DIAMOND_WIDTH, DIAMOND_HEIGHT, 900, 200);
	Button *MemoryStage3 = CreateButton(BUTTON_MemoryStage3, bmp_MemoryStage2, DIAMOND_WIDTH, DIAMOND_HEIGHT, 900, 200);
	Button *MemoryStage4 = CreateButton(BUTTON_MemoryStage4, bmp_MemoryStage2, DIAMOND_WIDTH, DIAMOND_HEIGHT, 900, 200);
	buttons.push_back(startButton);
	buttons.push_back(HelpButton);
	buttons.push_back(NextButton);
	buttons.push_back(PrevButton);
	buttons.push_back(ReturnButton);

	buttons.push_back(Level1button);
	buttons.push_back(Level2button);
	buttons.push_back(Level3button);
	buttons.push_back(Level4button);

	buttons.push_back(HomeButton);
	buttons.push_back(ResumeButton);
	buttons.push_back(ReplayButton);

	buttons.push_back(MemoryStage2);
	buttons.push_back(MemoryStage3);
	buttons.push_back(MemoryStage4);

	Event_Stage1.push_back(CreateEvents(STAGE_1, Stage1_PTFishCaught, false));
	Event_Stage2.push_back(CreateEvents(STAGE_2, Stage2_PTFishCollided, false));
	Event_Stage2.push_back(CreateEvents(STAGE_2, Stage2_DiamondClicked, false));
	Event_Stage3.push_back(CreateEvents(STAGE_3, Stage3_CoralCaught, false));
	Event_Stage3.push_back(CreateEvents(STAGE_3, Stage3_CoralSent, false));
	Event_Stage3.push_back(CreateEvents(STAGE_3, Stage3_DiamondClicked, false));
	Event_Stage4.push_back(CreateEvents(STAGE_4, Stage4_BossKilled, false));
	Event_Stage4.push_back(CreateEvents(STAGE_4, Stage4_DiamondClicked, false));
	//初始化背景
	bmp_Background = InitBackGround(hWnd, bmp_Grass);
	bmp_Background_LevelMenu = InitBackGround(hWnd, bmp_LevelMenu);
	bmp_Background_SnowMountain = InitBackGround(hWnd, bmp_SnowGround);
	bmp_Background_Stage2 = InitBackGround(hWnd, bmp_BGStage2);
	bmp_Background_Stage3 = InitBackGround(hWnd, bmp_BGStage3);
	bmp_Background_Stage4 = InitBackGround(hWnd, bmp_BGStage4);
	//初始化开始场景
	InitStage(hWnd, STAGE_STARTMENU);

	//初始化主计时器
	SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);
}

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 0x57: //W
		if (!keyUpDown&&!WhetherStop)
		{
			keyUpDown = true;
			timeRecordJumpIce++;
			units[0]->vy = -UNIT_JUMPINGSPEED;
		}
		if (currentStage->stageID != STAGE_STARTMENU && currentStage->stageID != STAGE_LEVELMENU && currentStage->stageID != HELPSTAGE)
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_JUMPSOUND), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
		}

		break;
	case 0x53: //S
		if (currentStage->stageID == STAGE_3&&!WhetherStop)
		{
			keyDownDown = true;
			units[0]->vy = UNIT_JUMPINGSPEED;
		}
		break;
	case 0x41: //A
		keyLeftDown = true;
		units[0]->vx = -5.0;
		units[0]->direction = UNIT_DIRECT_LEFT;

		break;
	case 0x44: //D
		keyRightDown = true;
		units[0]->vx = 5.0;
		units[0]->direction = UNIT_DIRECT_RIGHT;

		break;
	case 0x51: //Q
		if (units[0]->direction == UNIT_DIRECT_RIGHT)
		{
			units[0]->vx = 5 * UNIT_JUMPINGSPEED;
		}
		else if (units[0]->direction == UNIT_DIRECT_LEFT)
		{
			units[0]->vx = (-5) * UNIT_JUMPINGSPEED;
		}
		if (currentStage->stageID != STAGE_STARTMENU && currentStage->stageID != STAGE_LEVELMENU && currentStage->stageID != HELPSTAGE)
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_QDOWNM), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
		}
		break;
	case VK_ESCAPE:
	{
		WhetherStop = true; //记录游戏已被暂停
		for (int i = 0; i < buttons.size(); i++)
		{
			Button *button = buttons[i];
			if (button->buttonID == BUTTON_HOME || button->buttonID == BUTTON_REPLAY || button->buttonID == BUTTON_RESUME)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	break;
	case VK_RETURN:
	{
		if (currentStage->stageID == STAGE_1)
		{
			if (EventStage1Finished)
			{
				if (Stage1_Dialog_Row <= 3)
				{
					Stage1_Dialog_Row++;
				}
			}
		}
		if (currentStage->stageID == STAGE_2)
		{
			if (EventStage2Finished)
			{
				if (Stage2_Dialog_Row <= 1)
				{
					Stage2_Dialog_Row++;
				}
			}
		}
		if (currentStage->stageID == STAGE_3)
		{
			if (EventStage3Finished)
			{
				if (Stage3_Dialog_Row <= 1)
				{
					Stage3_Dialog_Row++;
				}
			}
		}
		if (currentStage->stageID == STAGE_4)
		{
			if (EventStage4Finished)
			{
				if (Stage4_Dialog_Row <= 12)
				{
					Stage4_Dialog_Row++;
				}
			}
		}
	}
	break;
	default:
		break;
	}
}

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// TODO
	switch (wParam)
	{
	case 0x57:
		/*keyUpDown = false;*/
		/*units[0]->vy = 0;*/
		break;
	case 0x53:
		keyDownDown = false;
		break;
	case 0x41:
		keyLeftDown = false;
		units[0]->vx = 0;

		break;
	case 0x44:
		keyRightDown = false;
		units[0]->vx = 0;
	case 0x51:
		units[0]->vx = 0;
		break;
	default:
		break;
	}
}

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
}

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = true;

	if (bullets.size() < NUM_BULLET && !WhetherStop && (currentStage->stageID == STAGE_1 || currentStage->stageID == STAGE_2 || currentStage->stageID == STAGE_4))
	{
		double difx = mouseX - units[0]->x;
		double dify = mouseY - units[0]->y;
		if (mouseX <= units[0]->x && bullets.size() <= 4)
		{
			bullets.push_back(CreateBullet(UNIT_SIDE_ICEUNIT1, units[0]->x - UNIT_SIZE_X / 2, units[0]->y,
										   UNIT_BULLET_SPEED * sin(atan(difx / abs(dify))), UNIT_BULLET_SPEED * sin(atan(dify / abs(difx))), 1, bmp_Bullet));
		}
		else
		{
			bullets.push_back(CreateBullet(UNIT_SIDE_ICEUNIT1, units[0]->x + UNIT_SIZE_X / 2, units[0]->y,
										   UNIT_BULLET_SPEED * sin(atan(difx / abs(dify))), UNIT_BULLET_SPEED * sin(atan(dify / abs(difx))), 1, bmp_Bullet));
		}
	}

	for (int i = 0; i < buttons.size(); i++)
	{
		Button *button = buttons[i];
		if (button->visible)
		{
			if (button->x <= mouseX && button->x + button->width >= mouseX && button->y <= mouseY && button->y + button->height >= mouseY)
			{
				switch (button->buttonID)
				{ //TODO：判断进入哪个关卡
				case BUTTON_STARTGAME:
				{

					InitStage(hWnd, STAGE_LEVELMENU);
				}
				break;
				case BUTTON_STAGE1:
				{
					if(currentStage->stageID==STAGE_LEVELMENU)
					{
						mciSendString(TEXT("close STARTBM.mp3"), NULL, 0, NULL);
					}
					InitStage(hWnd, STAGE_1);
				}
				break;
				case BUTTON_STAGE2:
				{
					if(currentStage->stageID==STAGE_LEVELMENU)
					{
						mciSendString(TEXT("close STARTBM.mp3"), NULL, 0, NULL);
					}
					InitStage(hWnd, STAGE_2);
				}
				break;
				case BUTTON_STAGE3:
				{
					if(currentStage->stageID==STAGE_LEVELMENU)
					{
						mciSendString(TEXT("close STARTBM.mp3"), NULL, 0, NULL);
					}
					InitStage(hWnd, STAGE_3);
				}
				break;
				case BUTTON_STAGE4:
				{
					if(currentStage->stageID==STAGE_LEVELMENU)
					{
						mciSendString(TEXT("close STARTBM.mp3"), NULL, 0, NULL);
					}
					InitStage(hWnd, STAGE_4);
				}
				break;
				case BUTTON_HOME:
				{
					PlaySound(NULL, NULL, NULL);
					//Background Music Stop
					if (currentStage->stageID == STAGE_2)
					{
						mciSendString(TEXT("close Stage2BM.mp3"), NULL, 0, NULL);
					}
					else if (currentStage->stageID == STAGE_3)
					{
						mciSendString(TEXT("close Stage3BM.mp3"), NULL, 0, NULL);
					}
					else if (currentStage->stageID == STAGE_1)
					{
						mciSendString(TEXT("close Stage1BM.mp3"), NULL, 0, NULL);
					}
					else if (currentStage->stageID == STAGE_4)
					{
						mciSendString(TEXT("close Stage4BM.mp3"), NULL, 0, NULL);
					}
					mciSendString(TEXT("play STARTBM.mp3 repeat"), NULL, 0, NULL);
					WhetherStop = false;
					keyUpDown = false;
					keyDownDown = false;
					keyDownDown = false;
					units.erase(units.begin(), units.end());
					bullets.erase(bullets.begin(), bullets.end());
					for (int i = 0; i < Event_Stage1.size(); i++)
					{
						Event_Stage1[i]->status = false;
					}
					for (int i = 0; i < Event_Stage2.size(); i++)
					{
						Event_Stage2[i]->status = false;
					}
					for (int i = 0; i < Event_Stage3.size(); i++)
					{
						Event_Stage3[i]->status = false;
					}
					for (int i = 0; i < Event_Stage4.size(); i++)
					{
						Event_Stage4[i]->status = false;
					}
					UnitInited = false;
					UnitHealth = true;
					BossHealth = true;
					timeRecordJumpIce = 0;
					timeRecordJumpPTFish = 0;
					timeRec_Shoot_Stage2 = 0;
					EventStage1Finished = false;
					EventStage2Finished = false;
					EventStage3Finished = false;
					EventStage4Finished = false;
					Stage1_Dialog_Row = 0;
					Stage2_Dialog_Row = 0;
					Stage3_Dialog_Row = 0;
					Stage4_Dialog_Row = 0;
					LowHealthMPlayed = false;
					InitStage(hWnd, STAGE_STARTMENU);
					//units.push_back(CreateUnit(UNIT_SIDE_ICEUNIT1, UNIT_TYPE_ICE, 10,550, 100));
				}
				break;
				case BUTTON_RESUME:
				{
					WhetherStop = false;
					//将原场景还原，先去除现有按钮
					for (int i = 0; i < buttons.size(); i++)
					{
						Button *button = buttons[i];
						button->visible = false;
					}
				}
				break;
				case BUTTON_REPLAY:
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE_REPLAY), GetModuleHandle(NULL), SND_RESOURCE | SND_SYNC);//Attension:SND_SYNC
					UnitHealth = true;
					BossHealth = true;
					timeRecordJumpIce = 0;
					timeRecordJumpPTFish = 0;
					timeRec_Shoot_Stage2 = 0;
					WhetherStop = false;
					keyUpDown = false;
					keyDownDown = false;
					units.erase(units.begin(), units.end());
					bullets.erase(bullets.begin(), bullets.end());
					for (int i = 0; i < Event_Stage1.size(); i++)
					{
						Event_Stage1[i]->status = false;
					}
					for (int i = 0; i < Event_Stage2.size(); i++)
					{
						Event_Stage2[i]->status = false;
					}
					for (int i = 0; i < Event_Stage3.size(); i++)
					{
						Event_Stage3[i]->status = false;
					}
					for (int i = 0; i < Event_Stage4.size(); i++)
					{
						Event_Stage4[i]->status = false;
					}
					UnitInited = false;
					EventStage1Finished = false;
					EventStage2Finished = false;
					EventStage3Finished = false;
					EventStage4Finished = false;
					Stage1_Dialog_Row = 0;
					Stage2_Dialog_Row = 0;
					Stage3_Dialog_Row = 0;
					Stage4_Dialog_Row = 0;
					LowHealthMPlayed = false;
					//停止音乐
					PlaySound(NULL, NULL, NULL);
					if (currentStage->stageID == STAGE_2)
					{
						mciSendString(TEXT("close Stage2BM.mp3"), NULL, 0, NULL);
					}
					else if (currentStage->stageID == STAGE_3)
					{
						mciSendString(TEXT("close Stage3BM.mp3"), NULL, 0, NULL);
					}
					else if (currentStage->stageID == STAGE_1)
					{
						mciSendString(TEXT("close Stage1BM.mp3"), NULL, 0, NULL);
					}
					else if (currentStage->stageID == STAGE_4)
					{
						mciSendString(TEXT("close Stage4BM.mp3"), NULL, 0, NULL);
					}
					InitStage(hWnd, currentStage->stageID);
				}
				break;
				case BUTTON_MemoryStage2:
				{
					for (int i = 0; i < Event_Stage2.size(); i++)
					{
						if (Event_Stage2[i]->eventID == Stage2_DiamondClicked)
						{
							Event_Stage2[i]->status = true;
						}
					}
				}
				break;
				case BUTTON_MemoryStage3:
				{
					for (int i = 0; i < Event_Stage3.size(); i++)
					{
						if (Event_Stage3[i]->eventID == Stage3_DiamondClicked)
						{
							Event_Stage3[i]->status = true;
						}
					}
				}
				break;
				case BUTTON_MemoryStage4:
				{
					for (int i = 0; i < Event_Stage4.size(); i++)
					{
						if (Event_Stage4[i]->eventID == Stage4_DiamondClicked)
						{
							Event_Stage4[i]->status = true;
						}
					}
				}
				break;
				case BUTTON_HELP:
					InitStage(hWnd, HELPSTAGE);
					break;
				case BUTTON_PREV:
					HelpStage_Dialog_Row--;
					break;
				case BUTTON_NEXT:
					HelpStage_Dialog_Row++;
					break;
				case BUTTON_RETURN:
					HelpStage_Dialog_Row = 1;
					InitStage(hWnd, STAGE_STARTMENU);
					break;
				}
			}
		}
	}
}

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = false;
}

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (!WhetherStop)
	{
		UpdateUnits(hWnd);
	}
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}

#pragma endregion

#pragma region 其它游戏状态处理函数

//TODO: 添加游戏需要的更多函数

// 添加按钮函数
Button *CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y)
{
	Button *button = new Button();
	button->buttonID = buttonID;
	button->img = img;
	button->width = width;
	button->height = height;
	button->x = x;
	button->y = y;

	button->visible = false;
	return button;
}
Event *CreateEvents(int stageID, int eventID, bool status)
{
	Event *event = new Event();
	event->stageID = stageID;
	event->eventID = eventID;
	event->status = status;
	return event;
}
//添加地砖函数
Block *CreateBlock(HBITMAP img, FILE *is)
{
	Block *block = new Block();
	block->img = img;
	int num = fscanf(is, "%d-%d-%d-%d-%d\n", &block->StageID, &block->x, &block->y, &block->width, &block->height);
	return block;
}
// 添加主角函数
Unit *CreateUnit(int side, int type, int x, int y, double vx, double vy, int health)
{
	Unit *unit = new Unit();
	unit->side = side;

	if (side == UNIT_SIDE_ICEUNIT1)
	{
		unit->img = bmp_Unit_ice1;
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else if (side == UNIT_SIDE_ICEUNIT2)
	{
		unit->img = bmp_Unit_ice2;
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else if (side == UNIT_SIDE_ICEUNIT3)
	{
		unit->img = bmp_Unit_ice3;
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else if (side == UNIT_SIDE_ICEUNIT4)
	{
		unit->img = bmp_Unit_ice4;
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else if (side == UNIT_SIDE_PTFISH)
	{
		unit->img = bmp_Unit_PTFISH;
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else if (side == UNIT_SIDE_ICEBALL)
	{
		unit->img = bmp_Iceball;
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else if (side == UNIT_SIDE_FISHSTAGE3)
	{
		unit->img = bmp_FishStage3;
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else if (side == UNIT_SIDE_GREENPEPPER)
	{
		unit->img = bmp_Unit_GreenPepper;
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else if (side == UNIT_SIDE_PARROT)
	{
		unit->img = bmp_Unit_Parrot;
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	unit->type = type;
	unit->state = UNIT_STATE_HOLD;

	unit->frame_row = type;
	unit->frame_column = unit->direction;

	unit->frame_sequence = FRAMES_HOLD;
	unit->frame_count = FRAMES_HOLD_COUNT;
	unit->frame_id = 0;

	unit->x = x;
	unit->y = y;
	unit->vx = vx;
	unit->vy = vy;
	unit->health = health;
	return unit;
}
//添加子弹函数
Bullet *CreateBullet(int side, int x, int y, double vx, double vy, int timerecord, HBITMAP img)
{
	Bullet *bullet = new Bullet();
	bullet->side = side;
	bullet->x = x;
	bullet->y = y;
	bullet->vx = vx;
	bullet->vy = vy;
	bullet->timeRecordOfBullet = timerecord;
	bullet->img = img;
	return bullet;
}

// 初始化游戏场景函数
void InitStage(HWND hWnd, int stageID)
{

	// 初始化场景实例
	if (currentStage != NULL)
		delete currentStage;

	currentStage = new Stage();
	currentStage->stageID = stageID;

	if (stageID == STAGE_STARTMENU)
	{
		mciSendString(TEXT("play STARTBM.mp3 repeat"), NULL, 0, NULL);
		currentStage->bg = bmp_Background;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;

		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button *button = buttons[i];
			if (button->buttonID == BUTTON_STARTGAME || button->buttonID == BUTTON_HELP)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID == STAGE_LEVELMENU) //TODO：添加多个游戏场景
	{
		currentStage->bg = bmp_Background_LevelMenu;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;

		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button *button = buttons[i];
			if (buttons[i]->buttonID == BUTTON_STAGE1 || buttons[i]->buttonID == BUTTON_STAGE2 || buttons[i]->buttonID == BUTTON_STAGE3 || buttons[i]->buttonID == BUTTON_STAGE4 || buttons[i]->buttonID == BUTTON_STAGE5) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}

	else if (stageID == STAGE_1) //TODO：添加多个游戏场景
	{
		currentStage->bg = bmp_Background_SnowMountain;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;
		
		PlaySound(MAKEINTRESOURCE(IDR_WAVE_STAGESTART), GetModuleHandle(NULL), SND_RESOURCE | SND_SYNC);//Attension:SND_SYNC
		mciSendString(TEXT("play Stage1BM.mp3 repeat"), NULL, 0, NULL);
		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button *button = buttons[i];
			if (false) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
		// 按场景初始化单位
		if (!UnitInited)
		{
			units.push_back(CreateUnit(UNIT_SIDE_ICEUNIT1, UNIT_TYPE_ICE, 10, 600, 0, 0, 100));
			units.push_back(CreateUnit(UNIT_SIDE_PTFISH, UNIT_TYPE_PTFISH, 889, 399, 0, 0, 100));
			UnitInited = true;
			EventStage1Finished = false;
			UnitHealth = true;
			Stage1_Dialog_Row = 0;
		}
		if (!Stage1Inited)
		{
			for (int i = 0; i < NUM_Block_Stage1; i++)
			{
				BlockOfStage1.push_back(CreateBlock(bmp_IceBlock, txt_Block_Stage1));
			}
			Stage1Inited = true;
		}
	}
	else if (stageID == STAGE_2) //TODO：添加多个游戏场景
	{
		currentStage->bg = bmp_Background_Stage2;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;

		PlaySound(MAKEINTRESOURCE(IDR_WAVE_STAGESTART), GetModuleHandle(NULL), SND_RESOURCE | SND_SYNC);//Attension:SND_SYNC
		//播放背景音乐
		mciSendString(TEXT("play Stage2BM.mp3 repeat"), NULL, 0, NULL);
		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button *button = buttons[i];
			if (false) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
		// 按场景初始化单位
		if (!UnitInited)
		{
			units.push_back(CreateUnit(UNIT_SIDE_ICEUNIT2, UNIT_TYPE_ICE, 900, 600, 0, 0, 100));
			units.push_back(CreateUnit(UNIT_SIDE_PTFISH, UNIT_TYPE_PTFISH, 10, 600, 0, 0, 100));
			units.push_back(CreateUnit(UNIT_SIDE_ICEBALL, UNIT_TYPE_ICEBALL, 1208, 60 - ICEBALL_HEIGHT / 2, 0, 0, 100));
			UnitInited = true;
			UnitHealth = true;
			EventStage2Finished = false;
			Stage2_Dialog_Row = 0;
		}
		if (!Stage2Inited)
		{
			for (int i = 0; i < NUM_Block_Stage2; i++)
			{
				BlockOfStage2.push_back(CreateBlock(bmp_IceBlock, txt_Block_Stage2));
			}
			Stage2Inited = true;
		}
	}
	else if (stageID == STAGE_3) //TODO：添加多个游戏场景
	{
		currentStage->bg = bmp_Background_Stage3;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;

		PlaySound(MAKEINTRESOURCE(IDR_WAVE_STAGESTART), GetModuleHandle(NULL), SND_RESOURCE | SND_SYNC);//Attension:SND_SYNC
		//背景音乐
		mciSendString(TEXT("play Stage3BM.mp3 repeat"), NULL, 0, NULL);
		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button *button = buttons[i];
			if (false) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
		// 按场景初始化单位
		if (!UnitInited)
		{
			units.push_back(CreateUnit(UNIT_SIDE_ICEUNIT3, UNIT_TYPE_ICE, 980, 40, 0, 0, 100));
			for (int i = 0; i < 4; i++)
			{
				units.push_back(CreateUnit(UNIT_SIDE_FISHSTAGE3, UNIT_TYPE_FISHSTAGE3, 43 + i * 250, 120, 15.0, 0, 100));
			}
			for (int i = 3; i >= 0; i--)
			{
				units.push_back(CreateUnit(UNIT_SIDE_FISHSTAGE3, UNIT_TYPE_FISHSTAGE3, 59 + i * 250, 240, -15.0, 0, 100));
			}
			for (int i = 0; i < 4; i++)
			{
				units.push_back(CreateUnit(UNIT_SIDE_FISHSTAGE3, UNIT_TYPE_FISHSTAGE3, 37 + i * 250, 390, 15.0, 0, 100));
			}
			for (int i = 3; i >= 0; i--)
			{
				units.push_back(CreateUnit(UNIT_SIDE_FISHSTAGE3, UNIT_TYPE_FISHSTAGE3, 37 + i * 250, 540, -15.0, 0, 100));
			}

			UnitInited = true;
			UnitHealth = true;
			EventStage3Finished = false;
			Stage3_Dialog_Row = 0;
		}
		if (!Stage3Inited)
		{

			Stage3Inited = true;
		}
	}
	else if (stageID == STAGE_4) //TODO：添加多个游戏场景
	{
		currentStage->bg = bmp_Background_Stage4;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;

		PlaySound(MAKEINTRESOURCE(IDR_WAVE_STAGESTART), GetModuleHandle(NULL), SND_RESOURCE | SND_SYNC);//Attension:SND_SYNC
		//背景音乐
		mciSendString(TEXT("play Stage4BM.mp3 repeat"), NULL, 0, NULL);
		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button *button = buttons[i];
			if (false) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
		// 按场景初始化单位
		if (!UnitInited)
		{
			units.push_back(CreateUnit(UNIT_SIDE_ICEUNIT4, UNIT_TYPE_ICE, 40, 600, 0, 0, 100));
			units.push_back(CreateUnit(UNIT_SIDE_PTFISH, UNIT_TYPE_PTFISH, 1000, 352, 0, 0, 500));
			units.push_back(CreateUnit(UNIT_SIDE_PARROT, UNIT_TYPE_PARROT, 200, 129, 0, 0, 100));
			units.push_back(CreateUnit(UNIT_SIDE_GREENPEPPER, UNIT_TYPE_GREENPEPPER, 1130, 98 - UNIT_GREENPEPPER_SIZE_Y / 2, 0, 0, 100));
			UnitInited = true;
			UnitHealth = true;
			EventStage4Finished = false;
			Stage4_Dialog_Row = 0;
		}
		if (!Stage4Inited)
		{
			for (int i = 0; i < NUM_Block_Stage4; i++)
			{
				BlockOfStage4.push_back(CreateBlock(bmp_Block_Stage4, txt_Block_Stage4));
			}
			Stage4Inited = true;
		}
	}
	else if (stageID == HELPSTAGE) //TODO：添加多个游戏场景
	{
		currentStage->bg = bmp_Background_LevelMenu;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;

		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button *button = buttons[i];

			if (HelpStage_Dialog_Row == 1 && (buttons[i]->buttonID == BUTTON_NEXT))
			{
				button->visible = true;
			}
			else if (buttons[i]->buttonID == BUTTON_RETURN) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}

// 刷新单位状态函数
void UpdateUnits(HWND hWnd)
{
	for (int i = 0; i < units.size(); i++)
	{
		Unit *unit = units[i];

		//根据单位类型选择行为函数
		switch (unit->type)
		{
		//case UNIT_TYPE_CASTER:

		//	break;
		case UNIT_TYPE_ICE:
			if (unit->health <= 0)
			{
				//UnitHealth将改变状态，不会二次引发音乐
				if (UnitHealth)
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE_HEALTH0), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
				}
				UnitHealth = false;
				WhetherStop = true;
				for (int i = 0; i < buttons.size(); i++)
				{
					if (buttons[i]->buttonID == BUTTON_HOME || buttons[i]->buttonID == BUTTON_REPLAY)
					{
						buttons[i]->visible = true;
					}
				}
			}
			else if (unit->health > 0 && unit->health <= 20)
			{
				if (!LowHealthMPlayed)
				{
					LowHealthMPlayed = true;
					PlaySound(MAKEINTRESOURCE(IDR_WAVE_LOWHEALTH), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
				}
			}
			UnitBehaviour_ice(unit, currentStage);
			break;
		case UNIT_TYPE_PTFISH:
			UnitBehaviour_PTFISH(unit, currentStage);
			break;
		case UNIT_TYPE_ICEBALL:
			UnitBehaviour_ICEBALL(unit, currentStage);
			break;
		case UNIT_TYPE_FISHSTAGE3:
			UnitBehaviour_FISHSTAGE3(unit, currentStage);
			break;
		case UNIT_TYPE_PARROT:
			UnitBehaviour_PARROT(unit, currentStage);
			break;
		case UNIT_TYPE_GREENPEPPER:
			UnitBehaviour_GREENPEPPER(unit, currentStage);
			break;
		}
	}
	if (bullets.size() != 0)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			UnitBehaviour_Bullet(bullets[i], currentStage);
		}
	}
	if (currentStage->stageID == STAGE_1)
	{
		if (!EventStage1Finished)
		{
			bool flag = true;
			for (int i = 0; i < Event_Stage1.size(); i++)
			{
				if (!Event_Stage1[i]->status)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_SUCCESS), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
				EventStage1Finished = true;
				Stage1_Dialog_Row++;
			}
		}
	}
	else if (currentStage->stageID == STAGE_2)
	{
		if (Event_Stage2[0]->status) //胖头鱼被击中
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i]->buttonID == BUTTON_MemoryStage2)
				{
					buttons[i]->visible = true;
				}
			}
		}
		if (!EventStage2Finished)
		{
			bool flag = true;
			for (int i = 0; i < Event_Stage2.size(); i++)
			{
				if (!Event_Stage2[i]->status)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_SUCCESS), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
				EventStage2Finished = true;
				WhetherStop = true;
				Stage2_Dialog_Row++;
			}
		}
	}
	else if (currentStage->stageID == STAGE_3)
	{
		if (Event_Stage3[0]->status && Event_Stage3[1]->status)
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i]->buttonID == BUTTON_MemoryStage3)
				{
					buttons[i]->visible = true;
				}
			}
		}
		if (!EventStage3Finished)
		{
			bool flag = true;
			for (int i = 0; i < Event_Stage3.size(); i++)
			{
				if (!Event_Stage3[i]->status)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_SUCCESS), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
				EventStage3Finished = true;
				WhetherStop = true;
				Stage3_Dialog_Row++;
			}
		}
	}
	else if (currentStage->stageID == STAGE_4)
	{
		for (int i = 0; i < units.size(); i++)
		{
			if (units[i]->type == UNIT_TYPE_PTFISH && units[i]->health <= 0)
			{
				Event_Stage4[0]->status = true;
			}
		}
		if (Event_Stage4[0]->status)
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i]->buttonID == BUTTON_MemoryStage4)
				{
					buttons[i]->visible = true;
				}
			}
		}
		if (!EventStage4Finished)
		{
			bool flag = true;
			for (int i = 0; i < Event_Stage4.size(); i++)
			{
				if (!Event_Stage4[i]->status)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_SUCCESS), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
				EventStage4Finished = true;
				WhetherStop = true;
				Stage4_Dialog_Row++;
			}
		}
	}
	else if (currentStage->stageID == HELPSTAGE) //TODO：添加多个游戏场景
	{

		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button *button = buttons[i];

			if (HelpStage_Dialog_Row == 1 && (buttons[i]->buttonID == BUTTON_NEXT))
			{
				button->visible = true;
			}
			else if (HelpStage_Dialog_Row >= 2 && HelpStage_Dialog_Row <= 8 && (buttons[i]->buttonID == BUTTON_NEXT || buttons[i]->buttonID == BUTTON_PREV))
			{
				button->visible = true;
			}
			else if (HelpStage_Dialog_Row == 9 && buttons[i]->buttonID == BUTTON_PREV)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
			if (buttons[i]->buttonID == BUTTON_RETURN) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
		}
	}
}

void PreventOutOfWIndow(Unit *unit1, int &x, int &y)
{
	if (y < 40)
	{
		y = 40;
	}
	else if (y > 580)
	{
		if (currentStage->stageID != STAGE_3)
		{
			y = 580;
			if ((unit1->side == UNIT_SIDE_ICEUNIT1 || unit1->side == UNIT_SIDE_ICEUNIT2 || unit1->side == UNIT_SIDE_ICEUNIT3 || unit1->side == UNIT_SIDE_ICEUNIT4) && timeRecordJumpIce != 0)
			{
				timeRecordJumpIce = 0;
				unit1->vy = 0;
			}
			if (unit1->side == UNIT_SIDE_PTFISH && timeRecordJumpPTFish != 0)
			{
				timeRecordJumpPTFish = 0;
				unit1->vy = 0;
			}
		}
		else
		{
			if (y > 600)
			{
				y = 600;
			}
		}
	}
	if (x < 32)
	{
		x = 32;
		if (unit1->type == UNIT_TYPE_FISHSTAGE3)
		{
			unit1->vx *= -1;
		}
	}
	else if (x >= WINDOW_WIDTH - 32)
	{
		x = WINDOW_WIDTH - 32;
		if (unit1->type == UNIT_TYPE_FISHSTAGE3)
		{
			unit1->vx *= -1;
		}
	}
}

void CollisionTest(int stageID, int type, int &x, int &y, double &vx, double &vy)
{
	if (stageID == 1)
	{
		if (vy > 0)
		{
			for (int i = 0; i < BlockOfStage1.size(); i++)
			{
				if (((y + UNIT_SIZE_Y / 2) >= BlockOfStage1[i]->y) && (y - UNIT_SIZE_Y / 2 <= BlockOfStage1[i]->y) && ((x > BlockOfStage1[i]->x - UNIT_SIZE_X / 2) && (x - UNIT_SIZE_X / 2 < BlockOfStage1[i]->x + BlockOfStage1[i]->width)))
				{
					y = BlockOfStage1[i]->y - UNIT_SIZE_Y / 2;
					break;
				}
			}
		}
	}
	else if (stageID == 2)
	{
		if (type == UNIT_TYPE_PTFISH || type == UNIT_TYPE_ICE)
		{
			if (vy > 0)
			{
				for (int i = 0; i < BlockOfStage2.size(); i++)
				{
					if (((y + UNIT_SIZE_Y / 2) >= BlockOfStage2[i]->y) && (y - UNIT_SIZE_Y / 2 <= BlockOfStage2[i]->y) && ((x > BlockOfStage2[i]->x - UNIT_SIZE_X / 2) && (x - UNIT_SIZE_X / 2 < BlockOfStage2[i]->x + BlockOfStage2[i]->width)))
					{
						y = BlockOfStage2[i]->y - UNIT_SIZE_Y / 2;
						break;
					}
				}
			}
		}
		else if (type == UNIT_TYPE_ICEBALL)
		{
			if (vy > 0)
			{
				for (int i = 0; i < BlockOfStage2.size(); i++)
				{
					if (((y + ICEBALL_HEIGHT / 2) >= BlockOfStage2[i]->y) && (y - ICEBALL_HEIGHT / 2 <= BlockOfStage2[i]->y) && ((x > BlockOfStage2[i]->x - ICEBALL_WIDTH / 2) && (x - ICEBALL_WIDTH / 2 < BlockOfStage2[i]->x + BlockOfStage2[i]->width)))
					{
						y = BlockOfStage2[i]->y - ICEBALL_HEIGHT / 2;
						break;
					}
				}
			}
		}
	}
	else if (stageID == STAGE_4)
	{
		if (type == UNIT_TYPE_PTFISH || type == UNIT_TYPE_ICE)
		{
			if (vy > 0)
			{
				for (int i = 0; i < BlockOfStage4.size(); i++)
				{
					if (((y + UNIT_SIZE_Y / 2) >= BlockOfStage4[i]->y) && (y - UNIT_SIZE_Y / 2 <= BlockOfStage4[i]->y) && ((x > BlockOfStage4[i]->x - UNIT_SIZE_X / 2) && (x - UNIT_SIZE_X / 2 < BlockOfStage4[i]->x + BlockOfStage4[i]->width)))
					{
						y = BlockOfStage4[i]->y - UNIT_SIZE_Y / 2;
						break;
					}
				}
			}
		}
		else if (type == UNIT_TYPE_PARROT)
		{
			if (vy > 0)
			{
				for (int i = 0; i < BlockOfStage4.size(); i++)
				{
					if (((y + UNIT_PARROT_SIZE_Y / 2) >= BlockOfStage4[i]->y) && (y - UNIT_PARROT_SIZE_Y / 2 <= BlockOfStage4[i]->y) && ((x > BlockOfStage4[i]->x - UNIT_PARROT_SIZE_X / 2) && (x - UNIT_PARROT_SIZE_X / 2 < BlockOfStage4[i]->x + BlockOfStage4[i]->width)))
					{
						y = BlockOfStage4[i]->y - UNIT_PARROT_SIZE_Y / 2;
						break;
					}
				}
			}
		}
		else if (type == UNIT_TYPE_GREENPEPPER)
		{
			if (vy > 0)
			{
				for (int i = 0; i < BlockOfStage4.size(); i++)
				{
					if (((y + UNIT_GREENPEPPER_SIZE_Y / 2) >= BlockOfStage4[i]->y) && (y - UNIT_GREENPEPPER_SIZE_Y / 2 <= BlockOfStage4[i]->y) && ((x > BlockOfStage4[i]->x - UNIT_GREENPEPPER_SIZE_X / 2) && (x - UNIT_GREENPEPPER_SIZE_X / 2 < BlockOfStage4[i]->x + BlockOfStage4[i]->width)))
					{
						y = BlockOfStage4[i]->y - UNIT_GREENPEPPER_SIZE_Y / 2;
						break;
					}
				}
			}
		}
	}
}
//Stage1抓捕胖头鱼检测
bool CollisionTestStage1(int x, int y)
{
	if ((units[0]->x > x - UNIT_SIZE_X / 2 && units[0]->x < x + UNIT_PTFISH_SIZE_X) && (units[0]->y > y - UNIT_SIZE_Y / 2 && units[0]->y < y + UNIT_PTFISH_SIZE_Y))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//Stage2检测冰球是否碰撞胖头鱼
bool CollisionTestStage2(int x, int y)
{
	for (int i = 0; i < units.size(); i++)
	{
		if (units[i]->side == UNIT_SIDE_ICEBALL)
		{
			if ((units[i]->x + ICEBALL_WIDTH / 2 > x - UNIT_PTFISH_SIZE_X / 2) && (units[i]->x - ICEBALL_WIDTH / 2 < x + UNIT_PTFISH_SIZE_X / 2) && (units[i]->y + ICEBALL_HEIGHT / 2 > y - UNIT_PTFISH_SIZE_Y / 2) && (units[i]->y - ICEBALL_HEIGHT / 2 < y + UNIT_PTFISH_SIZE_Y / 2))
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		}
	}
	return false;
}

void CollisionTestStage3(int x, int y)
{

	if ((units[0]->x + UNIT_SIZE_X / 2 > x - FISH_WIDTH / 2) && (units[0]->x - UNIT_SIZE_X / 2 < x + FISH_WIDTH / 2) && (units[0]->y + UNIT_SIZE_Y / 2 > y - FISH_HEIGHT / 2) && (units[0]->y - UNIT_SIZE_Y / 2 < y + FISH_HEIGHT / 2))
	{
		units[0]->health -= 5;
	}
}

void CollisionIceball(int x, int y, double &vx, double &vy)
{
	if ((units[0]->x > x - UNIT_SIZE_X / 2 && units[0]->x < x + ICEBALL_WIDTH) && (units[0]->y > y - UNIT_SIZE_Y / 2 && units[0]->y < y + ICEBALL_HEIGHT))
	{
		vx = 2 * units[0]->vx;
		vy = UNIT_JUMPINGSPEED;
	}
}

void CollisionBullet(Unit *&unit)
{
	if (unit->type == UNIT_TYPE_ICE)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->side == UNIT_SIDE_PTFISH || bullets[i]->side == UNIT_SIDE_GREENPEPPER || bullets[i]->side == UNIT_SIDE_PARROT)
			{
				if (((unit->y + UNIT_SIZE_Y / 2) >= bullets[i]->y - UNIT_BULLET_SIZE_Y / 2) && (unit->y - UNIT_SIZE_Y / 2 <= bullets[i]->y + UNIT_BULLET_SIZE_Y / 2) && ((unit->x + UNIT_SIZE_X / 2) >= bullets[i]->x - UNIT_BULLET_SIZE_X / 2) && (unit->x - UNIT_SIZE_X / 2 <= bullets[i]->x + UNIT_BULLET_SIZE_X / 2))
				{
					unit->health -= 5;
				}
			}
		}
	}
	else if (unit->type == UNIT_TYPE_PTFISH)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->side == UNIT_SIDE_ICEUNIT1)
			{
				if (((unit->y + UNIT_PTFISH_SIZE_Y / 2) >= bullets[i]->y - UNIT_BULLET_SIZE_Y / 2) && (unit->y - UNIT_PTFISH_SIZE_Y / 2 <= bullets[i]->y + UNIT_BULLET_SIZE_Y / 2) && ((unit->x + UNIT_PTFISH_SIZE_X / 2) >= bullets[i]->x - UNIT_BULLET_SIZE_X / 2) && (unit->x - UNIT_PTFISH_SIZE_X / 2 <= bullets[i]->x + UNIT_BULLET_SIZE_X / 2))
				{
					unit->health -= 10;
				}
			}
		}
	}
}
//单位行为函数
void UnitBehaviour_ice(Unit *unit, Stage *currentstage)
{
	if (currentStage->stageID == STAGE_3)
	{
		if (!keyDownDown)
		{
			unit->vy = -UNIT_JUMPINGSPEED;
		}
	}
	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	//防止角色越界
	PreventOutOfWIndow(unit, unit->x, unit->y);
	if (currentStage->stageID == STAGE_1 || currentStage->stageID == STAGE_2 || currentStage->stageID == STAGE_4)
	{
		CollisionTest(currentstage->stageID, unit->type, unit->x, unit->y, unit->vx, unit->vy);
		CollisionBullet(unit);
	}
	if (currentStage->stageID == STAGE_3)
	{ //1080 530
		if (unit->x >= 1080 && unit->x <= 1130 && unit->y >= 530 && unit->y <= 560)
		{
			for (int i = 0; i < Event_Stage3.size(); i++)
			{
				if (Event_Stage3[i]->eventID == Stage3_CoralCaught)
				{
					Event_Stage3[i]->status = true;
					break;
				}
			}
		}
		if (Event_Stage3[0]->status && unit->x >= 130 && unit->x <= 180 && unit->y >= 300 && unit->y <= 360)
		{ //130 300
			for (int i = 0; i < Event_Stage3.size(); i++)
			{
				if (Event_Stage3[i]->eventID == Stage3_CoralSent)
				{
					Event_Stage3[i]->status = true;
					break;
				}
			}
		}
	}
}

void UnitBehaviour_ICEBALL(Unit *unit, Stage *currentstage)
{

	//动画运行到下一帧

	unit->x += unit->vx;
	unit->y += unit->vy;

	//防止角色越界
	PreventOutOfWIndow(unit, unit->x, unit->y);
	CollisionTest(currentstage->stageID, unit->type, unit->x, unit->y, unit->vx, unit->vy);
	CollisionIceball(unit->x, unit->y, unit->vx, unit->vy);
}

void UnitBehaviour_Bullet(Bullet *bullet, Stage *currentstage)
{

	//动画运行到下一帧
	bullet->x += bullet->vx;
	bullet->y += bullet->vy;
	if (bullet->side == UNIT_SIDE_ICEUNIT1)
	{
		for (int i = 0; i < BlockOfStage4.size(); i++)
		{
			if (((bullet->y + UNIT_BULLET_SIZE_Y / 2) >= BlockOfStage4[i]->y) && (bullet->y - UNIT_BULLET_SIZE_Y / 2 <= BlockOfStage4[i]->y) && ((bullet->x > BlockOfStage4[i]->x - UNIT_BULLET_SIZE_X / 2) && (bullet->x - UNIT_BULLET_SIZE_X / 2 < BlockOfStage4[i]->x + BlockOfStage4[i]->width)))
			{
				bullet->vy *= -1;
				break;
			}
		}
	}

	//防止角色越界
	//PreventOutOfWIndow(unit->x,unit->y);

	//	CollisionTest(currentstage->stageID,unit->x,unit->y,unit->vx,unit->vy);
}

void UnitBehaviour_PTFISH(Unit *unit, Stage *currentstage)
{

	unit->vx = units[0]->vx / 2;
	if (!timeRecordJumpPTFish && units[0]->vy)
	{
		unit->vy = units[0]->vy;
		timeRecordJumpPTFish++;
	}

	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	//防止角色越界
	PreventOutOfWIndow(unit, unit->x, unit->y);

	CollisionTest(currentstage->stageID, unit->type, unit->x, unit->y, unit->vx, unit->vy);

	if (currentStage->stageID == STAGE_1)
	{
		if (CollisionTestStage1(unit->x, unit->y))
		{
			for (int i = 0; i < Event_Stage1.size(); i++)
			{
				if (Event_Stage1[i]->eventID == Stage1_PTFishCaught)
				{
					Event_Stage1[i]->status = true;
				}
			}
		}
	}
	else if (currentStage->stageID == STAGE_2)
	{
		//发射子弹
		srand(time(NULL));
		int temp = rand();
		if (temp % 3 == 0 && bullets.size() < NUM_BULLET)
		{
			double difx = units[0]->x - unit->x;
			double dify = units[0]->y - unit->y;
			if (units[0]->x <= unit->x)
			{
				bullets.push_back(CreateBullet(UNIT_SIDE_PTFISH, unit->x - UNIT_PTFISH_SIZE_X / 2, unit->y,
											   UNIT_BULLET_SPEED * sin(atan(difx / abs(dify))), UNIT_BULLET_SPEED * sin(atan(dify / abs(difx))), 1, bmp_Bullet));
			}
			else
			{
				bullets.push_back(CreateBullet(UNIT_SIDE_PTFISH, unit->x + UNIT_PTFISH_SIZE_X / 2, unit->y,
											   UNIT_BULLET_SPEED * sin(atan(difx / abs(dify))), UNIT_BULLET_SPEED * sin(atan(dify / abs(difx))), 1, bmp_Bullet));
			}
		}
		if (CollisionTestStage2(unit->x, unit->y))
		{
			for (int i = 0; i < Event_Stage2.size(); i++)
			{
				if (Event_Stage2[i]->eventID == Stage2_PTFishCollided)
				{
					Event_Stage2[i]->status = true;
				}
			}
		}
	}
	else if (currentStage->stageID == STAGE_4)
	{
		//发射子弹
		srand(time(NULL));
		int temp = rand();
		if (temp % 3 == 0 && bullets.size() < NUM_BULLET / 2)
		{
			double difx = units[0]->x - unit->x;
			double dify = units[0]->y - unit->y;
			if (units[0]->x <= unit->x)
			{
				bullets.push_back(CreateBullet(UNIT_SIDE_PTFISH, unit->x - UNIT_PTFISH_SIZE_X / 2, unit->y,
											   UNIT_BULLET_SPEED * sin(atan(difx / abs(dify))), UNIT_BULLET_SPEED * sin(atan(dify / abs(difx))), 1, bmp_Bullet));
			}
			else
			{
				bullets.push_back(CreateBullet(UNIT_SIDE_PTFISH, unit->x + UNIT_PTFISH_SIZE_X / 2, unit->y,
											   UNIT_BULLET_SPEED * sin(atan(difx / abs(dify))), UNIT_BULLET_SPEED * sin(atan(dify / abs(difx))), 1, bmp_Bullet));
			}
		}
		CollisionBullet(unit);
	}
}
void UnitBehaviour_PARROT(Unit *unit, Stage *currentstage)
{
	unit->vy = units[0]->vy;
	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	//防止角色越界
	PreventOutOfWIndow(unit, unit->x, unit->y);

	CollisionTest(currentstage->stageID, unit->type, unit->x, unit->y, unit->vx, unit->vy);

	//发射子弹
	srand(time(NULL));
	int temp = rand();
	if (temp % 6 == 0 && bullets.size() < NUM_BULLET_STAGE4 / 3)
	{
		double difx = units[0]->x - unit->x;
		double dify = units[0]->y - unit->y;
		if (units[0]->x <= unit->x)
		{
			bullets.push_back(CreateBullet(UNIT_SIDE_PARROT, unit->x - UNIT_PARROT_SIZE_X / 2, unit->y,
										   UNIT_BULLET_SPEED * sin(atan(difx / abs(dify))), UNIT_BULLET_SPEED * sin(atan(dify / abs(difx))), 1, bmp_Bullet));
		}
		else
		{
			bullets.push_back(CreateBullet(UNIT_SIDE_PARROT, unit->x + UNIT_PARROT_SIZE_X / 2, unit->y,
										   UNIT_BULLET_SPEED * sin(atan(difx / abs(dify))), UNIT_BULLET_SPEED * sin(atan(dify / abs(difx))), 1, bmp_Bullet));
		}
	}
}
void UnitBehaviour_GREENPEPPER(Unit *unit, Stage *currentstage)
{
	unit->vy = units[0]->vy;
	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	//防止角色越界
	PreventOutOfWIndow(unit, unit->x, unit->y);

	CollisionTest(currentstage->stageID, unit->type, unit->x, unit->y, unit->vx, unit->vy);

	//发射子弹
	srand(time(NULL));
	int temp = rand();
	if (temp % 4 == 0 && bullets.size() < NUM_BULLET_STAGE4 / 3)
	{
		double difx = units[0]->x - unit->x;
		double dify = units[0]->y - unit->y;
		if (units[0]->x <= unit->x)
		{
			bullets.push_back(CreateBullet(UNIT_SIDE_GREENPEPPER, unit->x - UNIT_GREENPEPPER_SIZE_X / 2, unit->y,
										   UNIT_BULLET_SPEED * sin(atan(difx / abs(dify))), UNIT_BULLET_SPEED * sin(atan(dify / abs(difx))), 1, bmp_Bullet));
		}
		else
		{
			bullets.push_back(CreateBullet(UNIT_SIDE_GREENPEPPER, unit->x + UNIT_GREENPEPPER_SIZE_X / 2, unit->y,
										   UNIT_BULLET_SPEED * sin(atan(difx / abs(dify))) / 2, UNIT_BULLET_SPEED * sin(atan(dify / abs(difx))) / 2, 1, bmp_Bullet));
		}
	}
}
void UnitBehaviour_FISHSTAGE3(Unit *unit, Stage *currentstage)
{

	unit->x += unit->vx;
	unit->y += unit->vy;
	if (unit->vx > 0)
	{
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else if (unit->vx < 0)
	{
		unit->direction = UNIT_DIRECT_LEFT;
	}

	//防止角色越界
	PreventOutOfWIndow(unit, unit->x, unit->y);
	if (currentStage->stageID == STAGE_3)
	{
		CollisionTestStage3(unit->x, unit->y);
	}
}
#pragma endregion

#pragma region 绘图函数
// 绘图函数
void Paint(HWND hWnd)
{

	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, blankBmp);

	// 绘制背景到缓存
	//SelectObject(hdc_loadBmp, currentStage->bg);
	SelectObject(hdc_loadBmp, bmp_Background);

	BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

	// 按场景分类绘制内容到缓存
	if (currentStage->stageID == STAGE_STARTMENU)
	{
		SelectObject(hdc_loadBmp, bmp_Background);
		TransparentBlt(
			hdc_memBuffer, 0, 0,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, 0, WINDOW_HEIGHT * (HelpStage_Dialog_Row - 1), WINDOW_WIDTH, WINDOW_HEIGHT,
			RGB(200, 200, 200));
	}
	else if (currentStage->stageID == STAGE_LEVELMENU) //TODO：添加多个游戏场景
	{
		SelectObject(hdc_loadBmp, bmp_Background_LevelMenu);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
	}
	else if (currentStage->stageID == HELPSTAGE) //TODO：添加多个游戏场景
	{
		SelectObject(hdc_loadBmp, bmp_Background_LevelMenu);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
		SelectObject(hdc_loadBmp, bmp_HelpStage);
		TransparentBlt(
			hdc_memBuffer, 0, 0,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, 0, WINDOW_HEIGHT * (HelpStage_Dialog_Row - 1), WINDOW_WIDTH, WINDOW_HEIGHT,
			RGB(250, 250, 254));
	}
	else if (currentStage->stageID == STAGE_1) //TODO：添加多个游戏场景
	{
		SelectObject(hdc_loadBmp, bmp_Background_SnowMountain);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
		// 绘制单位到缓存
		for (int i = 0; i < units.size(); i++)
		{
			Unit *unit = units[i];
			if (unit->side == UNIT_SIDE_ICEUNIT1)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * UNIT_SIZE_X, unit->y - 0.5 * UNIT_SIZE_Y,
					UNIT_SIZE_X, UNIT_SIZE_Y,
					hdc_loadBmp, UNIT_SIZE_X * (unit->direction - 1), 0, UNIT_SIZE_X, UNIT_SIZE_Y,
					RGB(255, 255, 255));
				switch (unit->health)
				{
				case 20:
					SelectObject(hdc_loadBmp, bmp_Health_20);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
					break;
				case 40:
					SelectObject(hdc_loadBmp, bmp_Health_40);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
					break;
				case 60:
					SelectObject(hdc_loadBmp, bmp_Health_60);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
					break;
				case 80:
					SelectObject(hdc_loadBmp, bmp_Health_80);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
					break;
				case 100:
					SelectObject(hdc_loadBmp, bmp_Health_100);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
					break;
				}
			}

			else if (unit->side == UNIT_SIDE_PTFISH)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * UNIT_PTFISH_SIZE_X, unit->y - 0.5 * UNIT_PTFISH_SIZE_Y,
					UNIT_PTFISH_SIZE_X, UNIT_PTFISH_SIZE_Y,
					hdc_loadBmp, UNIT_PTFISH_SIZE_X * (unit->direction - 1), 0, UNIT_PTFISH_SIZE_X, UNIT_PTFISH_SIZE_Y,
					RGB(255, 255, 255));
			}
		}
		for (int i = 0; i < BlockOfStage1.size(); i++)
		{
			Block *block = BlockOfStage1[i];
			SelectObject(hdc_loadBmp, block->img);
			TransparentBlt(
				hdc_memBuffer, block->x, block->y,
				block->width, block->height,
				hdc_loadBmp, 0, 0, block->width, block->height,
				RGB(255, 255, 255));
		}
	}
	else if (currentStage->stageID == STAGE_2) //TODO：添加多个游戏场景
	{
		SelectObject(hdc_loadBmp, bmp_Background_Stage2);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
		// 绘制单位到缓存
		for (int i = 0; i < units.size(); i++)
		{
			Unit *unit = units[i];
			if (unit->side == UNIT_SIDE_ICEUNIT2)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * UNIT_SIZE_X, unit->y - 0.5 * UNIT_SIZE_Y,
					UNIT_SIZE_X, UNIT_SIZE_Y,
					hdc_loadBmp, UNIT_SIZE_X * (unit->direction - 1), 0, UNIT_SIZE_X, UNIT_SIZE_Y,
					RGB(255, 255, 255));
				if (unit->health > 0 && unit->health <= 20)
				{
					SelectObject(hdc_loadBmp, bmp_Health_20);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 20 && unit->health <= 40)
				{
					SelectObject(hdc_loadBmp, bmp_Health_40);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 40 && unit->health <= 60)
				{
					SelectObject(hdc_loadBmp, bmp_Health_60);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 60 && unit->health <= 80)
				{
					SelectObject(hdc_loadBmp, bmp_Health_80);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 80 && unit->health <= 100)
				{
					SelectObject(hdc_loadBmp, bmp_Health_100);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
			}
			else if (unit->side == UNIT_SIDE_PTFISH)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * UNIT_PTFISH_SIZE_X, unit->y - 0.5 * UNIT_PTFISH_SIZE_Y,
					UNIT_PTFISH_SIZE_X, UNIT_PTFISH_SIZE_Y,
					hdc_loadBmp, UNIT_PTFISH_SIZE_X * (unit->direction - 1), 0, UNIT_PTFISH_SIZE_X, UNIT_PTFISH_SIZE_Y,
					RGB(255, 255, 255));
			}
			else if (unit->side == UNIT_SIDE_ICEBALL)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * ICEBALL_WIDTH, unit->y - 0.5 * ICEBALL_HEIGHT,
					ICEBALL_WIDTH, ICEBALL_HEIGHT,
					hdc_loadBmp, 0, 0, ICEBALL_WIDTH, ICEBALL_HEIGHT,
					RGB(255, 255, 255));
			}
		}
		//绘制障碍块到缓存
		for (int i = 0; i < BlockOfStage2.size(); i++)
		{
			Block *block = BlockOfStage2[i];
			SelectObject(hdc_loadBmp, block->img);
			TransparentBlt(
				hdc_memBuffer, block->x, block->y,
				block->width, block->height,
				hdc_loadBmp, 0, 0, block->width, block->height,
				RGB(255, 255, 255));
		}
	}
	else if (currentStage->stageID == STAGE_3) //TODO：添加多个游戏场景
	{
		SelectObject(hdc_loadBmp, bmp_Background_Stage3);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
		// 绘制单位到缓存
		for (int i = 0; i < units.size(); i++)
		{
			Unit *unit = units[i];
			if (unit->side == UNIT_SIDE_ICEUNIT3)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * UNIT_SIZE_X, unit->y - 0.5 * UNIT_SIZE_Y,
					UNIT_SIZE_X, UNIT_SIZE_Y,
					hdc_loadBmp, UNIT_SIZE_X * (unit->direction - 1), 0, UNIT_SIZE_X, UNIT_SIZE_Y,
					RGB(255, 255, 255));
				if (unit->health > 0 && unit->health <= 20)
				{
					SelectObject(hdc_loadBmp, bmp_Health_20);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 20 && unit->health <= 40)
				{
					SelectObject(hdc_loadBmp, bmp_Health_40);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 40 && unit->health <= 60)
				{
					SelectObject(hdc_loadBmp, bmp_Health_60);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 60 && unit->health <= 80)
				{
					SelectObject(hdc_loadBmp, bmp_Health_80);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 80 && unit->health <= 100)
				{
					SelectObject(hdc_loadBmp, bmp_Health_100);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
			}
			else if (unit->side == UNIT_SIDE_FISHSTAGE3)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * FISH_WIDTH, unit->y - 0.5 * FISH_HEIGHT,
					FISH_WIDTH, FISH_HEIGHT,
					hdc_loadBmp, (unit->direction - 1) * FISH_WIDTH, 0, FISH_WIDTH, FISH_HEIGHT,
					RGB(255, 255, 255));
			}
		}
		if (Event_Stage3[0]->status)
		{
			SelectObject(hdc_loadBmp, bmp_Stage3Pointer);
			TransparentBlt(
				hdc_memBuffer, 1020, 100,
				Stage3Pointer_WIDTH, Stage3Pointer_HEIGHT,
				hdc_loadBmp, 0, 0, Stage3Pointer_WIDTH, Stage3Pointer_HEIGHT,
				RGB(255, 255, 255));
		}
	}
	else if (currentStage->stageID == STAGE_4) //TODO：添加多个游戏场景
	{
		SelectObject(hdc_loadBmp, bmp_Background_Stage4);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
		// 绘制单位到缓存
		for (int i = 0; i < units.size(); i++)
		{
			Unit *unit = units[i];
			if (unit->side == UNIT_SIDE_ICEUNIT4)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * UNIT_SIZE_X, unit->y - 0.5 * UNIT_SIZE_Y,
					UNIT_SIZE_X, UNIT_SIZE_Y,
					hdc_loadBmp, UNIT_SIZE_X * (unit->direction - 1), 0, UNIT_SIZE_X, UNIT_SIZE_Y,
					RGB(255, 255, 255));
				if (unit->health > 0 && unit->health <= 20)
				{
					SelectObject(hdc_loadBmp, bmp_Health_20);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 20 && unit->health <= 40)
				{
					SelectObject(hdc_loadBmp, bmp_Health_40);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 40 && unit->health <= 60)
				{
					SelectObject(hdc_loadBmp, bmp_Health_60);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 60 && unit->health <= 80)
				{
					SelectObject(hdc_loadBmp, bmp_Health_80);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 80 && unit->health <= 100)
				{
					SelectObject(hdc_loadBmp, bmp_Health_100);
					TransparentBlt(
						hdc_memBuffer, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
			}
			else if (unit->side == UNIT_SIDE_PTFISH)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * UNIT_PTFISH_SIZE_X, unit->y - 0.5 * UNIT_PTFISH_SIZE_Y,
					UNIT_PTFISH_SIZE_X, UNIT_PTFISH_SIZE_Y,
					hdc_loadBmp, UNIT_PTFISH_SIZE_X * (unit->direction - 1), 0, UNIT_PTFISH_SIZE_X, UNIT_PTFISH_SIZE_Y,
					RGB(255, 255, 255));
				if (unit->health > 0 && unit->health <= 100)
				{
					SelectObject(hdc_loadBmp, bmp_Health_20);
					TransparentBlt(
						hdc_memBuffer, 1280 - HEALTHRING_WIDTH, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 100 && unit->health <= 200)
				{
					SelectObject(hdc_loadBmp, bmp_Health_40);
					TransparentBlt(
						hdc_memBuffer, 1280 - HEALTHRING_WIDTH, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 200 && unit->health <= 300)
				{
					SelectObject(hdc_loadBmp, bmp_Health_60);
					TransparentBlt(
						hdc_memBuffer, 1280 - HEALTHRING_WIDTH, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 300 && unit->health <= 400)
				{
					SelectObject(hdc_loadBmp, bmp_Health_80);
					TransparentBlt(
						hdc_memBuffer, 1280 - HEALTHRING_WIDTH, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
				else if (unit->health > 400 && unit->health <= 500)
				{
					SelectObject(hdc_loadBmp, bmp_Health_100);
					TransparentBlt(
						hdc_memBuffer, 1280 - HEALTHRING_WIDTH, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT,
						hdc_loadBmp, 0, 0, HEALTHRING_WIDTH, HEALTHRING_HEIGHT, RGB(255, 255, 255));
				}
			}
			else if (unit->side == UNIT_SIDE_PARROT)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * UNIT_PARROT_SIZE_X, unit->y - 0.5 * UNIT_PARROT_SIZE_Y,
					UNIT_PARROT_SIZE_X, UNIT_PARROT_SIZE_Y,
					hdc_loadBmp, 0, 0, UNIT_PARROT_SIZE_X, UNIT_PARROT_SIZE_Y,
					RGB(255, 255, 255));
			}
			else if (unit->side == UNIT_SIDE_GREENPEPPER)
			{
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * UNIT_GREENPEPPER_SIZE_X, unit->y - 0.5 * UNIT_GREENPEPPER_SIZE_Y,
					UNIT_GREENPEPPER_SIZE_X, UNIT_GREENPEPPER_SIZE_Y,
					hdc_loadBmp, 0, 0, UNIT_GREENPEPPER_SIZE_X, UNIT_GREENPEPPER_SIZE_Y,
					RGB(255, 255, 255));
			}
		}
		//绘制障碍块到缓存
		for (int i = 0; i < BlockOfStage4.size(); i++)
		{
			Block *block = BlockOfStage4[i];
			SelectObject(hdc_loadBmp, block->img);
			TransparentBlt(
				hdc_memBuffer, block->x, block->y,
				block->width, block->height,
				hdc_loadBmp, 0, 0, block->width, block->height,
				RGB(255, 255, 255));
		}
	}
	//绘制子弹到缓存
	for (int i = 0; i < bullets.size(); i++)
	{
		Bullet *bullet = bullets[i];
		SelectObject(hdc_loadBmp, bullet->img);
		TransparentBlt(
			hdc_memBuffer, bullet->x, bullet->y,
			UNIT_BULLET_SIZE_X, UNIT_BULLET_SIZE_Y,
			hdc_loadBmp, 0, 0, UNIT_BULLET_SIZE_X, UNIT_BULLET_SIZE_Y,
			RGB(255, 255, 255));
	}
	//绘制对话框到缓存
	if (EventStage1Finished)
	{
		if (Stage1_Dialog_Row <= 3)
		{
			SelectObject(hdc_loadBmp, bmp_Dialog_Stage1);
			TransparentBlt(
				hdc_memBuffer, WINDOW_WIDTH / 2 - DIALOG_WIDTH / 2, WINDOW_HEIGHT / 2 - DIALOG_HEIGHT / 2,
				DIALOG_WIDTH, DIALOG_HEIGHT,
				hdc_loadBmp, 0, (Stage1_Dialog_Row - 1) * DIALOG_HEIGHT, DIALOG_WIDTH, DIALOG_HEIGHT,
				RGB(1, 1, 1));
		}
		else
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i]->buttonID == BUTTON_HOME || buttons[i]->buttonID == BUTTON_REPLAY)
				{
					buttons[i]->visible = true;
				}
			}
		}
	}
	else if (EventStage2Finished)
	{
		if (Stage2_Dialog_Row == 1)
		{
			SelectObject(hdc_loadBmp, bmp_Dialog_Stage2);
			TransparentBlt(
				hdc_memBuffer, WINDOW_WIDTH / 2 - DIALOG_WIDTH / 2, WINDOW_HEIGHT / 2 - DIALOG_HEIGHT / 2,
				DIALOG_WIDTH, DIALOG_HEIGHT,
				hdc_loadBmp, 0, (Stage2_Dialog_Row - 1) * DIALOG_HEIGHT, DIALOG_WIDTH, DIALOG_HEIGHT,
				RGB(1, 1, 1));
		}
		else if (Stage2_Dialog_Row == 2)
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i]->buttonID == BUTTON_HOME || buttons[i]->buttonID == BUTTON_REPLAY)
				{
					buttons[i]->visible = true;
				}
			}
		}
	}
	else if (EventStage3Finished)
	{
		if (Stage3_Dialog_Row == 1)
		{
			SelectObject(hdc_loadBmp, bmp_Dialog_Stage3);
			TransparentBlt(
				hdc_memBuffer, WINDOW_WIDTH / 2 - DIALOG_WIDTH / 2, WINDOW_HEIGHT / 2 - DIALOG_HEIGHT / 2,
				DIALOG_WIDTH, DIALOG_HEIGHT,
				hdc_loadBmp, 0, (Stage3_Dialog_Row - 1) * DIALOG_HEIGHT, DIALOG_WIDTH, DIALOG_HEIGHT,
				RGB(1, 1, 1));
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i]->buttonID == BUTTON_MemoryStage3)
				{
					buttons[i]->visible = false;
					break;
				}
			}
		}
		else if (Stage3_Dialog_Row == 2)
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i]->buttonID == BUTTON_HOME || buttons[i]->buttonID == BUTTON_REPLAY)
				{
					buttons[i]->visible = true;
				}
			}
		}
	}
	else if (EventStage4Finished)
	{
		if (Stage4_Dialog_Row <= 12)
		{
			SelectObject(hdc_loadBmp, bmp_Dialog_Stage4);
			TransparentBlt(
				hdc_memBuffer, WINDOW_WIDTH / 2 - DIALOG_WIDTH / 2, WINDOW_HEIGHT / 2 - DIALOG_HEIGHT / 2,
				DIALOG_WIDTH, DIALOG_HEIGHT,
				hdc_loadBmp, 0, (Stage4_Dialog_Row - 1) * DIALOG_HEIGHT, DIALOG_WIDTH, DIALOG_HEIGHT,
				RGB(1, 1, 1));
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i]->buttonID == BUTTON_MemoryStage4)
				{
					buttons[i]->visible = false;
					break;
				}
			}
		}
		else if (Stage4_Dialog_Row == 13)
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i]->buttonID == BUTTON_HOME || buttons[i]->buttonID == BUTTON_REPLAY)
				{
					buttons[i]->visible = true;
				}
			}
		}
	}

	// 绘制按钮到缓存

	for (int i = 0; i < buttons.size(); i++)
	{
		Button *button = buttons[i];
		if (button->visible)
		{
			SelectObject(hdc_loadBmp, button->img);
			TransparentBlt(
				hdc_memBuffer, button->x, button->y,
				button->width, button->height,
				hdc_loadBmp, 0, 0, button->width, button->height,
				RGB(255, 255, 255));
		}
	}

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}

// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src)
{

	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP bmp_output = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, bmp_output);

	//加载资源
	SelectObject(hdc_loadBmp, bmp_src);
	TransparentBlt(
		hdc_memBuffer, 0, 0,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		hdc_loadBmp, 0, 0,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		RGB(255, 255, 255));

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);

	return bmp_output;
}

#pragma endregion