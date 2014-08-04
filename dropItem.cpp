#include "dropItem.h"
#include "cocos2d.h"
#include "UserData.h"
USING_NS_CC;


dropItem* dropItem::create(Layer* l){
	dropItem* di = new dropItem();
	di->mark = 0;
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(PLIST_DROPITEM);
	di->layer = l;
	di->dropMark = UserData::getInstance()->stageCount*1500;
	return di;
}

bool dropItem::Isdropitem(){
	if(hx - mark >dropMark){
		mark = hx;
		return true;
	}
	else
	{
		return false;
	}
}
int dropItem::typeSelector(){
	int  type = CCRANDOM_0_1()*5;

	return type;
}
void dropItem::drop(){
	int type = typeSelector();
	type = type+666;
	auto size =Director::getInstance()->getWinSize();
	switch(type)
	{
		case TAG_DROP_INVINCIBLE:
			{
			auto tdi = Sprite::createWithSpriteFrameName("invincible.png");
			auto body = PhysicsBody::createCircle(tdi->getContentSize().width/2);
			//body->setCollisionBitmask(NO_COLLISION_MASK);
			body->setContactTestBitmask(0xFFFFFFFF);
			tdi->setPosition(Vec2(hx+size.width*1.4,size.height));
			body->applyForce(Vec2(0,body->getMass()*(-1)*0.9*GRAVITY));
			tdi->setPhysicsBody(body);
			layer->addChild(tdi,0,type);
			curdropItemlist.pushBack(tdi);
			break;
			}
		case TAG_DROP_SPEEDUP:
			{
			auto tdi = Sprite::createWithSpriteFrameName("speedup.png");
			auto body = PhysicsBody::createCircle(tdi->getContentSize().width/2);
			//body->setCollisionBitmask(NO_COLLISION_MASK);
			body->setContactTestBitmask(0xFFFFFFFF);
			tdi->setPosition(Vec2(hx+size.width*1.4,size.height));
			body->applyForce(Vec2(0,body->getMass()*(-1)*0.9*GRAVITY));
			tdi->setPhysicsBody(body);
			layer->addChild(tdi,0,type);
			curdropItemlist.pushBack(tdi);
			break;
			}
		case TAG_DROP_HEAL:
		{
			auto tdi = Sprite::createWithSpriteFrameName("cure.png");
			auto body = PhysicsBody::createCircle(tdi->getContentSize().width/2);
			//body->setCollisionBitmask(NO_COLLISION_MASK);
			body->setContactTestBitmask(0xFFFFFFFF);
			tdi->setPosition(Vec2(hx+size.width*1.4,size.height));
			body->applyForce(Vec2(0,body->getMass()*(-1)*0.9*GRAVITY));
			tdi->setPhysicsBody(body);
			layer->addChild(tdi,0,type);
			curdropItemlist.pushBack(tdi);
			break;
		}
		case TAG_DROP_POISON:
			{
			auto tdi = Sprite::createWithSpriteFrameName("poison.png");
			auto body = PhysicsBody::createCircle(tdi->getContentSize().width/2);
			//body->setCollisionBitmask(NO_COLLISION_MASK);
			body->setContactTestBitmask(0xFFFFFFFF);
			tdi->setPosition(Vec2(hx+size.width*1.4,size.height));
			body->applyForce(Vec2(0,body->getMass()*(-1)*0.9*GRAVITY));
			tdi->setPhysicsBody(body);
			layer->addChild(tdi,0,type);
			curdropItemlist.pushBack(tdi);
			break;
			}
		case TAG_DROP_BLIND:
			{
			auto tdi = Sprite::createWithSpriteFrameName("flash.png");
			auto body = PhysicsBody::createCircle(tdi->getContentSize().width/2);
			//body->setCollisionBitmask(NO_COLLISION_MASK);
			body->setContactTestBitmask(0xFFFFFFFF);
			tdi->setPosition(Vec2(hx+size.width,size.height));
			body->applyForce(Vec2(0,body->getMass()*(-1)*0.9*GRAVITY));
			tdi->setPhysicsBody(body);
			layer->addChild(tdi,0,type);
			curdropItemlist.pushBack(tdi);
			break;
			}
	}
}
void dropItem::Manager(float x,float y){
	hx = x;
	hy = y;
	if(Isdropitem()){
		drop();
	}
}

void dropItem::removeDropItem(){
	for(Vector<Sprite*>::iterator i = curdropItemlist.begin(); i != curdropItemlist.end(); i++)
	{
		auto worldSpace = this->convertToWorldSpace(i[0]->getPosition());

		if(worldSpace.x < 0)
		{
			layer->removeChild(i[0],false);
			i = curdropItemlist.erase(i);
		}
		if(i == curdropItemlist.end())
			break;
	}
}