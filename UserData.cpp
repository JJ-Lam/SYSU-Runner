#include "UserData.h"
#include "resource.h"

UserData* UserData::ptr = NULL;

UserData::UserData()
{
	auto u = UserDefault::getInstance();
	totalPoints = u->getIntegerForKey("totalPoints",0);
	unlockStage = u->getIntegerForKey("unlockStage",1);
	unlockWeapon = u->getIntegerForKey("unlockWeapon",0);
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
	u->setIntegerForKey("unlockWeapon",unlockWeapon);
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