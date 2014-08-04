#include "Coin.h"
#include "resource.h"

USING_NS_CC;

Coin::Coin(Layer* l)
{
	this->autorelease();
	//coinsVector = new Vector<Sprite*>;
	auto sp = Sprite::create(PIC_COIN);
	coinSize = sp->getContentSize();
	layer = l;
}

void Coin::removeOneCoin(Sprite* coin)
{/*
	if(coin->getReferenceCount() < 2)
		coin->retain();*/
//	coinsVector.eraseObject(coin);
	
	coin->getPhysicsBody()->removeFromWorld();
	coin->removeFromParentAndCleanup(true);
	//if(coin->getReferenceCount() < 2)
	//	coin->release();
}

void Coin::removeUselessCoins()
{
	
	for(Vector<Sprite*>::iterator i = coinsVector.begin(); i != coinsVector.end(); i++)
	{
		auto worldSpace = this->convertToWorldSpace(i[0]->getPosition());

		if(worldSpace.x < 0)
		{
			/*if(i[0]->getParent()->getChildrenCount()==1){
				i[0]->getParent()->removeFromParentAndCleanup(true);
			}
			else
			{
				i[0]->removeFromParentAndCleanup(true);
			}*/
			i[0]->removeFromParentAndCleanup(true);
			i = coinsVector.erase(i);
		}
		if(i == coinsVector.end())
			break;
	}
}

Sprite* Coin::placeCoin()
{
	if(coinsVector.size() <= 4)
	{
		auto layer = this->getParent();
		auto newCoin = Sprite::create(PIC_COIN);
		newCoin->runAction(RepeatForever::create(RotateBy::create(2,0,360)));

		auto body = PhysicsBody::createCircle(newCoin->getContentSize().width/2);
		body->setDynamic(false);
		body->setContactTestBitmask(0xFFFFFFFF);
		body->setCollisionBitmask(COIN_COLLISION_MASK);
		newCoin->setPhysicsBody(body);

		float offset = newCoin->getContentSize().width/2;
		float y = CCRANDOM_0_1()*(JumpHeight+offset - groundHeight+offset) + groundHeight+offset;
		Vec2 temp = Vec2(Director::getInstance()->getWinSize().width, y);
		Vec2 pos = this->convertToNodeSpace(temp);
		newCoin->setPosition(pos);
		coinsVector.pushBack(newCoin);
		return newCoin;
	}
	return NULL;
}
void Coin::placecoinSquare(int col,int row,float x,float y,Layer* l){
	//auto sb = SpriteBatchNode::create(PIC_COIN);
	//layer->addChild(sb);
	//sb->retain();
	float baseh = y+COIN_BASEHHIGHT;
	for(int i = 0;i<row;i++){
		for(int j = 0;j<col;j++){
			auto co = Sprite::create(PIC_COIN);
			auto body = PhysicsBody::createBox(co->getContentSize());
			body->setDynamic(false);
			body->setContactTestBitmask(0xFFFFFFFF);
			body->setCollisionBitmask(COIN_COLLISION_MASK);
			co->setTag(TAG_COIN);
			co->setPhysicsBody(body);
			l->addChild(co);
			co->setPosition(x+i*COIN_INTER+i*co->getContentSize().width,baseh+j*COIN_BASEHHIGHT);
			coinsVector.pushBack(co);
		}
	}
	
}
void Coin::placecoinPoint(float x,float y){
	auto co = Sprite::create(PIC_COIN);
}
int Coin::typeSelector(){
	int ret = 0;
	ret = (int)(CCRANDOM_0_1()*3)+1;
	return ret;
}
void Coin::placecoinLine(Vec2 posStart,Vec2 posEnd){
	int coinCount = 0;
	//auto sb = SpriteBatchNode::create(PIC_COIN);
	//layer->addChild(sb);
	coinCount = (int)((posEnd.x-posStart.x)/(coinSize.width+COIN_INTER)+1);
	float eachY = (posEnd.y-posStart.y)/(coinCount-1);
	for(int i = 0;i<coinCount;i++){
		auto co = Sprite::create(PIC_COIN);
		auto body = PhysicsBody::createBox(co->getContentSize());
		body->setDynamic(false);
		body->setContactTestBitmask(0xFFFFFFFF);
		body->setCollisionBitmask(COIN_COLLISION_MASK);
		co->setTag(TAG_COIN);
		co->setPhysicsBody(body);
		layer->addChild(co);
		co->setPosition(posStart.x+i*COIN_INTER+i*coinSize.width,posStart.y+groundHeight+i*eachY);
		coinsVector.pushBack(co);
	}
}
void Coin::placecoinArrow(Vec2 ss,Vec2 ee){
	Vec2 s = Vec2(ss.x,ss.y+groundHeight);
	Vec2 e = Vec2(ee.x,ee.y+groundHeight);
	placecoinLine(s,e);
	float xx = calX(3);
	float yy = calY(3);
	Vec2 ups = Vec2(e.x-COIN_INTER,e.y+coinSize.height);
	Vec2 upe = Vec2(e.x-COIN_INTER-xx,e.y+coinSize.height+yy);
	placecoinLine(upe,ups);
	Vec2 ds = Vec2(e.x-COIN_INTER,e.y-coinSize.height);
	Vec2 de = Vec2(e.x-COIN_INTER-xx,e.y-coinSize.height-yy);
	placecoinLine(de,ds);
}
void Coin::Manager(Vec2 startpos,Vec2 endpos){
	int blockCount = 0;
	blockCount = (endpos.x-startpos.x)/1000;
	float eachx = ((endpos.x-startpos.x)-(blockCount*COIN_BLOCK_SIZE))/blockCount+COIN_BLOCK_SIZE;
	for(int i = 0;i<blockCount;i++){
		int type = typeSelector();
		//type = COIN_LINE;
		switch (type)
		{
		case COIN_LINE:
			{
				float x = CCRANDOM_0_1()*COIN_BLOCK_SIZE+startpos.x+i*eachx;
				float y = startpos.y;
				int count = (int)(CCRANDOM_0_1()*7+3);
				float x1 = x+calX(count);
				float y1 = 0;
				if(CCRANDOM_0_1()>0.5){
					y1 = startpos.y;
				}
				else
				{
					y1 = startpos.y+CCRANDOM_0_1()*200;
				}
				placecoinLine(Vec2(x,y),Vec2(x1,y1));
				//auto sp = Sprite::create(PIC_COIN);
				//sp->setPosition(startpos.x+500,startpos.y+100);
				//auto body = PhysicsBody::createBox(sp->getContentSize());
				//body->setDynamic(false);
				//body->setContactTestBitmask(0xFFFFFFFF);
				//body->setCollisionBitmask(COIN_COLLISION_MASK);
				//sp->setTag(TAG_COIN);
				//sp->setPhysicsBody(body);
				//layer->addChild(sp,10);
				////layer->addChild(sp);
				//co->setPosition(posStart.x+i*COIN_INTER+i*coinSize.width,posStart.y+groundHeight+i*eachY);
				/*coinsVector.pushBack(sp);*/
				break;
			}
		case COIN_ARROW:
			{
				float x = CCRANDOM_0_1()*COIN_BLOCK_SIZE+startpos.x+i*eachx;
				float y = startpos.y;
				int count = (int)(CCRANDOM_0_1()*7+3);
				float x1 = x+calX(count);
				float y1 = y;
				placecoinArrow(Vec2(x,y),Vec2(x1,y1));
				break;
			}
		case COIN_SQUARE:
			{
				float x = CCRANDOM_0_1()*COIN_BLOCK_SIZE+startpos.x+i*eachx;
				float y = startpos.y;
				int ww = (int)(CCRANDOM_0_1()*3+2);
				int hh = (int)(ww+CCRANDOM_0_1()*4);
				placecoinSquare(ww,hh,x,y,layer);
			}
		default:
			break;
		}
	}
}
float Coin::calX(int x){
	float ret;
	ret = coinSize.width*(x-1)+COIN_INTER*(x-1);
	return ret;
}
float Coin::calY(int x){
	float ret;
	ret = coinSize.height*(x-1);
	return ret;
}