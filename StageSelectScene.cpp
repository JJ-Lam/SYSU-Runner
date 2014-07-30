#include "StageSelectScene.h"
#include "GameMenu.h"
#include "StageScene.h"
#include "UserData.h"

Scene* StageSelectScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = StageSelectScene::create();

    scene->addChild(layer);

    return scene;
}

bool StageSelectScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	selectedStage = 1;
	selectedWeapon = 0;

    auto gameStart = MenuItemImage::create(
                                           "start.png",
                                           "start.png",
										   CC_CALLBACK_1(StageSelectScene::gameStartCallBack,this));
	gameStart->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/8 + origin.y));
	auto menu = Menu::create(gameStart, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
	auto content = "select a stage and choose your weapon";
	auto label = LabelTTF::create(content, "Arial", 24);  
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

   /* auto backGround = Sprite::create("HelloWorld.png");
    backGround->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backGround, 0);*/

	Layer* containerLayer = Layer::create();
	containerLayer->setAnchorPoint(Vec2(0,0));
	auto s1 = Sprite::create("stage1.png");
	s1->setScale(0.5);
	s1->setPosition(450,0);
	containerLayer->addChild(s1);
	auto s2 = Sprite::create("stage2.png");
	s2->setScale(0.5);
	s2->setPosition(1200,0);
	containerLayer->addChild(s2);

	scrollview = ScrollView::create();
	scrollview->setContainer(containerLayer);
	scrollview->setViewSize(visibleSize);
	scrollview->setContentSize(Size(1700,640));
	scrollview->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollview->setDelegate(this);
	scrollview->setAnchorPoint(Vec2(0,0));
	scrollview->setPositionY(100);
	scrollview->setContentOffset(Vec2(0,320));
	this->addChild(scrollview);

	auto normal = MenuItemImage::create(WEAPON_BUTTONS[0],WEAPON_BUTTONS[0],CC_CALLBACK_1(StageSelectScene::weaponMenuCallBack,this));
	normal->setPositionX(normal->getPositionX()-180);
	normal->setTag(0);
	auto damage = MenuItemImage::create(WEAPON_BUTTONS[1],WEAPON_BUTTONS[1],CC_CALLBACK_1(StageSelectScene::weaponMenuCallBack,this));
	damage->setPositionX(damage->getPositionX()-60);
	damage->setTag(1);
	auto destroy = MenuItemImage::create(WEAPON_BUTTONS[2],WEAPON_BUTTONS[2],CC_CALLBACK_1(StageSelectScene::weaponMenuCallBack,this));
	destroy->setPositionX(destroy->getPositionX()+60);
	destroy->setTag(2);
	auto laser = MenuItemImage::create(WEAPON_BUTTONS[3],WEAPON_BUTTONS[3],CC_CALLBACK_1(StageSelectScene::weaponMenuCallBack,this));
	laser->setPositionX(laser->getPositionX()+180);
	laser->setTag(3);
	auto weapon = Menu::create(normal,damage,destroy,laser,NULL);
	weapon->setPositionY(weapon->getPositionY()-130);
	weapon->setTag(10);
	this->addChild(weapon);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(StageSelectScene::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(StageSelectScene::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(StageSelectScene::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}

void StageSelectScene::gameStartCallBack(Ref* pSender)
{
	auto ud = UserData::getInstance();
	ud->stageCount = selectedStage;
	ud->selectedWeapon = selectedWeapon;
	Director::getInstance()->replaceScene(StageScene::createScene());
}

bool StageSelectScene::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void StageSelectScene::onTouchMoved(Touch* touch, Event* event)
{
}

void StageSelectScene::onTouchEnded(Touch* touch, Event* event)
{
	if(scrollview->getContentOffset().x < -250)
	{
		scrollview->setContentOffset(Vec2(-700,320));
		selectedStage = 2;
	}
	else
	{
		scrollview->setContentOffset(Vec2(0,320));
		selectedStage = 1;
	}
}

void StageSelectScene::scrollViewDidScroll(ScrollView* view)
{
    return;
}

void StageSelectScene::scrollViewDidZoom(ScrollView* view)
{
    return;
}

void StageSelectScene::weaponMenuCallBack(Object* sender)
{
	auto item = (MenuItemImage*)sender;
	selectedWeapon = item->getTag();
	item->runAction(Sequence::createWithTwoActions(ScaleTo::create(0.2,0.8),ScaleTo::create(0.2,1.5)));
	auto weapon = this->getChildByTag(10);
	for(int i = 0; i < 4; i++)
	{
		if(weapon->getChildByTag(i)->getScale() != 1)
			weapon->getChildByTag(i)->runAction(ScaleTo::create(0.2,1));
	}
}