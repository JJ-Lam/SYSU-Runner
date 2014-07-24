#include "Coin.h"
#include "resource.h"

USING_NS_CC;

Coin::Coin()
{
	coinsVector = new Vector<Sprite*>;
}

void Coin::removeOneCoin(Sprite* coin)
{
	auto layer = this->getParent();
	layer->removeChild(coin,false);
	coinsVector->eraseObject(coin);
}

void Coin::removeUselessCoins()
{
	auto layer = this->getParent();
	for(Vector<Sprite*>::iterator i = coinsVector->begin(); i != coinsVector->end(); i++)
	{
		auto worldSpace = this->convertToWorldSpace(i[0]->getPosition());

		if(worldSpace.x < 0)
		{
			layer->removeChild(i[0],false);
			i = coinsVector->erase(i);
		}
		if(i == coinsVector->end())
			break;
	}
}

Sprite* Coin::placeCoin()
{
	if(coinsVector->size() <= 4)
	{
		auto layer = this->getParent();
		auto newCoin = Sprite::create("coin.png");
		//newCoin->runAction(RepeatForever::create(RotateBy::create(2,0,360)));

		auto body = PhysicsBody::createCircle(newCoin->getContentSize().width/2);
		body->setDynamic(false);
		body->setContactTestBitmask(0xFFFFFFFF);
		body->setCollisionBitmask(NO_COLLISION_MASK);
		newCoin->setPhysicsBody(body);

		float offset = newCoin->getContentSize().width/2;
		float y = CCRANDOM_0_1()*(JumpHeight+offset - groundHeight+offset) + groundHeight+offset;
		Vec2 temp = Vec2(Director::getInstance()->getWinSize().width, y);
		Vec2 pos = this->convertToNodeSpace(temp);
		newCoin->setPosition(pos);
		coinsVector->pushBack(newCoin);

		return newCoin;
	}
	return NULL;
}