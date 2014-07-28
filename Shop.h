#ifndef __SHOP_H__
#define __SHOP_H__

#include "cocos2d.h"
USING_NS_CC;

class Shop : public cocos2d::Layer
{
	public:
    static cocos2d::Scene* createScene();

	virtual bool init();  

	void returnToGameMenu(Ref* pSender);
	void Bought(Ref* pSender);
	void returnToShop(Ref* pSender);
	void Confirm(Ref* pSender);
    
	CREATE_FUNC(Shop);
};

#endif
