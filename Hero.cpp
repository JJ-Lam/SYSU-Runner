#include "Hero.h"
#include "StageScene.h"
#include "Bullet.h"
#include "Resource.h"

USING_NS_CC;

Hero::Hero(Weapon w)
{
	//初始化变量
	weapon = w;
	hp = 100;
	mp = 100;
	status = HERO_STATUS_NOMAL;
	buff = HERO_BUFF_NORMAL;
	mpRechargeEnableTime = 0;

	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(PLIST_HERO);
	//_heros = SpriteBatchNode::create(PLIST_HERO);
	myHero = Sprite::createWithSpriteFrameName("run0.png");
	//weapon = damageBullet;

	this->initSpriteFrames();

	auto body = PhysicsBody::createCircle(myHero->getContentSize().width/2);
	body->getShape(0)->setFriction(0);
	body->setContactTestBitmask(0xFFFFFFFF);
	body->getShape(0)->setRestitution(0);
	myHero->setPhysicsBody(body);

	this->runAction("run");
	scheduleUpdate();
}

void Hero::injured(int damage)
{
	if(status != HERO_STATUS_INJURED)
	{
		if(buff == HERO_BUFF_INVINCIBLE)
		{
			buff = HERO_BUFF_NORMAL;
			this->getParent()->removeChild(bubble);
		}
		else
		{
			hp -= damage;
			HpBar* bar = (HpBar*)this->getParent()->getParent()->getParent()->getChildByTag(TAG_INFORMATION)->getChildByTag(TAG_HERO_HPBAR);
			bar->changeHp(-damage);
			this->runAction("injured");
			if(hp <= 0)
			{
				auto l = (StageScene*)this->getParent();
				l->gameStatus = GAME_STATUS_GAMEOVER;
			}
			else
			{
				status = HERO_STATUS_INJURED;
				auto seq = Sequence::create(Blink::create(1,4),CallFunc::create(CC_CALLBACK_0(Hero::injuredCallBack,this)),NULL);
				myHero->runAction(seq);
			}
		}
	}
}

void Hero::jump()
{
	if(status != HERO_STATUS_JUMP)
	{
		//myHero->runAction(MoveBy::create(0.5,Vec2(0,JumpHeight)));
		auto upaction = MoveBy::create(0.5,Vec2(0,JumpHeight));
		auto seq = Sequence::create(upaction,CallFunc::create(CC_CALLBACK_0(Hero::runCallBack,this)),NULL);
		myHero->runAction(seq);
		//auto impulse = myHero->getPhysicsBody()->getMass() * 220;
		//myHero->getPhysicsBody()->applyImpulse(Vec2(0,impulse));
		status = HERO_STATUS_JUMP;
		this->runAction("jump");
	}
}

void Hero::attack()
{
	switch (weapon)
	{
	case normalBullet:
		if(!mpChange(-10))
			return;
		break;
	case damageBullet:
		if(!mpChange(-15))
			return;
		break;
	case destroyBullet:
		if(!mpChange(-20))
			return;
		break;
	case laser:
		if(!mpChange(-25))
			return;
		break;
	default:
		break;
	}
	mpRechargeEnableTime = -60;
	myHero->stopActionByTag(TAG_RUN_ACTION);
	//获取层
	StageScene* layer = (StageScene*)this->getParent();
	//调用Bullet类的Launch方法，并addchild到层中
	layer->addChild(layer->getBulletClass()->SpecialLaunch(this->myHero,weapon),1,TAG_BULLET);
	auto animation1 = AnimationCache::sharedAnimationCache()->animationByName("shoot");
	auto animate1 = Animate::create(animation1);
	auto animation2 = AnimationCache::sharedAnimationCache()->animationByName("run");
	auto animate2 = Animate::create(animation2);
	auto seq = Sequence::createWithTwoActions(animate1,animate2);
	seq->setTag(TAG_RUN_ACTION);
	myHero->runAction(seq);
}

bool Hero::fallen()
{
	if(myHero->getPositionY() < groundHeight && this->status != HERO_STATUS_FALLEN)
	{
		this->status = HERO_STATUS_FALLEN;
		return true;
	}
	else
		return false;
}

void Hero::bringBackToGround()
{
	myHero->getPhysicsBody()->setDynamic(false);
	auto seq = Sequence::create(MoveTo::create(2,myHero->getPosition()),MoveTo::create(0,Vec2(myHero->getPositionX(),groundHeight*20)),CallFunc::create(CC_CALLBACK_0(Hero::fallenCallBack,this)),NULL);
	myHero->runAction(seq);
}

void Hero::fallenCallBack()
{
	myHero->getPhysicsBody()->setDynamic(true);
	this->status = HERO_BUFF_NORMAL;
	injured(20);
	auto oo = (Obstacle*)this->getParent()->getChildByTag(TAG_OBSTALCE);
	auto fb = (Sprite*)oo->curBandlist.begin()[0];
	myHero->setPosition(fb->getPositionX() - fb->getContentSize().width/2,fb->getPositionY()+fb->getContentSize().height);
}

void Hero::heal(int heal)
{
	hp += heal;
	if(hp > 100)
		hp = 100;
	HpBar* bar = (HpBar*)this->getParent()->getParent()->getParent()->getChildByTag(TAG_INFORMATION)->getChildByTag(TAG_HERO_HPBAR);
	bar->changeHp(heal);
}

void Hero::injuredCallBack()
{
	if(status == HERO_STATUS_INJURED)
		status = HERO_STATUS_NOMAL;
	myHero->setVisible(true);
	this->runAction("run");
}

void Hero::runAction(const char *action)
{
	myHero->stopActionByTag(TAG_RUN_ACTION);

	auto animation = AnimationCache::sharedAnimationCache()->animationByName(action);
	auto animate = Animate::create(animation);
	if(action == "run")
		animate->setTag(TAG_RUN_ACTION);
	myHero->runAction(animate);
}

void Hero::initSpriteFrames()
{
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	Vector<SpriteFrame*> frames(5);
	char str[20] = {0};

	//run
	for(int i = 1; i < 5; i++)
	{
		sprintf(str,"run%1d.png",i);
		auto frame = cache->getSpriteFrameByName(str);
		frames.pushBack(frame);
	}
	auto runAnimation = Animation::createWithSpriteFrames(frames,0.6f/4.0f);
	runAnimation->setLoops(-1);
	AnimationCache::sharedAnimationCache()->addAnimation(runAnimation,"run");
	frames.clear();

	//jump
	for(int i = 0; i < 4; i++)
	{
		sprintf(str,"jump%1d.png",i);
		auto frame = cache->getSpriteFrameByName(str);
		frames.pushBack(frame);
	}
	auto jumpAnimation = Animation::createWithSpriteFrames(frames,1.2f/4.0f);
	AnimationCache::sharedAnimationCache()->addAnimation(jumpAnimation,"jump");
	frames.clear();

	//shoot
	for(int i = 0; i < 2; i++)
	{
		sprintf(str,"shoot%1d.png",i);
		auto frame = cache->getSpriteFrameByName(str);
		frames.pushBack(frame);
	}
	auto shootAnimation = Animation::createWithSpriteFrames(frames,0.5f/2.0f);
	AnimationCache::sharedAnimationCache()->addAnimation(shootAnimation,"shoot");
	frames.clear();

	//injured
	SpriteFrame* frame = cache->getSpriteFrameByName("injured.png");
	frames.pushBack(frame);
	auto injuredAnimation = Animation::createWithSpriteFrames(frames,1.0f);
	AnimationCache::sharedAnimationCache()->addAnimation(injuredAnimation,"injured");
}

void Hero::runCallBack(){
	auto v = myHero->getPhysicsBody()->getVelocity();
	myHero->getPhysicsBody()->setVelocity(Vec2(v.x,-300));
}

void Hero::setBuff(int buff)
{
	if(this->buff == buff)
		return;
	this->buff = buff;
	if(buff == HERO_BUFF_INVINCIBLE)
	{
		bubble = Sprite::create("bubble.png");
		bubble->setPosition(myHero->getPosition());
		this->getParent()->addChild(bubble);
	}
	else
	{
		float bufftime = 5.0;
		scheduleOnce(schedule_selector(Hero::removeBuff),bufftime);
	}
}

void Hero::removeBuff(float time)
{
	buff = HERO_BUFF_NORMAL;
}

void Hero::bubbleUpdate()
{
	bubble->setPosition(myHero->getPosition());
}

bool Hero::mpChange(int change)
{
	HpBar* mpbar = (HpBar*)this->getParent()->getParent()->getParent()->getChildByTag(TAG_INFORMATION)->getChildByTag(TAG_HERO_MPBAR);
	if(mp + change < 0)
	{
		mpbar->progressTimer->runAction(Sequence::createWithTwoActions(Blink::create(0.4,3),CallFunc::create(CC_CALLBACK_0(Hero::mpBlinkCallBack,this))));
		return false;
	}
	mp += change;
	if(mp > 100)
		mp = 100;
	mpbar->changeHp(change);
	return true;
}

void Hero::update(float time)
{
	//保持主角的前进速度
	auto sp = buff == HERO_BUFF_SPEEDUP? SPEED*2 : SPEED;
	myHero->getPhysicsBody()->setVelocity(Vec2(sp,myHero->getPhysicsBody()->getVelocity().y));
	mpRechargeEnableTime++;
	if(mpRechargeEnableTime >= 30)
	{
		mpChange(15);
		mpRechargeEnableTime = 0;
	}
}

void Hero::mpBlinkCallBack()
{
	HpBar* mpbar = (HpBar*)this->getParent()->getParent()->getParent()->getChildByTag(TAG_INFORMATION)->getChildByTag(TAG_HERO_MPBAR);
	mpbar->progressTimer->setVisible(true);
}