#include "UserData.h"
#include "resource.h"

UserData* UserData::ptr = NULL;

UserData::UserData()
{
	auto u = UserDefault::getInstance();
	totalPoints = u->getIntegerForKey("totalPoints",0);
	unlockStage = u->getIntegerForKey("unlockStage",1);
	u->setIntegerForKey("weaponLaser",1);
	u->setIntegerForKey("weaponDam",1);
	u->setIntegerForKey("weaponDes",1);
	WeaponMark[0] = u->getIntegerForKey("weaponLaser",0);
	WeaponMark[1] = u->getIntegerForKey("weaponDam",0);
	WeaponMark[2] = u->getIntegerForKey("weaponDes",0);
	stageCount = 0;
}

UserData* UserData::getInstance()
{
	if(ptr == NULL)
		ptr = new UserData();
	return ptr;
}

void UserData::saveData()
{
	auto u = UserDefault::getInstance();
	u->setIntegerForKey("totalPoints",totalPoints);
	u->setIntegerForKey("unlockStage",unlockStage);
	u->setIntegerForKey("weaponLaser",WeaponMark[0]);
	u->setIntegerForKey("weaponDam",WeaponMark[1]);
	u->setIntegerForKey("weaponDes",WeaponMark[2]);
	u->flush();
}

void UserData::gainPoints(int points)
{
	totalPoints += points;
	saveData();
}

void UserData::unlockNewStage()
{
	unlockStage++;
	saveData();
}

bool UserData::unlockNewWeapon(int weaponType){
	if(WeaponMark[weaponType] == 0)
	{
		WeaponMark[weaponType] = 1;
		saveData();
		return true;
	}
	return false;
}
