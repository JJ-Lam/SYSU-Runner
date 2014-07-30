#ifndef __HPBAR_H__
#define __HPBAR_H__

#include "cocos2d.h"

USING_NS_CC;

enum bar_type{
	hpbar,
	mpbar
};

class HpBar : public Node
{
public:
	HpBar(int max, bar_type type);
	void changeHp(int change);
	void setHpbar(Vec2 pos, float scalex, float scaley);
	Sprite* background;
	Sprite* hp;
	ProgressTimer* progressTimer;

private:
	float maxHp;
	float currentHp;
};

#endif