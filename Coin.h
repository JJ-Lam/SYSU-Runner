#ifndef __COIN_H__
#define __COIN_H__

#include "cocos2d.h"

USING_NS_CC;

class Coin : public cocos2d::Node
{
public:
	Coin();
	Sprite* placeCoin();
	void removeUselessCoins();
	void removeOneCoin(Sprite* bullet);

private:
	Vector<Sprite*>* coinsVector;
};
#endif