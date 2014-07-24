#ifndef _REFEH_
#define _REFEH_
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

static const int TAG_OBSTALCE = 890;
//Banding障碍物
static const int OB_BANDING = 88;
static const int BANDING_HEIGHT = 80;
static const int BANDING_INTERVAL = 40;
static const string PIC_BANDING = "Obst\\banding.png";
static const int BAND_WITDH = 185;
static const int BAND_H = 32;

//Wall障碍物
static const int OB_WALL  = 99;
static const string PIC_WALL = "bga.png";
static const int MAX_WALL_HEIGHT = 100;
static const int MIN_WALL_HEIGHT = 50;
static const int WALL_WIDTH = 30;
static const int MIN_WALL_INTERVAL = 300;
static const int MAX_WALL_INTERVAL = 700;

//Missile障碍物
static const int OB_MISSILE = 111;
static const string PIC_MISSILE = "DQIV.png";
static const int MAX_MISSILE_OFFSET = 40;

//一般障碍物
static const int MI_FIREBALL = 5;
static const int MAX_INTERVAL = 70;		//障碍物最大间隔
static const int INIT_POSITION = 0;    //障碍物起始刷新位置

static const int groundHeight = 100;//地面高度
static const int TAG_HERO = 99;

static const int SPEED = 300;
static const int HERO_BUFF_NORMAL = 10;
static const int HERO_BUFF_INVINCIBLE = 20;
static const int HERO_BUFF_SPEEDUP = 30;

static const int HERO_STATUS_NOMAL = 100;
static const int HERO_STATUS_JUMP = 200;
static const int HERO_STATUS_INJURED = 300;
static const int HERO_STATUS_FALLEN = 400;

static const int GAME_STATUS_BOSS = 996;
static const int GAME_STATUS_WIN = 997;
static const int GAME_STATUS_PLAYING = 998;
static const int GAME_STATUS_GAMEOVER = 999;

//ground刷新相关
static const int TAG_GROUND = 599;
static const int GROUND_MIN_INTERVAL = 1900;           //最大最小间隔
static const int GROUND_MAX_INTERVAL = 2600;
static const int GROUND_MIN_LENGTH = 2500;			//最大最小长度
static const int GROUND_MAX_LENGTH = 4000;
static const string PIC_GROUND ="Obst\\ground1.png";

//Map 刷新
static const int TAG_MAP = 111;
static const string PIC_AMAP = "bga.png";
static const string PIC_BMAP ="bgb.png";

static const int TAG_BULLET = 3;
static const int TAG_ENEMY = 4;
static const int TAG_COIN = 5;
static const int TAG_BOSS = 6;

static const int GRAVITY = -200;

static const int JumpHeight = 180;

static const int TAG_HERO_HPBAR = 123;
static const int TAG_BOSS_HPBAR = 124;
static const int TAG_INFORMATION = 234;
static const int TAG_STAGESCENE = 235;
static const int TAG_GAMEOVER = 345;
static const int TAG_STAGECLEAR = 346;

//mask
static const int NO_COLLISION_MASK = 0x00000000;

static const int TAG_RUN_ACTION = 66;

//Enemy 刷新相关
static const string PIC_ENE = "HelloWorld.png";
static const Rect PIC_ENER = Rect(0,0,50,50);
static const float CON1_XBEI = 0.1;
static const float CON1_YBEI = 0.1;
static const float CON2_XBEI = 0.9;
static const float CON2_YBEI = 0.1;

//dropItem刷新相关
static const int TAG_DROP = 660;
static const int TAG_DROP_INVINCIBLE = 666;
static const int TAG_DROP_ENENMY = 667;
static const int TAG_DROP_HEAL = 668;
static const int TAG_DROP_POISON = 669;
static const int TAG_DROP_BLIND = 670;
static const float DROP_RATE = 0.8f;

#endif 