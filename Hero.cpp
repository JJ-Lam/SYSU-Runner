#include "Hero.h"
#include "StageScene.h"
#include "Bullet.h"
#include "Resource.h"

USING_NS_CC;

Hero::Hero()
{
	//��ʼ������
	hp = 100;
	status = HERO_STATUS_NOMAL;
	buff = HERO_BUFF_NORMAL;
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("Hero//hero.plist");
	myHero = Sprite::createWithSpriteFrameName("run0.png");

	this->initSpriteFrames();

	auto body = PhysicsBody::createCircle(myHero->getContentSize().width/2);
	body->getShape(0)->setFriction(0);
	body->setContactTestBitmask(0xFFFFFFFF);
	body->getShape(0)->setRestitution(0);
	myHero->setPhysicsBody(body);

	this->runAction("run");
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

void Hero::heal(int heal)
{
	hp += heal;
	if(hp > 100)
		hp = 100;
	HpBar* bar = (HpBar*)this->getParent()->getParent()->getParent()->getChildByTag(TAG_INFORMATION)->getChildByTag(TAG_HERO_HPBAR);
	bar->changeHp(heal);
}

void Hero::jump()
{
	if(status != HERO_STATUS_JUMP)
	{
		myHero->runAction(MoveBy::create(0.5,Vec2(0,JumpHeight)));
		//auto impulse = myHero->getPhysicsBody()->getMass() * 220;
		//myHero->getPhysicsBody()->applyImpulse(Vec2(0,impulse));
		status = HERO_STATUS_JUMP;
		this->runAction("jump");
	}
}

void Hero::attack()
{
	//��ȡ��
	StageScene* layer = (StageScene*)this->getParent();
	//����Bullet���Launch��������addchild������
	layer->addChild(layer->getBulletClass()->Launch(this->myHero),1,TAG_BULLET);
	this->runAction("shoot");
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
	auto jumpAnimation = Animation::createWithSpriteFrames(frames,2.0f/4.0f);
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

void Hero::setBuff(int buff)
{
	this->buff = buff;
	if(buff == HERO_BUFF_INVINCIBLE)
	{
		bubble = Sprite::create("bubble.png");
		bubble->setPosition(myHero->getPosition());
		this->getParent()->addChild(bubble);
	}
	else
	{
		float bufftime = 3.0;
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