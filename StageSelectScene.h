#ifndef __STAGESELECTSCENE_H__
#define __STAGESELECTSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class StageSelectScene : public cocos2d::Layer, public ScrollViewDelegate
{
public:
    static Scene* createScene();

	virtual bool init();  
    
	CREATE_FUNC(StageSelectScene);

	void gameStartCallBack(Ref* pSender);

private:
	int selectedStage;
	int selectedWeapon;

	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);

	virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);

	void weaponMenuCallBack(Object* sender);

	ScrollView* scrollview;
};

#endif // __GAMEMENU_H__