#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "resource.h"

USING_NS_CC;

class Bullet : public cocos2d::Node
{
public:
	Bullet();
	Sprite* Launch(Sprite* from, int direction = 1);	//1为向右，-1为向左
	void removeUselessBullets();
	void removeOneBullet(Sprite* bullet);
	Sprite* Launch(Sprite* from ,Vec2 v2);

private:
	
	Vector<Sprite*>* bulletsVector;
};
#endif