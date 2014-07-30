#ifndef __USERDATA_H__
#define __USERDATA_H__

#include "cocos2d.h"
USING_NS_CC;

class UserData
{
private:
	static UserData *ptr;
	UserData();

	int totalPoints;
	int unlockStage;
	int unlockWeapon;	//三位二进制表示三种武器当前是否解锁，1（001）表示damageBullet，2（010）表示destroyBullet，4（100）表示laser
	
public:
	static UserData* getInstance();
	int getPoints(){return totalPoints;};
	int getUnlockStages(){return unlockStage;};
	int getUnlockWeapon(){return unlockWeapon;};

	int stageCount;
	int selectedWeapon;

	void gainPoints(int points);
	void unlockNewStage();
	void saveData();
};

#endif