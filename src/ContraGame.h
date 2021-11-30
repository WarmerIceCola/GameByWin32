#pragma once

#pragma region 头文件引用

// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <stdio.h>


// 资源头文件
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")			//图象处理的函数接口，例如：透明色的位图的绘制TransparentBlt函数

//音乐头文件
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")	
// TODO:  在此处引用程序需要的其他头文件
#include <vector>
#include <math.h>


#pragma endregion


#pragma region 宏定义

#define WINDOW_TITLEBARHEIGHT	32			//标题栏高度
#define WINDOW_WIDTH			1280		//游戏窗口宽度
#define WINDOW_HEIGHT			672			//游戏窗口高度


#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_1					1		//第一个游戏场景的ID
#define STAGE_2					2		//第二个游戏场景的ID
#define STAGE_3					3		//第三个游戏场景的ID
#define STAGE_4					4		//第四个游戏场景的ID
#define STAGE_5					5		//第五个游戏场景的ID
#define HELPSTAGE				6		//帮助场景ID
#define STAGE_LEVELMENU         2001	//关卡选择场景的ID

//SIZEINFO
#define UNIT_SIZE_X				40		//单位的宽度
#define UNIT_SIZE_Y				80		//单位的高度
#define UNIT_LAST_FRAME			11		//单位的动画帧最大值
#define UNIT_BULLET_SIZE_X		32		//子弹宽度
#define UNIT_BULLET_SIZE_Y		32		//子弹高度
#define UNIT_PTFISH_SIZE_X		100		//胖头鱼宽度
#define UNIT_PTFISH_SIZE_Y		120		//胖头鱼高度
#define UNIT_PARROT_SIZE_X		40		//胡萝卜宽度
#define	UNIT_PARROT_SIZE_Y		96		//胡萝卜高度
#define	UNIT_GREENPEPPER_SIZE_X	40		//青椒宽度
#define	UNIT_GREENPEPPER_SIZE_Y	98		//青椒高度

//单位阵营定义
#define UNIT_SIDE_RED			10000	//红方
#define UNIT_SIDE_BLUE			10000	//蓝方
#define UNIT_SIDE_ICEUNIT1      10001   //小王1
#define UNIT_SIDE_ICEUNIT2      10002   //小王2
#define UNIT_SIDE_ICEUNIT3		10003	//小王3
#define UNIT_SIDE_ICEUNIT4		10004	//小王4
#define UNIT_SIDE_BULLET		10005	//子弹
#define UNIT_SIDE_PTFISH		10006	//胖头鱼
#define UNIT_SIDE_ICEBALL		10007	//冰球
#define UNIT_SIDE_FISHSTAGE3	10008	//Stage3Fish
#define	UNIT_SIDE_PARROT		10009	//Parrot
#define	UNIT_SIDE_GREENPEPPER	10010	//Green Pepper


//单位类型定义
#define UNIT_TYPE_ICE		    1		//小王
#define UNIT_TYPE_BULLET		2		//子弹
#define UNIT_TYPE_PTFISH		3		//胖头鱼
#define UNIT_TYPE_ICEBALL		4		//冰球
#define UNIT_TYPE_FISHSTAGE3	5		//Stage3Fish		
#define UNIT_TYPE_PARROT		6		//Parrot
#define	UNIT_TYPE_GREENPEPPER	7		//GreenPepper

//单位状态定义
#define UNIT_STATE_HOLD			0		//静止
#define UNIT_STATE_WALK			1		//行走
#define UNIT_STATE_ATTACK		2		//攻击

//单位方向定义
#define UNIT_DIRECT_RIGHT		1		//向右
#define UNIT_DIRECT_LEFT		2		//向左

//事件ID定义
#define Stage1_PTFishCaught		20000	//胖头鱼被冰冰抓获
#define Stage2_PTFishCollided	20001	//胖头鱼被冰球撞击
#define Stage2_DiamondClicked	20002	//记忆钻石被点击
#define Stage2_IceHealth0		20003	//冰冰血量为零
#define Stage3_CoralCaught		20004	//采集珊瑚成功
#define Stage3_CoralSent		20005	//珊瑚运送成功
#define Stage3_DiamondClicked	20006	//Stage3记忆钻石被点击
#define	Stage4_BossKilled		20007	//PTFISHBoss defeated
#define	Stage4_DiamondClicked	20008	//Stage4记忆钻石被点击	
//背景
#define BG_SRC_COUNT			6		//背景资源数量
#define BG_COLUMNS				16		//背景列数
#define BG_ROWS					12		//背景行数
#define BG_ROWS_SKY				3		//背景天空行数
#define BG_ROWS_LAND			9		//背景地面行数
#define BG_CELL_WIDTH			64		//背景单格宽度
#define BG_CELL_HEIGHT			64		//背景单格高度

//障碍块
#define NUM_Block_Stage1     	22       //Stage1障碍块数量
#define NUM_Block_Stage2     	27      //Stage2障碍块数量
#define	NUM_Block_Stage4		31		//Stage4障碍块数量

//子弹
#define NUM_BULLET				5		//子弹数量	
#define NUM_BULLET_STAGE4		15		//子弹数量ForStage4

//其它定义
#define BUTTON_STARTGAME			1000	//开始游戏按钮ID
#define BUTTON_STARTGAME_WIDTH		200		//开始游戏按钮宽度
#define BUTTON_STARTGAME_HEIGHT		56		//开始游戏按钮高度
#define BUTTON_HELP_WIDTH			150		//帮助按钮宽度
#define BUTTON_HELP_HEIGHT			54		//帮助按钮高度
#define BUTTON_LEVEL_WIDTH			200		//关卡按钮宽度
#define BUTTON_LEVEL_HEIGHT			170		//关卡按钮高度
#define BUTTON_STOP_WIDTH			376		//暂停界面所有按钮宽度
#define BUTTON_STOP_HEIGHT			150		//暂停界面所有按钮高度		
#define HEALTHRING_WIDTH			100		//生命环宽度
#define HEALTHRING_HEIGHT			100		//生命环高度
#define RETURN_WIDTH				54		//返回箭头宽度
#define RETURN_HEIGHT				50		//返回箭头高度
#define NEXT_WIDTH					50		//下一张箭头宽度
#define NEXT_HEIGHT					50		//下一张箭头高度

#define BUTTON_STAGE1				1001	//关卡1游戏按钮ID
#define BUTTON_STAGE2				1002	//关卡2游戏按钮ID
#define BUTTON_STAGE3				1003	//关卡3游戏按钮ID
#define BUTTON_STAGE4				1004	//关卡4游戏按钮ID
#define BUTTON_STAGE5				1005	//关卡5游戏按钮ID
#define BUTTON_HELP					1006	//帮助界面ID
#define BUTTON_NEXT					1007	//NEXT箭头ID
#define BUTTON_PREV					1008	//PREV箭头ID
#define BUTTON_RETURN				1009	//RETURN箭头ID
#define BUTTON_HOME					2001	//暂停界面回到主页按钮ID
#define BUTTON_RESUME				2002	//暂停界面恢复游戏按钮ID
#define BUTTON_REPLAY				2003	//暂停界面重新开始游戏按钮ID
#define BUTTON_MemoryStage2			3002	//Stage2记忆钻石图标
#define BUTTON_MemoryStage3			3003	//Stage3记忆钻石图标
#define	BUTTON_MemoryStage4			3004	//Stage4记忆钻石图标

#define TIMER_GAMETIMER				1		//游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE		20		//默认计时器刷新间隔的毫秒数
#define UNIT_SPEED					3.0		//单位行走速度	
#define UNIT_JUMPINGSPEED          	10.0    //unit跳跃速度
#define UNIT_BULLET_SPEED			30.0	//子弹飞行速度

#define DIALOG_WIDTH				960		//对话框宽度
#define DIALOG_HEIGHT				540		//对话框高度

#define ICEBALL_WIDTH				80		//冰球宽度
#define ICEBALL_HEIGHT				54		//冰球高度

#define	DIAMOND_WIDTH				100		//记忆钻石宽度
#define DIAMOND_HEIGHT				80		//记忆钻石高度

#define FISH_WIDTH					44		//Stage3中鱼的宽度
#define FISH_HEIGHT					32		//Stage3中鱼的高度

#define Stage3Pointer_WIDTH			200		//STAGE3Pointer宽度
#define Stage3Pointer_HEIGHT		100		//STAGE3Pointer高度
#pragma endregion


#pragma region 结构体声明

// 场景结构体
struct Stage
{
	int stageID;		//场景编号
	HBITMAP bg;			//背景图片
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）

};


// 按钮结构体
struct Button
{
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
};
//地砖结构体
struct Block
{
	int StageID;	//场景编号
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
};


// 单位结构体
struct Unit
{
	HBITMAP img;	//图片

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;		//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几个


	int side;		//单位阵营
	int type;		//单位类型
	int state;		//单位状态
	int direction;	//单位方向

	int originx;
	int originy;

	int x;			//坐标x
	int y;			//坐标y
	double vx;		//速度x
	double vy;		//速度y
	int health;		//生命值
};
struct Bullet
{
	HBITMAP img;	//图片
	int side;
	int x;			//坐标x
	int y;			//坐标y
	double vx;		//速度x
	double vy;		//速度y
	int timeRecordOfBullet;			//Record Bullet Move Time
};

struct Event
{
	int stageID;	//场景序号
	int eventID;
	bool status;
};




//TODO: 添加游戏需要的更多种数据（地物、砖块等）


#pragma endregion


#pragma region 事件处理函数声明


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

#pragma endregion


#pragma region 其它游戏状态处理函数声明

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

//添加对话框函数
Event* CreateEvents(int stageID,int eventID,bool status);

// 添加单位函数
Unit* CreateUnit(int side, int type, int x, int y, double vx,double vy ,int health);
//添加子弹函数
Bullet* CreateBullet(int side,int x,int y,double vx,double vy,int timerecord,HBITMAP img);
//添加障碍块
Block *CreateBlock(HBITMAP img,FILE* is);


// 初始化场景函数
void InitStage(HWND hWnd, int stageID);

// 刷新单位状态函数
void UpdateUnits(HWND hWnd);



//单位行为函数
void UnitBehaviour_ice(Unit* unit,Stage* currentstage);
void UnitBehaviour_Bullet(Bullet* bullet,Stage* currentstage);
void UnitBehaviour_PTFISH(Unit* unit, Stage* currentstage);
void UnitBehaviour_ICEBALL(Unit* unit, Stage* currentstage);
void UnitBehaviour_FISHSTAGE3(Unit* unit,Stage* currentstage);
void UnitBehaviour_PARROT(Unit* unit,Stage* currentstage);
void UnitBehaviour_GREENPEPPER(Unit* unit,Stage* currentstage);
//避免角色离开窗口函数
void PreventOutOfWIndow(Unit* unit1,int &x , int &y);
//碰撞检测函数
void CollisionTest(int stageID, int type,int &x, int &y,double &vx,double &vy);
//Stage1中检测PTFish是否被抓获函数
bool CollisionTestStage1(int x,int y);
//Stage2中检测ice是否撞击iceball
void CollisionIceball(int x,int y,double &vx,double &vy);
//Stage2中检测冰球是否碰撞胖头鱼
bool CollisionTestStage2(int x,int y);
//Stage3中检测鱼是否撞击冰冰
void CollisionTestStage3(int x, int y);
//检测子弹是否击中物体
void CollisionBullet(Unit* &unit);
//TODO: 添加游戏需要的更多函数


#pragma endregion 


#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src);

#pragma endregion