#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "resource.h"

USING_NS_CC;

enum Weapon
{
	normalBullet = 0,
	damageBullet = 1,
	destroyBullet = 2,
	laser = 3
};

class Bullet : public cocos2d::Node
{
public:
	Bullet();
	Sprite* Launch(Sprite* from, int direction = 1);	//1为向右，-1为向左
	void removeUselessBullets();
	void removeOneBullet(Sprite* bullet);

	Sprite* Launch(Sprite* from ,Vec2 v2);
	Sprite* SpecialLaunch(Sprite* from, Weapon weapon, int direction = 1);

	void playHitEffet(Sprite* bullet);
	void playTrajectoryEffect(Sprite* bullet);

private:
	//Vector<BulletAndTrajectory*> bulletsVector;
	Map<Sprite*,ParticleSystemQuad*> bulletsMap;
	void update(float time);
};
#endif