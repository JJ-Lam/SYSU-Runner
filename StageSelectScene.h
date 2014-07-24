#ifndef __STAGESELECTSCENE_H__
#define __STAGESELECTSCENE_H__

#include "cocos2d.h"

class StageSelectScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

	virtual bool init();  
    
	CREATE_FUNC(StageSelectScene);

	void gameStartCallBack(Ref* pSender);
};

#endif // __GAMEMENU_H__
