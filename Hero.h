#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class Hero : public cocos2d::Node
{
public:
	Hero();
	void injured(int damage);
	void heal(int heal);
	
	void jump();
	void attack();
	bool fallen();
	void bringBackToGround();
	void fallenCallBack();
	void injuredCallBack();
	void runAction(const char *action);
	void setBuff(int buff);
	void removeBuff(float time);
	void bubbleUpdate();

	Sprite* myHero;
	Sprite* bubble;
	int hp;
	int status;
	int buff;
private:
	void initSpriteFrames();
};
#endif