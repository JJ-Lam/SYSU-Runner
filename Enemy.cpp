#include "Enemy.h"
USING_NS_CC;

Enemy::Enemy(){
	b = new Bullet();
	ob = new Obstacle();
	timeCount = 0;
}
Enemy* Enemy::create(Layer* l,Obstacle* o,Bullet* bu){
	Enemy* ene = new Enemy();
	ene->b = bu;
	ene->layer = l;
	ene->ob = o;
	return ene;
}

void Enemy::Manager(float x,float y){
	
	if(isaddEnemy( x )){
		addEnemy( x,y);
	}
	enemyAttack(x,y);
	removeEnemy(x);
}
void Enemy::removeEnemy(float x){
	if(enemyAlllist.size() != 0){
	auto e = enemyAlllist.begin()[0];
	if(e->getPositionX() < x){
		enemyAlllist.eraseObject(e);
		e->removeFromParentAndCleanup(true);

	}
	}
}
bool Enemy::isaddEnemy(float x){
	
	if(timeCount % 120 == 0){
		if(timeCount==0){
			timeCount++;
		}
		else
		{
			timeCount= 1;
		}
		return true;
	}
	else
	{
		timeCount++;
		return false;
	}

}

void Enemy::addEnemy(float x,float y){

	auto ene = Sprite::create(PIC_ENE,PIC_ENER);
	ene->setPosition(Point(x+Director::getInstance()->getWinSize().width*5/4,Director::getInstance()->getWinSize().height));
	//auto body = PhysicsBody::createBox(ene->getContentSize());
	//ene->setPhysicsBody(body);

	layer->addChild(ene);
	enemyAlllist.pushBack(ene);
	
	ene->runAction(randomEnemy());
}
Action* Enemy::randomEnemy(){
	auto size = Director::getInstance()->getWinSize();
	Vec2 tmp = Vec2((-1)*size.width,0);
	auto pos = this->convertToNodeSpace(tmp);
	
	ccBezierConfig mybe;
	mybe.endPosition=tmp;
	mybe.controlPoint_1 = Vec2( (-1)* size.width * CON1_XBEI,(-1)*size.height * CON1_YBEI);
	mybe.controlPoint_2 = Vec2( (-1)* size.width* CON2_XBEI,(-1)*size.height *CON2_YBEI);
	auto myBaction = BezierBy::create(4,mybe);
	return myBaction;
}
void Enemy::enemyAttack(float x,float y){
	if( timeCount == 1 ||timeCount % 30 == 0 )
	{
	Vector<Sprite*>::iterator it;
	
	for(it = enemyAlllist.begin();it != enemyAlllist.end();it++){
		layer->addChild(b->Launch(it[0],Vec2(x,y)));
	}
	}
	b->removeUselessBullets();
}