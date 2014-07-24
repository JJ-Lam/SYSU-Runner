#ifndef _ENEMY_
#define _ENEMY_
#include "cocos2d.h"
#include "MyMap.h"
#include "Bullet.h"
#include "Obstacle.h"
USING_NS_CC;
class Enemy: public cocos2d::Node{
public:
	Obstacle* ob;
	int timeCount;
	MyMap* m;
	Bullet* b;
	Sprite* myEnemy;
	Layer* layer;
	Enemy();
	
	Vector<Sprite*> enemyAlllist;
	//Vector<Sprite*> enemyActivelist;
	static Enemy* create(Layer* layer,Obstacle* o,Bullet* bu);
	void Manager(float x,float y);

	bool isaddEnemy(float x);
	void addEnemy(float x,float y);
	void removeEnemy(float x);
	Action* randomEnemy();
	void enemyAttack(float x, float y);

};






#endif