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
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm\\game\\gamescene.wav",true);
	
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//初始化各种变量
	gameStatus = GAME_STATUS_PLAYING;

	b = new Bullet();
	this->addChild(b);
	b->setTag(TAG_BULLET_CLASS);
	b->retain();

	enec = new EneController();
	enec->initeneAction();
	enec->retain();


	//掉落道具
	d = dropItem::create(this);
	this->addChild(d);
	d->retain();

	c = new Coin(this);
	this->addChild(c);
	this->retain();
	c->setTag(TAG_COIN_CLASSS);
	c->retain();

	o = Obstacle::create(this);
	this->addChild(o);
	o->setTag(TAG_OBSTALCE);
	o->retain();

	//三层背景
	m1 = MyMap::create(this,MID_SCENE);
	m2 = MyMap::create(this,FAR_SCENE);
	m3 =MyMap::create(this,FARFAR_SCENE); 
	
	//钉子
	na = new Nail(this);
	
	//加载手势识别模板
	g_r = new GeometricRecognizer;
	g_r->loadTemplates();


	//初始化Hero对象
	hero = new Hero();
	hero->myHero->setPosition(Vec2(0, visibleSize.height/2 + origin.y));
	hero->myHero->getPhysicsBody()->setVelocity(Vec2(100,0));
	this->addChild(hero);
	hero->setTag(TAG_HERO_CLASS);
	this->addChild(hero->myHero,1,TAG_HERO);
	startPosition = hero->myHero->getPositionX();
	totalDistance = 10000;

	//触摸事件监听
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(StageScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(StageScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(StageScene::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//碰撞回调函数
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(StageScene::onContactBegin, this);
	dispatcher->addEventListenerWithFixedPriority(contactListener,10);
    
	scheduleUpdate();

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
		auto sp = hero->buff == HERO_BUFF_SPEEDUP? SPEED*2 : SPEED;
		hero->myHero->getPhysicsBody()->setVelocity(Vec2(sp,hero->myHero->getPhysicsBody()->getVelocity().y));
		//清除所有飞出屏幕范围外的子弹和金币
		b->removeUselessBullets();
		d->Manager(hero->myHero->getPositionX(),hero->myHero->getPositionY());

		//出现新地面时刷出金币和钉板

		UpdateCoin();
		UpdateNail();
		UpdateandAddEnemy();

		o->Manager(hero->myHero->getPositionX(),hero->myHero->getPositionY());
		//o->na->removeUselessNail();
		//三层背景
		m1->mapupdate(hero->myHero->getPositionX());
		m2->mapupdate(hero->myHero->getPositionX());
		m3->mapupdate(hero->myHero->getPositionX());
		//检测主角是否掉落
		if(hero->fallen())
			hero->bringBackToGround();
		if(hero->buff == HERO_BUFF_INVINCIBLE)
		{
			hero->bubbleUpdate();
		}
		if(gameStatus == GAME_STATUS_PLAYING)
		{
			currentPosition = hero->myHero->getPositionX() - startPosition;
			if(currentPosition >= totalDistance)
			{
				gameStatus = GAME_STATUS_BOSS;
				//初始化boss对象
				stageBoss = new Boss(this,b);
				stageBoss->retain();
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
	if(gameStatus != GAME_STATUS_GAMEOVER && hero->status != HERO_STATUS_FALLEN)
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
	if(p2d.size() < 1){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(BULLET_WAV);
		hero->attack();
	}
		//return;
	//向上划——跳
	else
	{
		RecognitionResult r = g_r->recognize(p2d);
		if(r.name == "Up"){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(JUMP_WAV);
			hero->jump();
		}
		p2d.clear();
	}
}

Bullet* StageScene::getBulletClass(){
	return b;
}

Hero* StageScene::getHero(){
	return hero;
}

void StageScene::UpdateandAddEnemy(){
	//update
	for(int i = 0;i<eneList.size();i++){
		auto se = (Enemy*)eneList.at(i);
		auto wp = se->convertToWorldSpace(se->ene->getPosition());
		if(wp.x < 0)
		{
			eneList.eraseObject(se);
			se->ene->removeFromParentAndCleanup(true);
			se->removeFromParentAndCleanup(true);
			break;
		}
		se->eneAI(hero->myHero->getPosition());
		se->doAction();
	}
	if(o->groundFlag != 0){
		auto s = (Sprite*)o->groundlist.at(o->groundlist.size()-1);
		int eneCount = o->nextLength/ENE_BLOCK;
		float eachb = o->nextLength/eneCount;
		for(int i = 0;i<eneCount;i++){
			float xx = s->getPositionX()+i*eachb+eachb*CCRANDOM_0_1();
			Enemy* ee = new Enemy(Vec2(xx,s->getPositionY()),ENE_GROUND_ACT,this);
			this->addChild(ee,3);
			ee->addEnemy();
			eneList.pushBack(ee);
		}
		o->groundFlag = 0;
	}
	if(o->bandingCount !=0){
		srand(unsigned(time(0)));
		for(int i = 0;i<o->bandingCount;i++){
			auto s = (Sprite*)o->curBandlist.at(o->curBandlist.size()-1-i);
			if(CCRANDOM_0_1() > 0.65){
				Enemy* ee = new Enemy(Vec2(s->getPositionX()-BAND_WITDH/2,s->getPositionY()+s->getContentSize().height/2),BAND_WITDH*9/10,this);
				this->addChild(ee,3);
				ee->addEnemy();
				eneList.pushBack(ee);
			}
		}
		o->bandingCount = 0;
	}
}

void StageScene::UpdateCoin(){
	if(o->groundFlag != 0){
		auto sg = (Sprite*)o->groundlist.at(o->groundlist.size()-1);
		c->Manager(sg->getPosition(),Vec2(sg->getPositionX()+o->nextLength,sg->getPositionY()));
	}
	c->removeUselessCoins();
}

void StageScene::UpdateNail()
{
	if(o->groundFlag !=0){
		auto sg = (Sprite*)o->groundlist.at(o->groundlist.size()-1);
		na->Manager(sg->getPosition(),Vec2(sg->getPositionX()+o->nextLength,groundHeight));
	}
	na->removeUselessNail();
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

//碰撞检测函数
bool StageScene::onContactBegin(const PhysicsContact& contact)
{
		auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
		if(spriteA == NULL || spriteB == NULL)
			return false;

		//主角与地面碰撞，将主角状态从JUMP恢复为NOMAL
		if((spriteA->getTag() == TAG_HERO && spriteB->getTag() == TAG_GROUND) || (spriteB->getTag() == TAG_HERO && spriteA->getTag() == TAG_GROUND))
		{
			
			auto body = hero->myHero->getPhysicsBody();
			//body->setVelocity(Vec2(body->getVelocity().x,0));
			hero->status = HERO_STATUS_NOMAL;
			hero->runAction("run");
		}

		//子弹与其他物体碰撞，消除子弹，并根据另一物体的类型进行处理
		if(spriteA->getTag() == TAG_BULLET || spriteB->getTag() == TAG_BULLET)
		{
			if(spriteA->getTag() != TAG_BULLET)
			{
				std::swap(spriteA,spriteB);
			}
			b->removeOneBullet(spriteA);
			if(spriteB->getTag() == TAG_BOSS)
			{
				stageBoss->injured(20);
			}
			else if(spriteB->getTag() == TAG_HERO)
			{
				hero->injured(10);
			}
			else if(spriteB->getTag() == TAG_ENEMY)
			{
				auto s = (Enemy*)spriteB->getParent();
				eneList.eraseObject(s);
				if(s->getState() !=666)
				{
					s->setState(ENEMY_DEAD);
					s->doAction();
				}
			}
		}

		//主角与金币碰撞，增加积分
		else if(spriteA->getTag() == TAG_HERO && spriteB->getTag() == TAG_COIN || spriteB->getTag() == TAG_HERO && spriteA->getTag() == TAG_COIN)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GETCOIN_WAV);
			if(spriteA->getTag() == TAG_COIN)
				c->removeOneCoin(spriteA);
			else
				c->removeOneCoin(spriteB);
			auto info = (InformationLayer*)Director::getInstance()->getRunningScene()->getChildByTag(TAG_INFORMATION);
			info->changeScore(10);
		}
		else if(spriteA->getTag() == TAG_HERO && spriteB->getTag() == TAG_NAIL || spriteB->getTag() == TAG_HERO && spriteA->getTag() == TAG_NAIL)
		{
			hero->injured(NAIL_DAMAGE);
			
		}
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
				hero->setBuff(HERO_BUFF_SPEEDUP);
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
}