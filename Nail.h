#ifndef _NAIL_
#define _NAIL_

#include "cocos2d.h"
#include "resource.h"
USING_NS_CC;

class Nail : public cocos2d::Node{
private:
	Layer* layer;
	Vec2 posStart;
	Vec2 posEnd;
public:
	Nail(Layer* l);
	Vector<Sprite*> curNailList;
	void Manager(Vec2 startpos,Vec2 endpos);
	void addNail();
	float posSelect(float x);
	void removeOneNail(Sprite* n);
	void removeUselessNail();
};

#endif