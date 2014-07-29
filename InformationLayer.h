#ifndef __INFORMATIONLAYER_H__
#define __INFORMATIONLAYER_H__

#include "cocos2d.h"
#include "HpBar.h"

USING_NS_CC;

class InformationLayer : public cocos2d::Layer
{
public:
	Menu* pausemenu, *resumemenu, *endmenu;

	virtual bool init();    
	CREATE_FUNC(InformationLayer);

	void changeScore(int change);
	int getScore();

	void updateProgress(float time);

	void pause();
	void resume();
	void backToMenu();
	void replay();

private:
	HpBar* herohpbar;
	HpBar* bosshpbar;
	Label* scoreLabel;
	ProgressTimer* progressTimer;
	
	int score;
	int gameStatus;
};

#endif