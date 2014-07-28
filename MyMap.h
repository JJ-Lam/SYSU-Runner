#ifndef _My_Map_  
#define _My_Map_  
  
#include "cocos2d.h" 

USING_NS_CC; 

class MyMap: public cocos2d::Node{
public:
	Sprite* mapa;
	Sprite* mapb;
	int mapWidth;
	int mapCount;
	int curMap;
	Layer* mlayer;
	void mapupdate(float x);
	MyMap();
	static MyMap* create(Layer* layer,int lc);
	bool mapReload(float xpos);
	int layerMark;
	Vector<Sprite*> curMaplist;
private:
	Sprite* lastMap;
};


#endif