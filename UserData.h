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
	
public:
	static UserData* getInstance();
	int getPoints(){return totalPoints;};
	int getUnlockStages(){return unlockStage;};

	int stageCount;
	int selectedWeapon;
	int WeaponMark[3];//解锁武器标记，第一个元素镭射，第二个元素双倍，第三个击碎

	void gainPoints(int points);
	void unlockNewStage();
	void saveData();
	bool unlockNewWeapon(int weaponType);
};

#endif