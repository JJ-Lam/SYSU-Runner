#ifndef _DROPITEM_
#define _DROPITEM_

#include "cocos2d.h"
#include "resource.h"
USING_NS_CC;
class dropItem :public cocos2d::Node{
public :
	float mark;
	float hx,hy;
	Vector<Sprite*> curdropItemlist;
	Layer* layer;

	dropItem(){};
	float dropMark;
	static dropItem* create(Layer* l);
	
	bool Isdropitem();
	
	void drop();
	
	void Manager(float x,float y);

	int typeSelector();
	
	void removeDropItem();

};
#endif