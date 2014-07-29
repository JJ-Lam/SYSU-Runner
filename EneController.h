#ifndef _ENECONTROLLER_
#define _ENECONTROLLER_

#include "cocos2d.h"
#include "resource.h"
USING_NS_CC;

class EneController : public cocos2d::Node{
private:
	float hx;
	float hy;
	Layer* l;
public:
	EneController();
	void initeneAction();
	void runCallback();

	void Manager(Vec2 start,float pos);
};


#endif