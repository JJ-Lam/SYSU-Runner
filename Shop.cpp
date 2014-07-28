#include "Shop.h"
#include "GameMenu.h"

USING_NS_CC;

Scene* Shop::createScene()
{
    auto scene = Scene::create();
    
    auto layer = Shop::create();

    scene->addChild(layer);

    return scene;
}

bool Shop::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bga.png");
	bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(bg, 0);

	auto returnBack = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_1(Shop::returnToGameMenu, this));
	returnBack->setPosition(Vec2(visibleSize.width * 0.8f, visibleSize.height * 0.1f));

	auto weapon1 = MenuItemImage::create("1q.png", "1q.png");
	weapon1->setPosition(Vec2(visibleSize.width * 0.3f, visibleSize.height * 0.6f));

	auto weapon2 = MenuItemImage::create("1w.png", "1w.png");
	weapon2->setPosition(Vec2(visibleSize.width * 0.3f, visibleSize.height * 0.45f));

	auto weapon3 = MenuItemImage::create("1e.png", "1e.png");
	weapon3->setPosition(Vec2(visibleSize.width * 0.3f, visibleSize.height * 0.3f));

	auto weapon4 = MenuItemImage::create("1r.png", "1r.png");
	weapon4->setPosition(Vec2(visibleSize.width * 0.3f, visibleSize.height * 0.15f));

	auto prise1 = Sprite::create("coin.png");
	prise1->setPosition(Vec2(visibleSize.width * 0.45f, visibleSize.height * 0.6f));
	this->addChild(prise1);

	auto prise2 = Sprite::create("coin1 (1).png");
	prise2->setPosition(Vec2(visibleSize.width * 0.45f, visibleSize.height * 0.45f));
	this->addChild(prise2);

	auto prise3 = Sprite::create("coin1 (2).png");
	prise3->setPosition(Vec2(visibleSize.width * 0.45f, visibleSize.height * 0.3f));
	this->addChild(prise3);

	auto prise4 = Sprite::create("coin1 (3).png");
	prise4->setPosition(Vec2(visibleSize.width * 0.45f, visibleSize.height * 0.15f));
	this->addChild(prise4);

	auto Buy1 = MenuItemImage::create("coin.png", "coin.png", CC_CALLBACK_1(Shop::Confirm, this));
	Buy1->setPosition(Vec2(visibleSize.width * 0.6f, visibleSize.height * 0.6f));

	auto Buy2 = MenuItemImage::create("coin.png", "coin.png", CC_CALLBACK_1(Shop::Confirm, this));
	Buy2->setPosition(Vec2(visibleSize.width * 0.6f, visibleSize.height * 0.45f));

	auto Buy3 = MenuItemImage::create("coin.png", "coin.png", CC_CALLBACK_1(Shop::Confirm, this));
	Buy3->setPosition(Vec2(visibleSize.width * 0.6f, visibleSize.height * 0.3f));

	auto Buy4 = MenuItemImage::create("coin.png", "coin.png", CC_CALLBACK_1(Shop::Confirm, this));
	Buy4->setPosition(Vec2(visibleSize.width * 0.6f, visibleSize.height * 0.15f));

	auto menu = Menu::create(returnBack, weapon1, weapon2, weapon3, weapon4, Buy1, Buy2, Buy3, Buy4, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	
	return true;
}

void Shop::returnToGameMenu(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameMenu::createScene());
}

void Shop::Confirm(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto confirmTrue = MenuItemImage::create("queren1.png", "queren2.png", CC_CALLBACK_1(Shop::Bought, this));
	confirmTrue->setPosition(Vec2(visibleSize.width * 0.4f, visibleSize.height * 0.8f));

	auto confirmFalse = MenuItemImage::create("queren3.png", "queren4.png", CC_CALLBACK_1(Shop::returnToShop, this));
	confirmFalse->setPosition(Vec2(visibleSize.width * 0.6f, visibleSize.height * 0.8f));

	auto menu = Menu::create(confirmTrue, confirmFalse, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void Shop::Bought(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto pScene = Scene::create();
	Director::getInstance()->replaceScene(pScene);

	auto returnToShop = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_1(Shop::returnToShop, this));
	returnToShop->setPosition(Vec2(visibleSize.width * 0.9f, visibleSize.height * 0.1f));

	auto menu = Menu::create(returnToShop, NULL);
	menu->setPosition(Vec2::ZERO);
	pScene->addChild(menu);
}

void Shop::returnToShop(Ref* pSender)
{
	Director::getInstance()->replaceScene(Shop::createScene());
}
