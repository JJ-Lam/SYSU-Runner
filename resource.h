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
static const int BAND_WITDH = 185;
static const int BAND_H = 50;
static const int BANDING_BLOCK = 400;

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

//hero
const static int SPEED = 300;
static const int HERO_BUFF_NORMAL = 10;
static const int HERO_BUFF_INVINCIBLE = 20;
static const int HERO_BUFF_SPEEDUP = 30;

static const int TAG_HERO_CLASS = 236;
static const int HERO_STATUS_NOMAL = 100;
static const int HERO_STATUS_JUMP = 200;
static const int HERO_STATUS_INJURED = 300;
static const int HERO_STATUS_FALLEN = 400;

static const int GAME_STATUS_PLAYING = 998;
static const int GAME_STATUS_GAMEOVER = 999;
static const int GAME_STATUS_BOSS = 996;
static const int GAME_STATUS_WIN = 997;

//ground刷新相关
static const int TAG_GROUND = 337;
static const int GROUND_MIN_INTERVAL = 1900;           //最大最小间隔
static const int GROUND_MAX_INTERVAL = 2600;
static const int GROUND_MIN_LENGTH = 2500;			//最大最小长度
static const int GROUND_MAX_LENGTH = 4000;
static const float GROUND_HHH = 75;
//Map 刷新
static const int TAG_MAP = 111;

//bullet
static const int TAG_BULLET = 3;
static const int TAG_ENEMY = 4;
static const int TAG_BULLET_CLASS = 259;
static const int TAG_LASER = 7;
static const int TAG_DESTROY = 8;
static const int TAG_DAMAGE = 9;
//coin
static const int TAG_COIN = 5;
static const float COIN_WIDTH = 10;
static const float COIN_BASEHHIGHT = 100;
static const float COIN_INTER = 10;
static const int TAG_COIN_CLASSS = 567;
static const int LINE_STRAGIHT =1; 
static const float ARROW_HEIGHT = 80;
static const float COIN_BLOCK_SIZE = 800;

static const int COIN_SQUARE = 1;
static const int COIN_LINE = 2;
static const int LINE_COUNT = 10;
static const int COIN_ARROW = 3;
static const int COIN_TYPE = 3;

//GRAVITY
static const int GRAVITY = -300;

static const int JumpHeight = 250;

static const int TAG_INFORMATION = 234;
static const int TAG_GAMEOVER = 345;
static const int TAG_STAGESCENE = 235;

//mask
static const int COIN_COLLISION_MASK = 0x00000000;

static const int TAG_RUN_ACTION = 66;

//Enemy 刷新相关
static const Rect PIC_ENER = Rect(0,0,50,50);
static const float CON1_XBEI = 0.1;
static const float CON1_YBEI = 0.1;
static const float CON2_XBEI = 0.9;
static const float CON2_YBEI = 0.1;
static const float ENE_GROUND_ACT = 200;
static const float ENE_ATTACK_DIST = 600;

//dropItem刷新相关
static const int TAG_DROP = 660;
static const int TAG_DROP_INVINCIBLE = 666;
static const int TAG_DROP_SPEEDUP = 667;
static const int TAG_DROP_HEAL = 668;
static const int TAG_DROP_POISON = 669;
static const int TAG_DROP_BLIND = 670;
static const float DROP_RATE = 0.8f;

//paraNode
static const int MID_SCENE = 1;
static const int FAR_SCENE = 2;
static const int FARFAR_SCENE = 3;

static const int TAG_PARA = 888;

static const float MID_RATE = 0.5;
static const float FAR_RATE = 0.2;

//nail
static const int TAG_NAIL = 333;
static const int NAIL_BLOCK = 1500;
static const int NAIL_DAMAGE = 20;

static const int NO_COLLISION_MASK = 0x00000000;

//血量
static const int TAG_HERO_HPBAR = 123;
static const int TAG_BOSS_HPBAR = 124;
static const int TAG_HERO_MPBAR = 125;
static const int TAG_BOSS = 6;
static const int TAG_STAGECLEAR = 346;

//音效与图片
static const char* JUMP_WAV = "bgm/hero/jump.wav";
static const char* GETCOIN_WAV = "bgm/hero/getcoin.wav";
static const char* BULLET_WAV = "bgm/hero/shoot.wav";
static const char* GAMEMENU_WAV = "bgm/game/gamemenu.wav";
static const char* GAMESCENE_WAV = "bgm/game/gamescene.wav";

static const string WEAPON_BUTTONS[4] = {"weapon/bulletButton.png","weapon/damageButton.png","weapon/destroyButton.png","weapon/laserButton.png"};
static const string PIC_BANDING = "Obst/banding.png";
static const string PIC_NAIL = "Obst/nail.png";
static const string PIC_MID = "background/1.png";
static const string PIC_FAR = "background/2.png";
static const string PIC_FARFAR = "background/3.png";
static const string BG_PIC[3] = {PIC_MID,PIC_FAR,PIC_FARFAR};
static const string PIC_ENE = "HelloWorld.png";
static const string PIC_COIN = "coin.png";
static const string PIC_AMAP = "bga.png";
static const string PIC_BMAP = "bgb.png";
static const string PIC_GROUND ="Obst/ground.png";
static const string PIC_NORMALBULLET = "weapon/bullet.png";
static const string PIC_LASER = "weapon/laser.png";
static const string PIC_DAMAGEBULLET = "weapon/damageBullet.png";
static const string PIC_DESTROYBULLET = "weapon/destroyBullet.png";
static const string PIC_HP = "hp.jpg";
static const string PIC_MP = "mp.jpg";
static const string PIC_BARBACKGROUND = "barBackground.png";
static const string PIC_START = "start.png";
static const string PIC_SHOP = "shop.png";
static const string PIC_SETTING = "setting.png";
static const string PIC_QUIT = "quit.png";
static const string PIC_MENUBACKGROUND = "menubackground.png";
static const string PIC_PAUSE = "buttons/pause.png";
static const string PIC_RESUME = "buttons/resume.png";
static const string PIC_HOME = "buttons/home.png";
static const string PIC_REPLAY = "buttons/replay.png";
static const string PIC_BOSS = "boss.png";

static const string PLIST_DROPITEM = "dropItem/drop.plist";
static const string PLIST_ENEMY = "Enemy/ene.plist";
static const string PLIST_HERO = "Hero/hero.plist";

#endif