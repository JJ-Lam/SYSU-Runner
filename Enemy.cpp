#include "Enemy.h"
USING_NS_CC;



void Enemy::removeEnemy(float x){
	vector<Sprite*>::iterator it;
	it = enemyAlllist.begin();
	if(enemyAlllist.size() != 0){
	if(it[0]->getPositionX() < x){
		it[0]->removeFromParentAndCleanup(true);
		enemyAlllist.erase(it);
	}
	}
}
bool Enemy::isaddEnemy(){
	
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

Enemy::Enemy(Vec2 v,float x,Layer* l){
	layer = l;
	startpos = v;
	activeLength = x;
	attackCount = 0;
}
void Enemy::addEnemy(){
	ene = Sprite::createWithSpriteFrameName("erun0.png");
	state = ENEMY_RUN;
	ene->setPosition(startpos.x,startpos.y+ene->getContentSize().height/2);
	auto body = PhysicsBody::createBox(ene->getContentSize());
	ene->setPhysicsBody(body);
	body->setContactTestBitmask(0xFFFFFFFF);
	body->setCollisionBitmask(COIN_COLLISION_MASK);
	body->applyForce(Vec2(0,body->getMass()*(-1)*(GRAVITY)));
	this->addChild(ene,2);
	ene->setTag(TAG_ENEMY);
	doAction();
}
void Enemy::doAction(){
	switch (state)
	{

	case ENEMY_DEAD:
		{
			state = 666;
			ene->stopAllActions();
			auto dieact = AnimationCache::getInstance()->animationByName("enedie");
			auto animate = Animate::create(dieact);
			auto seq = Sequence::create(animate,CallFunc::create(CC_CALLBACK_0(Enemy::deadCallBack,this)),NULL);
			ene->runAction(seq);
			break;
		}

	case ENEMY_ATTACK:
		{
			ene->stopAllActions();
			auto attact = AnimationCache::getInstance()->animationByName("eneshoot");
			auto animate = Animate::create(attact);
			auto seq = Sequence::create(FlipX::create(false),animate,CallFunc::create(CC_CALLBACK_0(Enemy::attactCallBack,this)),NULL);
			ene->runAction(seq);
			attackCount = 1;
			state = 888;
			break;
			
		}

	case ENEMY_RUN:
		{
			auto runact = AnimationCache::getInstance()->animationByName("enerun");
			auto animate = Animate::create(runact);
			ene->runAction(RepeatForever::create(animate));
			auto moveLeft = MoveBy::create(1,Vec2(-activeLength,0));
			auto moveRight = MoveBy::create(1,Vec2(activeLength,0));
			auto seq = Sequence::create(FlipX::create(true),moveRight,FlipX::create(false),moveLeft,NULL);
			ene->runAction(RepeatForever::create(seq));
			state = 777;
			break;
		}
	default:
		break;
	}
}

void Enemy::eneAI(Vec2 h){
	if(ene->getPositionX()-h.x< ENE_ATTACK_DIST && attackCount == 0 && ene->getPositionX()-h.x > 0)
	{
		state = ENEMY_ATTACK;
	}
	if(attackCount != 0){
		attackCount++;
		if(attackCount ==80){
			attackCount = 0;
		}
	}
}
void Enemy::runCallback(){
	
}

int Enemy::getState(){
	return this->state;
}
void Enemy::setState(int s){
	this->state = s;
}
void Enemy::deadCallBack(){
	ene->removeFromParentAndCleanup(true);
	this->removeFromParentAndCleanup(true);
}
void Enemy::attactCallBack(){
	auto b =(Bullet*)this->getParent()->getChildByTag(TAG_BULLET_CLASS);
	auto bul = b->Launch(ene,-1);
	layer->addChild(bul,3,TAG_BULLET);
}