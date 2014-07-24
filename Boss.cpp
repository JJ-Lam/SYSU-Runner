#include "Boss.h"
#include "StageScene.h"

USING_NS_CC;

Boss::Boss(Layer* l, Bullet* b)
{
	hp = 300;
	status = HERO_STATUS_NOMAL;
	moveCount = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->layer = l;
	this->bullet = b;

	boss = Sprite::create("boss.png");
	boss->setPosition(Vec2(layer->getChildByTag(TAG_HERO)->getPositionX() + visibleSize.width - boss->getContentSize().width*2, visibleSize.height/2));

	auto body = PhysicsBody::createBox(boss->getContentSize());
	body->setDynamic(false);
	body->setContactTestBitmask(0xFFFFFFFF);
	boss->setPhysicsBody(body);
}

void Boss::updatePosition()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	boss->setPositionX(layer->getChildByTag(TAG_HERO)->getPositionX() + visibleSize.width - boss->getContentSize().width*2);
	if(moveCount >= 120)
	{
		auto randomPos = CCRANDOM_0_1() * JumpHeight + layer->getChildByTag(TAG_HERO)->getPositionY();
		boss->runAction(MoveTo::create(1,Vec2(boss->getPositionX(),randomPos)));
		moveCount = 0;
	}
	moveCount++;
}

void Boss::injured(int damage)
{
	if(status != HERO_STATUS_INJURED)
	{
		hp -= damage;

		HpBar* bar = (HpBar*)layer->getParent()->getParent()->getChildByTag(TAG_INFORMATION)->getChildByTag(TAG_BOSS_HPBAR);
		bar->changeHp(-damage);
		if(hp <= 0)
		{
			auto temp = (StageScene*)layer;
			temp->gameStatus = GAME_STATUS_WIN;
		}
		else
		{
			status = HERO_STATUS_INJURED;
			auto seq = Sequence::create(Blink::create(1,4),CallFunc::create(CC_CALLBACK_0(Boss::injuredCallBack,this)),NULL);
			boss->runAction(seq);
		}
	}
}

void Boss::attack()
{
	if(CCRANDOM_0_1() > 0.97)
		layer->addChild(bullet->Launch(boss,-1),1,TAG_BULLET);
}

void Boss::injuredCallBack()
{
	if(status == HERO_STATUS_INJURED)
		status = HERO_STATUS_NOMAL;
	boss->setVisible(true);
}