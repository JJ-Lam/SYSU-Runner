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
	int WeaponMark[3];//����������ǣ���һ��Ԫ�����䣬�ڶ���Ԫ��˫��������������

	void gainPoints(int points);
	void unlockNewStage();
	void saveData();
	bool unlockNewWeapon(int weaponType);
};

#endif