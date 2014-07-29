#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__

#include "cocos2d.h"
#include "GeometricRecognizer\GeometricRecognizer.h"
#include "Hero.h"
#include "Bullet.h"
#include "HpBar.h"
#include "Coin.h"
#include "MyMap.h"
#include "Obstacle.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"
#include "Nail.h"
#include "EneController.h"
#include "Boss.h"
#include "dropItem.h"
#include "UserData.h"
using namespace DollarRecognizer;
USING_NS_CC;

class StageScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

	virtual bool init();
    
	CREATE_FUNC(StageScene);

	virtual bool onTouchBegan(Touch *touch, Event* event);

	virtual void onTouchMoved(Touch *touch, Event* event);

	virtual void onTouchEnded(Touch *touch, Event* event);

	void setPhyWorld(PhysicsWorld* world){m_world = world;}

	virtual void update(float time);

	Bullet* getBulletClass();

	Hero* getHero();

	int gameStatus;

	void UpdateandAddEnemy();
	void UpdateCoin();
	void UpdateNail();
	
	void blind();
	void blindRecover(float time);

	float startPosition, currentPosition, totalDistance;

private:
	Hero *hero;
	Bullet *b;
	Coin *c;
	Obstacle *o;
	MyMap* m1;
	MyMap* m2;
	MyMap* m3;
	Nail* na;

	dropItem* d;
	Boss* stageBoss;
	EneController* enec;
	Vector<Enemy*> eneList;
	ActionCamera* camera;
	PhysicsWorld* m_world;
	GeometricRecognizer *g_r;
	Path2D p2d;
};

#endif // __GAMEMENU_H__