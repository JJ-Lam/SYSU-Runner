#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet()
{
	bulletsVector = new Vector<Sprite*>;
	initParticleEffects();
}

Sprite* Bullet::Launch(Sprite* from, int direction)
{
	auto bullet = Sprite::create(PIC_NORMALBULLET);
	bullet->setPosition(from->getPositionX() + 1.2*direction*from->getContentSize().width/2, from->getPositionY());
	bullet->setTag(TAG_BULLET);
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
	playHitEffet(bullet);
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
	bullet->setPosition(Vec2(from->getPositionX(),from->getPositionY()-from->getContentSize().height/2-bullet->getContentSize().height/2));

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

Sprite* Bullet::SpecialLaunch(Sprite* from, Weapon weapon, int direction)
{
	auto visibleWidth = Director::getInstance()->getVisibleSize().width;
	Sprite* launch;
	switch (weapon)
	{
	case normalBullet:
		launch = Launch(from,direction);
		break;
	case laser:
		{
			launch = Sprite::create(PIC_LASER);
			launch->setPosition(from->getPositionX() + direction*from->getContentSize().width, from->getPositionY());
			launch->setTag(TAG_BULLET);
			auto body = PhysicsBody::createBox(launch->getContentSize());
			body->setCollisionBitmask(NO_COLLISION_MASK);
			body->setContactTestBitmask(0xFFFFFFFF);
			body->setVelocity(Vec2(3500*direction,0));
			body->setTag(TAG_LASER);
			launch->setPhysicsBody(body);
			break;
		}
	case damageBullet:
		{
			launch = Sprite::create(PIC_DAMAGEBULLET);
			launch->setPosition(from->getPositionX() + direction*from->getContentSize().width, from->getPositionY());
			launch->setTag(TAG_BULLET);
			auto body = PhysicsBody::createBox(launch->getContentSize());
			body->setCollisionBitmask(NO_COLLISION_MASK);
			body->setContactTestBitmask(0xFFFFFFFF);
			body->setVelocity(Vec2(2000*direction,0));
			body->setTag(TAG_DAMAGE);
			launch->setPhysicsBody(body);
			break;
		}
	case destroyBullet:
		{
			launch = Sprite::create(PIC_DESTROYBULLET);
			launch->setPosition(from->getPositionX() + direction*from->getContentSize().width, from->getPositionY());
			launch->setTag(TAG_BULLET);
			auto body = PhysicsBody::createBox(launch->getContentSize());
			body->setCollisionBitmask(NO_COLLISION_MASK);
			body->setContactTestBitmask(0xFFFFFFFF);
			body->setVelocity(Vec2(800*direction,0));
			body->setTag(TAG_DESTROY);
			launch->setPhysicsBody(body);
			break;
		}
	default:
		break;
	}
	return launch;
}

void Bullet::playHitEffet(Sprite* bullet)
{
	auto hitEffect = hitEffectVector.at(bullet->getPhysicsBody()->getTag());
	hitEffect->setPosition(bullet->getPosition());
	this->getParent()->addChild(hitEffect);
	//hitEffectVector.pushBack(hitEffect);
	//scheduleOnce(schedule_selector(Bullet::removeHitEffet),1.0f);
}

void Bullet::removeHitEffet(float time)
{
	auto hitEffect = hitEffectVector.begin()[0];
	hitEffect->removeFromParent();
}

void Bullet::initParticleEffects()
{
	//explotion for damageBullet
	auto hitEffect = ParticleExplosion::create();
	hitEffect->setLife(0.2);
	hitEffect->setLifeVar(0.3);
	hitEffect->setTextureWithRect( Director::getInstance()->getTextureCache()->addImage("explotion1.png"),Rect(78*3,0,78,59) );
	particleEffects.insert(Weapon::damageBullet,hitEffect);
}