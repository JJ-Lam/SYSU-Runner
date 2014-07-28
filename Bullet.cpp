#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet()
{
	bulletsVector = new Vector<Sprite*>;
}

Sprite* Bullet::Launch(Sprite* from, int direction)
{
	auto bullet = Sprite::create("bullet.png");
	bullet->setPosition(from->getPositionX() + 1.2*direction*from->getContentSize().width, from->getPositionY());
	//bullet->runAction(MoveBy::create(1,Vec2(2000,0)));
	auto body = PhysicsBody::createBox(bullet->getContentSize());
	body->setCollisionBitmask(NO_COLLISION_MASK);
	body->applyForce(Vec2(0,body->getMass()*GRAVITY*(-1)));
	body->getShape(0)->setFriction(0);
	body->setContactTestBitmask(0xFFFFFFFF);
	body->setVelocity(Vec2(1000*direction,0));
	bullet->setPhysicsBody(body);

	bulletsVector->pushBack(bullet);

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

		if(worldSpace.x > Director::getInstance()->getWinSize().width)
		{
			layer->removeChild(i[0],false);
			i = bulletsVector->erase(i);
		}
		if(i == bulletsVector->end())
			break;
	}
}

Sprite* Bullet::Launch(Sprite* from ,Vec2 hv){
	float t = 1;
	auto action =MoveTo::create(t,Vec2(hv.x+SPEED,hv.y));
	auto bullet = Sprite::create("CloseNormal.png");
	bullet->setPosition(Point(from->getPositionX(),from->getPositionY()-from->getContentSize().height/2-bullet->getContentSize().height/2));

	auto body = PhysicsBody::createBox(bullet->getContentSize());
	body->setCollisionBitmask(NO_COLLISION_MASK);
	body->getShape(0)->setFriction(0);
	body->setContactTestBitmask(0xFFFFFFFF);
	bullet->setPhysicsBody(body);
	bullet->runAction(action);
	bullet->setTag(TAG_BULLET);
	bulletsVector->pushBack(bullet);
	
	return bullet;
}