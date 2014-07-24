#ifndef _My_Map_  
#define _My_Map_  
  
#include "cocos2d.h"      
USING_NS_CC; 

class MyMap: public cocos2d::Node{
public:
	Sprite* mapa;
	Sprite* mapb;
	float mapWidth;
	int mapCount;
	int curMap;
	Layer* mlayer;

	MyMap();
	static MyMap* create(Layer* layer);
	bool mapReload(float xpos);
	
};


#endif