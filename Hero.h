#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Bullet.h"
#include "Obstacle.h"
USING_NS_CC;

class Hero : public cocos2d::Node
{
public:
	Hero();
	void injured(int damage);
	
	void jump();
	void attack();
	bool fallen();
	void bringBackToGround();
	void fallenCallBack();
	void injuredCallBack();
	void runCallBack();
	void runAction(const char *action);

	Sprite* myHero;
	Sprite* bubble;
	SpriteBatchNode* _heros;

	int hp;
	int status;
	int buff;

	void heal(int h);
	void setBuff(int buff);
	void removeBuff(float time);
	void bubbleUpdate();

private:
	void initSpriteFrames();
};
#endif