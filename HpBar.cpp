#include "HpBar.h"

USING_NS_CC;

HpBar::HpBar(int max)
{
	maxHp = max;
	currentHp = max;

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	hp = Sprite::create("hp.jpg");
	background = Sprite::create("hpbar.png");

	progressTimer = ProgressTimer::create(hp);
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer->setMidpoint(Vec2(0,1));
	progressTimer->setBarChangeRate(Vec2(1,0));
	progressTimer->setPercentage(100);

	this->addChild(progressTimer);
	this->addChild(background);
	progressTimer->retain();
}

void HpBar::changeHp(int change)
{
	currentHp += change;
	if(currentHp < 0)
		currentHp = 0;
	else if(currentHp > maxHp)
		currentHp = maxHp;
	auto progress = ProgressFromTo::create(0.5,progressTimer->getPercentage(),currentHp/maxHp*100);
	progressTimer->runAction(progress);
}

void HpBar::setHpbar(Vec2 pos, float scalex, float scaley)
{
	progressTimer->setPosition(pos);
	background->setPosition(pos);
	progressTimer->setScaleX(scalex);
	progressTimer->setScaleY(scaley);
}