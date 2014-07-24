#include "cocos2d.h"
#include "Obstacle.h"

USING_NS_CC;

Obstacle::Obstacle(){
	srand(unsigned(time(0)));
	timeController = 0;
	startPos = 0;
	groundPos = 0;
}

Obstacle*  Obstacle::create(Layer* l){
	Obstacle* mob = new Obstacle();
	mob->layer = l;
	auto di = Director::getInstance();
	mob->s = di->getWinSize();
	
	mob->curLength = mob->setLength();

	auto bo = PhysicsBody::createEdgeSegment(Point(0,0),Point(mob->curLength,0),PHYSICSBODY_MATERIAL_DEFAULT);
	auto ground = Sprite::create();
	ground->setPosition(Point(0,groundHeight));
	ground->setPhysicsBody(bo);
	ground->setTag(TAG_GROUND);
	l->addChild(ground);

	auto ground_pic = Sprite::create(PIC_GROUND,Rect(0,0,mob->curLength,groundHeight));
	ground_pic->setAnchorPoint(Vec2(0,1));
	ground_pic->setPosition(ground->getPosition());
	l->addChild(ground_pic,2);

	bo->setContactTestBitmask(0xFFFFFFFF);
	mob->curGround = ground->getPositionX();
	mob->nextLength =mob->curLength;
	mob->nextGround = mob->curGround;

	mob->groundlist.pushBack(ground);
	mob->timeController = 0;
	mob->currentOblist = Array::create();
	mob->currentOblist->retain();

	return mob;
	
}
void Obstacle::addWallob(float pos){

	
	//auto body= PhysicsBody::createCircle(obs->getContentSize().width/2);
	//body->setDynamic(false);
	//obs->setPhysicsBody(body);
	float wheight = CCRANDOM_0_1()*(MAX_WALL_HEIGHT-MIN_WALL_HEIGHT)+MIN_WALL_HEIGHT;
	auto obs=Sprite::create(PIC_WALL,Rect(0,0,WALL_WIDTH,wheight));
	obs->setTag(OB_WALL);
	auto body =PhysicsBody::createBox(obs->getContentSize());
	body->setDynamic(false);
	obs->setPhysicsBody(body);

	//int npos =  pos + Director::getInstance()->getWinSize().width/2 + (CCRANDOM_0_1()*MAX_WALL_INTERVAL -MIN_WALL_INTERVAL)+MIN_WALL_INTERVAL;
	//startPos = npos;
	Vec2 temp = Vec2(Director::getInstance()->getWinSize().width,groundHeight + obs->getContentSize().height/2);
	Vec2 position = this->convertToNodeSpace(temp);
	//obs->setPosition(Point( startPos, Director::getInstance()->getWinSize().height/3));
	obs->setPosition(position);
	body->setVelocity(Vec2(0,20));
	currentOblist->addObject(obs);
	layer->addChild(obs);	
}

void Obstacle::addMissile(float pos){
	float offset = setMissilePos();
	auto mi = Sprite::create(PIC_MISSILE,Rect(72,48,20,30));
	mi->setPosition(Point( pos +Director::getInstance()->getWinSize().width /2,offset+heroy));
	auto missileAction = MoveTo::create(1,Vec2(mi->getPositionX()-Director::getInstance()->getWinSize().width,mi->getPositionY()));
	auto body = PhysicsBody::createCircle(mi->getContentSize().width/2);
	mi->setPhysicsBody(body);

	mi->runAction(missileAction);
	mi->setTag(OB_MISSILE);
	currentOblist->addObject(mi);
	layer->addChild(mi);
}

void Obstacle::Manager(float pos,float y){
	herox = pos;
	heroy = y;
	//if(isWallob()){
		//addWallob(pos);
	//}
	
	/*if(isMissileob()){
		addMissile(pos);
	}*/
	if(isGroundob(pos)){
		addGroundob();
	}
	timeController++;
	auto di = Director::getInstance();
	if(currentOblist->count() != 0){
	auto di = Director::getInstance();
	auto s = di->getWinSize();
	for(int i = 0; i<currentOblist->count();i++){
		Sprite* tmpob = (Sprite*)currentOblist->getObjectAtIndex(i);
		if (tmpob->getPositionX() < (pos - s.width/2+100))
		{
			currentOblist->removeObject(tmpob);
			tmpob->removeFromParentAndCleanup(true);
			break;
		}
	}
	}
	auto band = (Sprite*)curBandlist.begin()[0];
	if(band->getPositionX()<pos){
		curBandlist.erase(curBandlist.begin());
	}
}

bool Obstacle::isWallob(){
	if( timeController % 122 == 0 ){
	return true;
	}
	else 
	{
		return false;
	}
}

bool Obstacle::isMissileob(){
	if(timeController %89 == 0){
	return true;
	}
	else
	{
		return false;
	}
}

int obType(){

	return true;
}

int Missile(){
	return true;
}

bool Obstacle::isBandingob(){
	if(timeController %89 ==0){return true;}
	return false;
}
void Obstacle::addBandingob(float pos,float distance){
	int bCount = distance/BAND_WITDH-5;
	if(bCount ==1){
		bCount++;
	}
	float eachDist = (distance-(bCount * BAND_WITDH))/ (bCount+1);
	float baseLine = pos+eachDist;
	float baseHeight = groundHeight;
	while(bCount--){
		if(CCRANDOM_0_1()>0.5){
			baseHeight = baseHeight+BANDING_HEIGHT;
		}
		else
		{
			baseHeight = baseHeight-BANDING_HEIGHT;
			if (baseHeight <groundHeight )
			{
				baseHeight = baseHeight+2*BANDING_HEIGHT;
			}
		}
		auto banding = Sprite::create(PIC_BANDING,Rect(0,0,BAND_WITDH,BAND_H));
		banding->setTag(OB_BANDING);
		banding->setPosition(baseLine+banding->getContentSize().width/2,baseHeight);
		curBandlist.pushBack(banding);
		//auto body = PhysicsBody::createBox(banding->getContentSize());
		//body->applyForce(Vec2(0,body->getMass() *98 ));
		//banding->setPhysicsBody(body);

		layer->addChild(banding);
		currentOblist->addObject(banding);
		baseLine=baseLine+eachDist+BAND_WITDH;
		auto bo = PhysicsBody::createEdgeSegment(Point(0,0),Point(banding->getContentSize().width,0),PHYSICSBODY_MATERIAL_DEFAULT);
		bo->setContactTestBitmask(0xFFFFFFFF);
		auto sprite =Sprite::create();
		sprite->setPhysicsBody(bo);
		sprite->setPosition(Point(banding->getPositionX()-banding->getContentSize().width/2, banding->getPositionY()+banding->getContentSize().height/2));
		bo->setDynamic(false);
		
		auto box = PhysicsBody::createBox(banding->getContentSize());
		box->setDynamic(false);
		box->setContactTestBitmask(0xFFFFFFFF);
		banding->setPhysicsBody(box);
		layer->addChild(sprite);
		sprite->setTag(TAG_GROUND);
		currentOblist->addObject(sprite);
	}
}

bool Obstacle::isGroundob(float x){
	
	float flag =curGround;
	if(x > flag ){
		return true;
	}
	else 
	{
		return false;
	}
}

void Obstacle::addHoleob(float pos){

}

float Obstacle::setLength(){
	float length = 0;
	length = CCRANDOM_0_1()*( GROUND_MAX_LENGTH - GROUND_MIN_LENGTH ) + GROUND_MIN_LENGTH;
	return length;
}

float Obstacle::setInterval(){
	float intverval = 0;
	intverval = CCRANDOM_0_1() * (GROUND_MAX_INTERVAL - GROUND_MIN_INTERVAL) + GROUND_MIN_INTERVAL;
	return intverval;
}

void Obstacle::addGroundob(){
	float tmplength = setLength();
	float tmpint = setInterval();

	auto ground = Sprite::create();
	auto bo = PhysicsBody::createEdgeSegment(Point(0,0),Point(tmplength,0),PHYSICSBODY_MATERIAL_DEFAULT);
	ground->setTag(TAG_GROUND);
	ground->setPosition(Point(nextGround+nextLength+tmpint,groundHeight));
	ground->setPhysicsBody(bo);

	layer->addChild(ground);
	bo->setContactTestBitmask(0xFFFFFFFF);
	addBandingob(nextGround+nextLength,tmpint);

	auto ground_pic =Sprite::create(PIC_GROUND,Rect(0,0,tmplength,groundHeight));
	ground_pic->setAnchorPoint(Vec2(0,1));
	ground_pic->setPosition(ground->getPosition());
	layer->addChild(ground_pic,1);


	curGround = nextGround;
	curLength = nextLength;
	nextGround = ground->getPositionX();
	nextLength = tmplength;

	Sprite* sprite = (Sprite*)groundlist.begin()[0];
	groundlist.pushBack(ground);
	if(groundlist.size()>3){
		layer->removeChild(sprite,true);
		groundlist.erase(groundlist.begin());
	}
}

float Obstacle::setMissilePos(){
	float re = 0;
	re = CCRANDOM_0_1()*(MAX_MISSILE_OFFSET)* 2 + (-1)* MAX_MISSILE_OFFSET;
	return re;
}