#include "GameMenu.h"
#include "StageSelectScene.h"
#include "Shop.h"
#include "UserData.h"
#include "resource.h"

USING_NS_CC;

Scene* GameMenu::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameMenu::create();

    scene->addChild(layer);

    return scene;
}

bool GameMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(GAMEMENU_WAV,true);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto gameStart = MenuItemImage::create(
                                           PIC_START,
                                           PIC_START,
										   CC_CALLBACK_1(GameMenu::gameStartCallBack,this));
	gameStart->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2 ));

	auto gameShop = MenuItemImage::create(
										   PIC_SHOP,
                                           PIC_SHOP,
										   CC_CALLBACK_1(GameMenu::gameShopCallBack,this));
	gameShop->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + origin.y-80 ));

	auto gameSetting = MenuItemImage::create(
											PIC_SETTING,
                                            PIC_SETTING);
	gameSetting->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2 + origin.y - 160));

	auto gameQuit = MenuItemImage::create(
											PIC_QUIT,
											PIC_QUIT,
										   CC_CALLBACK_0(GameMenu::gameQuitCallBack,this));
	gameQuit->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2 + origin.y - 240));

	auto menu = Menu::create(gameStart, gameShop, gameSetting, gameQuit, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
	auto content = "menu";
	auto label = LabelTTF::create(content, "Arial", 24);  
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - 1.5*label->getContentSize().height));
    this->addChild(label, 1);
	label->setVisible(false);

	auto backGround = Sprite::create(PIC_MENUBACKGROUND);
    backGround->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backGround, 0);

	//»ı·ÖÏÔÊ¾
	auto score = UserData::getInstance()->getPoints();
	auto temp = __String::createWithFormat("%d",score);
	auto temp2 = __String::create("Your total points: ");
	temp2->append(temp->getCString());
	auto scoreLabel = Label::create(temp2->getCString(),"Arial",24);
	scoreLabel->setPosition(Vec2(origin.x + scoreLabel->getContentSize().width/2, origin.y + visibleSize.height - 1.5*label->getContentSize().height));
	scoreLabel->setColor(Color3B(0,100,200));
	this->addChild(scoreLabel);

    return true;
}

void GameMenu::gameStartCallBack(Ref* pSender)
{
	Director::getInstance()->replaceScene(StageSelectScene::createScene());
}

void GameMenu::gameShopCallBack(Ref* pSender)
{
	Director::getInstance()->replaceScene(Shop::createScene());
}

void GameMenu::gameQuitCallBack()
{
	Director::getInstance()->end();
}