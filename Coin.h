#ifndef __COIN_H__
#define __COIN_H__

#include "cocos2d.h"

USING_NS_CC;

class Coin : public cocos2d::Node
{
public:
	
	SpriteBatchNode* batchCoin;
	
	Coin(Layer* l);
	
	Sprite* placeCoin();
	
	void removeUselessCoins();
	
	void removeOneCoin(Sprite* bullet);
	
	void Manager(Vec2 startpos,Vec2 endpos);
	
	void placecoinSquare(int w,int h,float x,float y,Layer* l);

	void placecoinPoint(float x ,float y);

	void placecoinLine(Vec2 posStart,Vec2 posEnd);

	void placecoinArrow(Vec2 pstart,Vec2 pend);
private:
	Vector<Sprite*>* coinsVector;
	int typeSelector();
	Layer* layer;
	float calX(int x);
	float calY(int x);
	Size coinSize;
};
#endif