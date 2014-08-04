#include "Nail.h"
#include "UserData.h"
Nail::Nail(Layer* l){
	layer = l;
	auto ud = UserData::getInstance();
	nail_Block = 2500-(500*ud->stageCount);
}

void Nail::Manager(Vec2 s,Vec2 e){
	int nailCount = 0;
	int tmp = 0;
	
	nailCount = (int)(e.x-s.x)/nail_Block;
	float eacheX = ((e.x-s.x)-(nailCount*nail_Block))/nailCount+nail_Block;
	for(int i = 0;i < nailCount;i++){
		float x = posSelect(eacheX);
		float xx = x+s.x+i*eacheX;
		auto na = Sprite::create(PIC_NAIL);
		if(i>=1){
			if(xx-tmp<na->getContentSize().width)
			{
				i = i-1;
				continue;
			}
			if(e.x-xx<na->getContentSize().width)
			{
				i = i-1;
				continue;
			}
		}
		else{
			if(xx-s.x<na->getContentSize().width)
			{
			xx = xx+100;
			}
		}
		tmp = xx;
		na->setPosition(x+s.x+i*eacheX,groundHeight+na->getContentSize().height/2);
		auto body = PhysicsBody::createBox(na->getContentSize());
		na->setPhysicsBody(body);
		body->setDynamic(false);
		body->setContactTestBitmask(0xFFFFFFFF);
		body->setCollisionBitmask(COIN_COLLISION_MASK);
		na->setTag(TAG_NAIL);
		layer->addChild(na,3);
		curNailList.pushBack(na);
	}
}

float Nail::posSelect(float x){
	float xx = 0;
	xx = CCRANDOM_0_1()*x;
	return xx;
}

void Nail::removeOneNail(Sprite* n)
{
	curNailList.eraseObject(n);
	n->removeFromParentAndCleanup(true);

}
void Nail::removeUselessNail(){
	for(int i = 0;i<curNailList.size();i++){
		auto ws = this->convertToWorldSpace(curNailList.at(i)->getPosition());
		if(ws.x<0){
			curNailList.at(i)->removeFromParentAndCleanup(true);
			curNailList.eraseObject(curNailList.at(i));
			break;
		}
	}
}