#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet()
{
	bulletsVector = new Vector<Sprite*>;
}

//1为水平向右，-1为水平向左
Sprite* Bullet::Launch(Sprite* from, int direction)
{
	auto bullet = Sprite::create("bullet.png");
	bullet->setPosition(from->getPositionX() + direction*from->getContentSize().width/2, from->getPositionY());
	//bullet->setScale(0.5);
	auto body = PhysicsBody::createCircle(bullet->getContentSize().width /2);
	//body->getShape(0)->setFriction(0);
	body->setContactTestBitmask(0xFFFFFFFF);
	body->setVelocity(Vec2(2000*direction,0));
	bullet->setPhysicsBody(body);

	bulletsVector->pushBack(bullet);

	//if(bulletsVector->size() > 1)
	//	CCLOG("");

	return bullet;
}

void Bullet::removeOneBullet(Sprite* bullet)
{
	auto layer = this->getParent();
	layer->removeChild(bullet,false);
	bulletsVector->eraseObject(bullet);
}

void Bullet::removeUselessBullets()
{
	auto layer = this->getParent();
	for(Vector<Sprite*>::iterator i = bulletsVector->begin(); i != bulletsVector->end(); i++)
	{
		auto worldSpace = this->convertToWorldSpace(i[0]->getPosition());

		if(worldSpace.x > Director::getInstance()->getWinSize().width || worldSpace.x < 0)
		{
			layer->removeChild(i[0],false);
			i = bulletsVector->erase(i);
		}
		if(i == bulletsVector->end())
			break;
	}
}

//hv是目标位置
Sprite* Bullet::Launch(Sprite* from ,Vec2 hv){
	float t = 1;
	auto action =MoveTo::create(t,Vec2(hv.x+SPEED,hv.y));
	auto bullet = Sprite::create("CloseNormal.png");
	bullet->setPosition(Point(from->getPositionX(),from->getPositionY()-from->getContentSize().height/2-bullet->getContentSize().height/2));

	auto body = PhysicsBody::createCircle(bullet->getContentSize().width /4);
	body->getShape(0)->setFriction(0);
	body->setContactTestBitmask(0xFFFFFFFF);
	bullet->setPhysicsBody(body);
	bullet->runAction(action);
	bulletsVector->pushBack(bullet);
	bullet->setTag(TAG_BULLET);
	return bullet;
}