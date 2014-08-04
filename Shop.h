#ifndef __SHOP_H__
#define __SHOP_H__

#include "cocos2d.h"
USING_NS_CC;

enum MyEnum
{
	TAG_LASER_BUTTON = 0,
	TAG_DAMAGE_BUTTON = 1,
	TAG_DESTROY_BUTTON = 2
};
class Shop : public cocos2d::Layer
{
	public:
    static cocos2d::Scene* createScene();

	virtual bool init();  

	void returnToGameMenu(Ref* pSender);
	void Bought(Ref* sender);
	void returnToShop(Ref* pSender);
	void Confirm(Ref* sender);
    
	CREATE_FUNC(Shop);

private:
	int weaponPrice[3];
	//record the price
};

#endif
