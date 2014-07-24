#include "StageScene.h"
#include "InformationLayer.h"
#include "Resource.h"

Scene* StageScene::createScene()
{
	srand(unsigned(time(0)));

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bigScene = Scene::create();

	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0,GRAVITY));

    auto layer = StageScene::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	auto informationLayer = InformationLayer::create();

	layer->camera = new ActionCamera();
	layer->camera->startWithTarget(scene);

    scene->addChild(layer,0,TAG_STAGESCENE);
	bigScene->addChild(scene,0,1);
	bigScene->addChild(informationLayer,2,TAG_INFORMATION);
	bigScene->retain();

    return bigScene;
}

bool StageScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//初始化各种变量
	gameStatus = GAME_STATUS_PLAYING;

	b = new Bullet();
	this->addChild(b);

	c = new Coin();
	this->addChild(c);

	o = Obstacle::create(this);
	this->addChild(o);

	ene = Enemy::create(this,o,b);

	m = MyMap::create(this);
	this->addChild(m);

	d = dropItem::create(this);
	this->addChild(d);

	//加载手势识别模板
	g_r = new GeometricRecognizer;
	g_r->loadTemplates();

	//初始化Hero对象
	hero = new Hero();
	hero->myHero->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	hero->myHero->getPhysicsBody()->setVelocity(Vec2(100,0));
	this->addChild(hero);
	this->addChild(hero->myHero,1,TAG_HERO);
	startPosition = hero->myHero->getPositionX();
	totalDistance = 1000;

	//触摸事件监听
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(StageScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(StageScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(StageScene::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//碰撞回调函数
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [=](const PhysicsContact& contact)
	{
		auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
		if(spriteA == NULL || spriteB == NULL)
			return false;

		//主角与地面碰撞，将主角状态从JUMP恢复为NOMAL
		if((spriteA->getTag() == TAG_HERO && spriteB->getTag() == TAG_GROUND) || (spriteB->getTag() == TAG_HERO && spriteA->getTag() == TAG_GROUND))
		{
			auto body = hero->myHero->getPhysicsBody();
			body->setVelocity(Vec2(body->getVelocity().x,0));
			hero->status = HERO_STATUS_NOMAL;
			hero->runAction("run");
		}

		//子弹与其他物体碰撞，消除子弹
		if(spriteA->getTag() == TAG_BULLET || spriteB->getTag() == TAG_BULLET)
		{
			if(spriteA->getTag() != TAG_BULLET)
				std::swap(spriteA,spriteB);
			b->removeOneBullet(spriteA);
			if(spriteB->getTag() == TAG_BOSS)
				stageBoss->injured(20);
			else if(spriteB->getTag() == TAG_HERO)
				hero->injured(10);
		}

		//主角与金币碰撞，增加积分
		else if(spriteA->getTag() == TAG_HERO && spriteB->getTag() == TAG_COIN || spriteB->getTag() == TAG_HERO && spriteA->getTag() == TAG_COIN)
		{
			if(spriteA->getTag() == TAG_COIN)
				c->removeOneCoin(spriteA);
			else
				c->removeOneCoin(spriteB);
			auto info = (InformationLayer*)Director::getInstance()->getRunningScene()->getChildByTag(TAG_INFORMATION);
			info->changeScore(10);
		}

		//主角与道具碰撞
		else if(spriteA->getTag() == TAG_HERO && spriteB->getTag() > TAG_DROP || spriteB->getTag() == TAG_HERO && spriteA->getTag() > TAG_DROP)
		{
			if(spriteA->getTag() != TAG_HERO)
				std::swap(spriteA,spriteB);
			d->curdropItemlist.eraseObject(spriteB);
			switch(spriteB->getTag())
			{
			case TAG_DROP_HEAL:
				hero->heal(30);
				break;
			case TAG_DROP_BLIND:
				blind();
				break;
			case TAG_DROP_ENENMY:
				break;
			case TAG_DROP_INVINCIBLE:
				hero->setBuff(HERO_BUFF_INVINCIBLE);
				break;
			case TAG_DROP_POISON:
				hero->injured(10);
				break;
			default:
				break;
			}
			this->removeChild(spriteB);
		}

		return true;
	};
	dispatcher->addEventListenerWithFixedPriority(contactListener,10);
    
	scheduleUpdate();

	this->retain();

    return true;
}

void StageScene::update(float time){
	if(gameStatus == GAME_STATUS_PLAYING || gameStatus == GAME_STATUS_BOSS)
	{
		//设置相机跟随主角移动
		auto LastEyeX = hero->myHero->getPositionX() - hero->myHero->getContentSize().width;
		auto EyeZ = camera->getEye().z;
		camera->setEye(LastEyeX,0,EyeZ);
		camera->setCenter(Vec3(LastEyeX ,0,0));
		//保持主角的前进速度
		hero->myHero->getPhysicsBody()->setVelocity(Vec2(SPEED,hero->myHero->getPhysicsBody()->getVelocity().y));
		//清除所有飞出屏幕范围外的子弹和金币
		b->removeUselessBullets();
		c->removeUselessCoins();
		//生成各种障碍物
		o->Manager(hero->myHero->getPositionX(),hero->myHero->getPositionY());
		//ene->Manager(hero->myHero->getPositionX(),hero->myHero->getPositionY());
		//滚动背景图
		m->mapReload(hero->myHero->getPositionX());
		//随机生成金币
		if(CCRANDOM_0_1() > 0.99)
		{
			auto newCoin = c->placeCoin();
			if(newCoin != NULL)
				this->addChild(newCoin,1,TAG_COIN);
		}
		//道具掉落
		d->Manager(hero->myHero->getPositionX(),hero->myHero->getPositionY());
		//检测主角是否掉落
		if(hero->fallen())
			hero->bringBackToGround();
		//bubble update
		if(hero->buff == HERO_BUFF_INVINCIBLE)
			hero->bubbleUpdate();
		//更新跑酷距离
		if(gameStatus == GAME_STATUS_PLAYING)
		{
			currentPosition = hero->myHero->getPositionX() - startPosition;
			if(currentPosition >= totalDistance)
			{
				gameStatus = GAME_STATUS_BOSS;
				//初始化boss对象
				stageBoss = new Boss(this,b);
				this->addChild(stageBoss->boss,2,TAG_BOSS);
				this->getParent()->getParent()->getChildByTag(TAG_INFORMATION)->getChildByTag(TAG_BOSS_HPBAR)->setVisible(true);
			}
		}
		else
		{
			//boss
			stageBoss->updatePosition();
			stageBoss->attack();
		}
	}
	else if(gameStatus == GAME_STATUS_GAMEOVER)
	{
		auto l = LayerColor::create(Color4B(0,0,0,200));
		this->getParent()->getParent()->addChild(l,1);
		hero->myHero->getPhysicsBody()->setVelocity(Vec2(0,0));
		auto info = (InformationLayer*)this->getParent()->getParent()->getChildByTag(TAG_INFORMATION);
		info->getChildByTag(TAG_GAMEOVER)->setVisible(true);
		info->endmenu->setVisible(true);
		info->pausemenu->setVisible(false);
		this->unscheduleUpdate();

		auto i = (InformationLayer*)this->getParent()->getParent()->getChildByTag(TAG_INFORMATION);
		UserData::getInstance()->gainPoints(i->getScore());
	}
	else
	{
		auto l = LayerColor::create(Color4B(255,255,255,200));
		this->getParent()->getParent()->addChild(l,1);
		hero->myHero->getPhysicsBody()->setVelocity(Vec2(0,0));
		auto info = (InformationLayer*)this->getParent()->getParent()->getChildByTag(TAG_INFORMATION);
		info->getChildByTag(TAG_STAGECLEAR)->setVisible(true);
		info->endmenu->setVisible(true);
		info->pausemenu->setVisible(false);
		this->unscheduleUpdate();

		auto i = (InformationLayer*)this->getParent()->getParent()->getChildByTag(TAG_INFORMATION);
		UserData::getInstance()->gainPoints(i->getScore());
	}
}

bool StageScene::onTouchBegan(Touch *touch, Event* event)
{
	if((gameStatus == GAME_STATUS_PLAYING || gameStatus == GAME_STATUS_BOSS) && hero->status != HERO_STATUS_FALLEN && !Director::getInstance()->isPaused())
		return true;
	else
		return false;
}

void StageScene::onTouchMoved(Touch *touch, Event* event)
{
	Point location = touch->getLocationInView();

	Point2D temp;
	temp.x = location.x;
	temp.y = location.y;

	p2d.push_back(temp);
}

void StageScene::onTouchEnded(Touch *touch, Event* event)
{
	//单击屏幕——攻击
	if(p2d.size() < 1)
		hero->attack();
	//向上划——跳
	else
	{
		RecognitionResult r = g_r->recognize(p2d);
		if(r.name == "Up")
			hero->jump();
		p2d.clear();
	}
}

Bullet* StageScene::getBulletClass(){
	return b;
}

Hero* StageScene::getHero(){
	return hero;
}

void StageScene::blind()
{
	auto l = LayerColor::create(Color4B(255,255,255,255));
	this->getParent()->getParent()->addChild(l,1,233);
	scheduleOnce(schedule_selector(StageScene::blindRecover),3.0f);
}

void StageScene::blindRecover(float time)
{
	this->getParent()->getParent()->removeChildByTag(233);
}