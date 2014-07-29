#ifndef __GAMEMENU_H__
#define __GAMEMENU_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
class GameMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMenu);

	void gameStartCallBack(Ref* pSender);

	void gameShopCallBack(Ref* pSender);

	void gameQuitCallBack();
};

#endif // __GAMEMENU_H__
