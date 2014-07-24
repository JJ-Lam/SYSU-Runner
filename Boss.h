#ifndef __BOSS_H__
#define __BOSS_H__

#include "cocos2d.h"
#include "Bullet.h"
#include "resource.h"
#include "Hero.h"
#include "Bullet.h"
#include "HpBar.h"

USING_NS_CC;

class Boss : public cocos2d::Node
{
public:
	Boss(Layer* l, Bullet* b);

	void updatePosition();

	void injured(int damage);
	void attack();
	void injuredCallBack();

	Sprite* boss;
	int hp;
	int status;
private:
	Layer* layer;
	Bullet* bullet;
	int moveCount;
};

#endif