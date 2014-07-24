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

	void blind();
	void blindRecover(float time);

	virtual void update(float time);

	Bullet* getBulletClass();

	Hero* getHero();

	int gameStatus;

	float startPosition, currentPosition, totalDistance;

private:
	Enemy *ene;
	Hero *hero;
	Bullet *b;
	Coin *c;
	Obstacle *o;
	MyMap *m;
	Boss* stageBoss;
	dropItem* d;

	ActionCamera* camera;
	PhysicsWorld* m_world;
	GeometricRecognizer *g_r;
	Path2D p2d;
};

#endif // __GAMEMENU_H__