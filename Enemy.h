#ifndef _ENEMY_
#define _ENEMY_
#include "cocos2d.h"
#include "MyMap.h"
#include "Bullet.h"

USING_NS_CC;
enum ENEMYSTATE{
	ENEMY_ATTACK = 1,
	ENEMY_RUN = 2,
	ENEMY_DEAD = 3,
	ENE_BLOCK = 1000
};
class Enemy: public cocos2d::Node{
public:
	int timeCount;
	MyMap* m;
	Bullet* b;
	Sprite* myEnemy;
	Layer* layer;
	
	
	Vector<Sprite*> enemyAlllist;
	//Vector<Sprite*> enemyActivelist;

	void Manager(float x,float y);

	bool isaddEnemy();
	void removeEnemy(float x);
	Action* randomEnemy();
	void enemyAttack();

	Enemy(Vec2 s,float x,Layer* l);
	int getState();
	void setState(int s);
	void doAction();
	void addEnemy();
	Sprite* ene;
	void eneAI(Vec2 h);
	
private:
	int attackCount;
	Vec2 startpos;
	float activeLength;
	int state;
	void deadCallBack();
	void attactCallBack();
	void runCallback();
};






#endif