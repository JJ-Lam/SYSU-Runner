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
	int unlockWeapon;	//��λ�����Ʊ�ʾ����������ǰ�Ƿ������1��001����ʾdamageBullet��2��010����ʾdestroyBullet��4��100����ʾlaser
	
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