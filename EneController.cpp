#include "EneController.h"

EneController::EneController(){
}

void EneController::initeneAction(){
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Enemy//ene.plist");
	Vector<SpriteFrame*> frames(10);
	char str[20] = {0};

	//run
	for(int i = 0;i<5;i++){
		sprintf(str,"erun%1d.png",i);
		auto frame = cache->getSpriteFrameByName(str);
		frames.pushBack(frame);
	}
	auto runact = Animation::createWithSpriteFrames(frames,0.8f/5.0f);
	AnimationCache::getInstance()->addAnimation(runact,"enerun");
	frames.clear();
	for(int i = 0; i < 9; i++)
	{
		sprintf(str,"eshoot%1d.png",i);
		auto frame = cache->getSpriteFrameByName(str);
		frames.pushBack(frame);
	}
	auto shootAnimation = Animation::createWithSpriteFrames(frames,0.5f/9.0f);
	AnimationCache::sharedAnimationCache()->addAnimation(shootAnimation,"eneshoot");
	frames.clear();

	//die
	for(int i = 0; i < 7; i++)
	{
		sprintf(str,"edie%1d.png",i);
		auto frame = cache->getSpriteFrameByName(str);
		frames.pushBack(frame);
	}
	auto dieAnimation = Animation::createWithSpriteFrames(frames,0.5f/7.0f);
	AnimationCache::sharedAnimationCache()->addAnimation(dieAnimation,"enedie");
	frames.clear();

}


void EneController::Manager(Vec2 start,float pos){
	
}