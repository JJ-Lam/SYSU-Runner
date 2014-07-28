#include "MyMap.h"
#include "resource.h"
#include "Hero.h"
USING_NS_CC;

MyMap::MyMap(){
	mlayer = NULL;
	mapCount = -1;
	mapWidth = 0;
}
MyMap* MyMap::create(Layer* layer,int lc){
	MyMap* map = new MyMap();
	map->curMaplist.clear();
	map->mlayer = layer;
	map->curMap = 0;
	map->layerMark = lc;
	auto si = Director::getInstance()->getWinSize();
	if(lc == MID_SCENE){
		map->mapa = Sprite::create(PIC_MID);  
		map->mapb = Sprite::create(PIC_MID); 
		map->mapb->setFlippedX(true);
	/*	auto paraMove = MoveBy::create(2,Vec2(MID_RATE*SPEED*2,0));
		
		map->mapa->runAction(RepeatForever::create(seq));
		map->mapb->runAction(RepeatForever::create(seq));*/
	}
	if (lc == FAR_SCENE)
	{
		map->mapa = Sprite::create(PIC_FAR);  
		map->mapb = Sprite::create(PIC_FAR);  
		map->mapb->setFlippedX(true);
		//auto paraMove = MoveBy::create(2,Vec2(FAR_RATE*SPEED*2,0));
		//auto seq =Sequence::create(paraMove,NULL);
		//map->mapa->runAction(RepeatForever::create(seq));
		//map->mapb->runAction(RepeatForever::create(seq));
	}
	if (lc == FARFAR_SCENE)
	{
		map->mapa = Sprite::create(PIC_FARFAR);  
		map->mapb = Sprite::create(PIC_FARFAR);  
		map->mapb->setFlippedX(true);
	}
    // ±³¾°a£¬ÉèÖÃÃªµã×óÏÂ½Ç  
	map->mapa->setAnchorPoint(Point(0, 0));
	if(map->layerMark != FARFAR_SCENE){
	map->mapa->setPosition(ccp(0,0)); 
	}
	else
	{
		map->mapa->setPosition(Point(0,(map->layerMark-2)*groundHeight)); 
	}
	map->mlayer->addChild(map->mapa,(-1)*map->layerMark);  
	map->mapa->setTag(TAG_MAP);
      
	map->mapWidth = map->mapa->getContentSize().width;
    // ±³¾°b£¬ÉèÖÃÃªµØ×óÏÂ½Ç£¬Î»ÖÃ  
	map->mapb->setAnchorPoint(Point(0, 0));  
	if(map->layerMark != FARFAR_SCENE){
		map->mapb->setPosition(ccp(map->mapa->getContentSize().width,0)); 
	}
	else
	{
		map->mapb->setPosition(Point(map->mapWidth,(map->layerMark-2)*groundHeight)); 
	}
	//map->mapb->setPosition(Point(map->mapWidth,(map->layerMark-1)*groundHeight));  
	map->mlayer->addChild(map->mapb,-(map->layerMark));  
	map->mapb->setTag(TAG_MAP);
	
	map->curMaplist.pushBack(map->mapa);
	map->curMaplist.pushBack(map->mapb);
    
	return map;  
}
bool MyMap::mapReload(float xpos){
	auto s = (Sprite*)curMaplist.begin()[0];
	auto bp = convertToWorldSpace(s->getPosition());
	if(bp.x+s->getContentSize().width<0){
		s->removeFromParentAndCleanup(true);
		curMaplist.eraseObject(s);
	}
	auto lm =(Sprite*) curMaplist.at(curMaplist.size()-1);
	auto wp = convertToWorldSpace(lm->getPosition());
	if(wp.x+lm->getContentSize().width < Director::getInstance()->getVisibleSize().width){
		//auto p = (ParallaxNode*)lm->getParent();
		if(layerMark ==MID_SCENE){
			auto newMap =Sprite::create(PIC_MID);
			if(mapCount ==-1){
			newMap->setFlippedX(true);
			}
			mapCount = mapCount*(-1);
			newMap->setAnchorPoint(Vec2(0,0));
			mlayer->addChild(newMap,3,909);
			newMap->setPosition(lm->getPositionX()+lm->getContentSize().width,100);
			auto paraMove = MoveBy::create(2,Vec2(MID_RATE*SPEED*2,0));
			auto seq =Sequence::create(paraMove,NULL);
			newMap->runAction(RepeatForever::create(seq));
			curMaplist.pushBack(newMap);
			//float x = lm->getContentSize().width+lm->getPositionX()-MID_RATE*p->getPositionX()+p->getPositionX();
			auto p = ParallaxNode::create();
			//p->addChild(newMap,3,Vec2(MID_RATE,0),Vec2(x,100));
			//newMap->setPosition(lm->getPositionX()+lm->getContentSize().width,100);
			
			
		}
		else{
			auto newMap =Sprite::create(PIC_FAR);
			if(mapCount ==-1){
				newMap->setFlippedX(true);
			}
			mapCount = mapCount*(-1);
			newMap->setAnchorPoint(Vec2(0,0));
			mlayer->addChild(newMap);
			newMap->setPosition(lm->getPositionX()+lm->getContentSize().width,200);
			auto paraMove = MoveBy::create(2,Vec2(FAR_RATE*SPEED*2,0));
			auto seq =Sequence::create(paraMove,NULL);
			newMap->runAction(RepeatForever::create(seq));
			curMaplist.pushBack(newMap);
			//float x = lm->getContentSize().width+lm->getPositionX()-FAR_RATE*p->getPositionX()+p->getPositionX();
			//p->addChild(newMap,2,Vec2(FAR_RATE,0),Vec2(x,0));

		}
	return true;
	}
	else
	{
		return false;
	}
}
void MyMap::mapupdate(float x){
	auto h = (Hero*)mlayer->getChildByTag(TAG_HERO_CLASS);
	if(h->status != HERO_STATUS_FALLEN)
	{
		if(1)
		{
			Vector<Sprite*>::iterator it;
			for(int i = 0;i<curMaplist.size();i++){
				auto tmp = (Sprite*)curMaplist.at(i);
				float posx = 0;
				switch (layerMark)
				{
				case MID_SCENE:
					{
						posx = 0; 
						break;
					}
				case FAR_SCENE:
					{
						posx = 0.2;
						break;
					}
				case FARFAR_SCENE:
					{
						posx = 0.5;
						break;
					}
				default:
				break;
				}
			tmp->setPositionX(tmp->getPositionX()+posx);
			}
		}
		else
		{
			mapWidth++;
		}
	}
	auto lm = (Sprite*)curMaplist.at(curMaplist.size()-1);
	if(x+lm->getContentSize().width > lm->getPositionX()+Director::getInstance()->getVisibleSize().width)
	{
		auto newMap = Sprite::create(BG_PIC[layerMark-1]);
		if(mapCount == 1){
			newMap->setFlippedX(true);
		}
		mapCount = mapCount*(-1);
		newMap->setAnchorPoint(Vec2(0,0));

		if(layerMark != FARFAR_SCENE){
			newMap->setPosition(Vec2(lm->getPositionX()+lm->getContentSize().width-2,0)); 
		}
		else
		{
			newMap->setPosition(Vec2(lm->getPositionX()+lm->getContentSize().width-2,(layerMark-2)*groundHeight));
		}

		mlayer->addChild(newMap,-layerMark,TAG_MAP);
		curMaplist.pushBack(newMap);
	}
	auto fm = (Sprite*)curMaplist.at(0);
	if(fm->getPositionX()+fm->getContentSize().width<x-200)
	{
		fm->removeFromParentAndCleanup(true);
		curMaplist.eraseObject(fm);
	}
}