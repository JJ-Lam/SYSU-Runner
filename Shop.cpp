#include "Shop.h"
#include "GameMenu.h"
#include "resource.h"
#include "UserData.h"
#include "SimpleAudioEngine.h"
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

	auto bg = Sprite::create("bg.png");
	bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(bg, 0);

	auto returnBack = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_1(Shop::returnToGameMenu, this));
	returnBack->setPosition(Vec2(visibleSize.width * 0.85f, visibleSize.height * 0.1f));
	

	weaponPrice[0] = 1000;
	weaponPrice[1] = 2000;
	weaponPrice[2] = 50000;

	float posY[3];
	for(int i = 0;i<3;i++){
		posY[i]= visibleSize.height*(0.7-i*0.24);
	}

	float posTY[3];
	for(int i = 0;i<3;i++)
	{
		posTY[i] = posY[i];
	}

	float textXX = visibleSize.width*0.5;
	float fontsize = 20;

	float itemX = visibleSize.width*0.2;
	float confirmX = visibleSize.width*0.8;

	//ÏÔÊ¾×Ü»ý·Ö
	auto ud = UserData::getInstance();
	auto ps = __String::createWithFormat("%d",ud->getPoints());
	auto pp = __String::create("Points:");
	pp->append(ps->getCString());
	
	auto pointlabel = Label::create(pp->getCString(),"Arial",48);
	pointlabel->setPosition(visibleSize.width*0.15,visibleSize.height*0.9);
	this->addChild(pointlabel,1);
	
	//ÀØÉäÎäÆ÷
	auto weaponlaser = MenuItemImage::create("shop/laser.png","shop/laser.png");
	weaponlaser->setPosition(Vec2(itemX,posY[0]));
	
	std::string laserinstruction = "This bullet can go through the nails and coins.\n" ;
	std::string mid = "To eqiup this,you will never about the enemy hide\n";
	std::string midd = "behind of the nails and coins!";
	laserinstruction+=mid+midd;
	auto laserlabel = Label::create(laserinstruction,"Arial",fontsize);
	laserlabel->setPosition(textXX,posTY[0]);
	this->addChild(laserlabel,1);
	
	auto Buydlas = MenuItemImage::create(PIC_BUY, PIC_BUY, CC_CALLBACK_1(Shop::Confirm, this));
	Buydlas->setPosition(Vec2(confirmX,posY[0]));
	Buydlas->setTag(TAG_LASER_BUTTON);

	//Ë«±¶ÉËº¦ÎäÆ÷
	auto weapondamage = MenuItemImage::create("shop/damage.png", "shop/damage.png");
	weapondamage->setPosition(Vec2(itemX, posY[1]));
	
	std::string damageinstruction = "This bullet can make the double damage to the boss. \n With this bullet, the boss is as tender as a cat!";
	auto damagelabel = Label::create(damageinstruction,"Arial",fontsize);
	damagelabel->setPosition(textXX,posTY[1]);
	this->addChild(damagelabel,1);

	auto Buydam = MenuItemImage::create(PIC_BUY, PIC_BUY, CC_CALLBACK_1(Shop::Confirm, this));
	Buydam->setPosition(Vec2(confirmX,posY[1]));
	Buydam->setTag(TAG_DAMAGE_BUTTON);
	
	//»÷ËéÎäÆ÷
	auto weapondestory = MenuItemImage::create("shop/destroy.png", "shop/destroy.png");
	weapondestory->setPosition(Vec2(itemX, posY[2]));
	
	std::string destoryinstruction = "This bullet can smash the nails. \n Buy this,you can taste the blood of destorying the world!";
	auto destorylabel = Label::create(destoryinstruction,"Arial", fontsize);
	destorylabel->setPosition(textXX,posTY[2]);
	this->addChild(destorylabel);
	
	auto Buydest = MenuItemImage::create(PIC_BUY, PIC_BUY, CC_CALLBACK_1(Shop::Confirm, this));
	Buydest->setPosition(Vec2(confirmX, posY[2]));
	Buydest->setTag(TAG_DESTROY_BUTTON);
	
	auto menu = Menu::create(returnBack, weapondamage, weapondestory, weaponlaser,Buydam, Buydlas, Buydest, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void Shop::returnToGameMenu(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameMenu::createScene());
}

void Shop::Confirm(Ref* sender)
{
	auto se = (MenuItem*)sender;
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto confirmTrue = MenuItemImage::create("shop/confirm.png", "shop/confirm.png", CC_CALLBACK_1(Shop::Bought, this));
	confirmTrue->setPosition(Vec2(visibleSize.width * 0.4f, visibleSize.height * 0.8f));
	confirmTrue->setTag(se->getTag());

	auto confirmFalse = MenuItemImage::create("shop/return.png", "shop/return.png", CC_CALLBACK_1(Shop::returnToShop, this));
	confirmFalse->setPosition(Vec2(visibleSize.width * 0.6f, visibleSize.height * 0.8f));

	auto menu = Menu::create(confirmTrue, confirmFalse, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void Shop::Bought(Ref* sender)
{
	auto tmp = (MenuItem*)sender;
	int wId = tmp->getTag();
	
	auto ud = UserData::getInstance();
	if(ud->getPoints() >= weaponPrice[wId]){
		if(ud->unlockNewWeapon(wId))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bgm/pressbutton.mp3");
			ud->gainPoints(-weaponPrice[wId]);
			ud->WeaponMark[wId] = 1;
			Director::getInstance()->replaceScene(Shop::createScene());
		}
	}
	
}

void Shop::returnToShop(Ref* pSender)
{
	Director::getInstance()->replaceScene(Shop::createScene());
}
