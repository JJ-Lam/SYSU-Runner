#include "Bullet.h"

USING_NS_CC;

//struct BulletAndTrajectory
//{
//	Sprite* bullet;
//	ParticleSystemQuad* trajectory;
//
//	BulletAndTrajectory(Sprite* b, ParticleSystemQuad* t){bullet = b; trajectory = t;};
//};

Bullet::Bullet()
{
	scheduleUpdate();
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

	auto t = ParticleSystemQuad::create();
	bulletsMap.insert(bullet,t);

	return bullet;
}

void Bullet::removeOneBullet(Sprite* bullet)
{
	playHitEffet(bullet);
	auto layer = this->getParent();
	layer->removeChild(bullet,false);
	bulletsMap.erase(bullet);
}

void Bullet::removeUselessBullets()
{
	auto layer = this->getParent();
	for(auto i : bulletsMap)
	{
		auto worldSpace = this->convertToWorldSpace(i.first->getPosition());

		if(worldSpace.x > Director::getInstance()->getWinSize().width)
		{
			layer->removeChild(i.first);
			layer->removeChild(i.second);
			bulletsMap.erase(i.first);
			break;
		}
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
	bulletsMap.insert(bullet,NULL);
	
	return bullet;
}

//根据武器类型发射子弹
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
			launch->setScale(0.5);
			launch->setTag(TAG_BULLET);
			auto body = PhysicsBody::createBox(launch->getContentSize()/2);
			body->setCollisionBitmask(NO_COLLISION_MASK);
			body->setContactTestBitmask(0xFFFFFFFF);
			body->setVelocity(Vec2(1500*direction,0));
			body->setTag(TAG_DESTROY);
			launch->setPhysicsBody(body);
			break;
		}
	default:
		break;
	}
	playTrajectoryEffect(launch);
	return launch;
}

//子弹击中特效
void Bullet::playHitEffet(Sprite* bullet)
{
	switch (bullet->getPhysicsBody()->getTag())
	{
	case TAG_LASER:
		{
		break;
		}
	case TAG_DAMAGE:
		{
			auto hitEffect = ParticleExplosion::create();
			hitEffect->setLife(0.2);
			hitEffect->setLifeVar(0.3);
			hitEffect->setTextureWithRect( Director::getInstance()->getTextureCache()->addImage("explotion1.png"),Rect(78*3,0,78,59) );
			hitEffect->setStartColor(Color4F(1.0f,0.5f,0.5f,1.0f));
			hitEffect->setStartColorVar(Color4F(0,0,0,0));
			hitEffect->getEndColor();
			hitEffect->setPosition(bullet->getPosition() + Vec2(30,0));
			this->getParent()->addChild(hitEffect);
		}
		break;
	case TAG_DESTROY:
		{
		break;
		}
	default:
		{
		break;
		}
	}
}

//子弹弹道特效
void Bullet::playTrajectoryEffect(Sprite* bullet)
{
	ParticleSystemQuad* trajectoryEffect = ParticleFire::create();
	trajectoryEffect->setDuration(0.5f);
	trajectoryEffect->setLife(0.3);
	trajectoryEffect->setLifeVar(0.2);
	this->getParent()->addChild(trajectoryEffect);
	trajectoryEffect->setPosition(bullet->getPosition());
	bulletsMap.insert(bullet,trajectoryEffect);
}

//弹道跟随子弹
void Bullet::update(float time)
{
	for(auto i : bulletsMap)
	{
		if(i.second != NULL)
		{
			i.second->setPosition(i.first->getPosition());
		}
	}
}