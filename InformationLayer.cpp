#include "InformationLayer.h"
#include "StageScene.h"
#include "GameMenu.h"
#include "resource.h"

bool InformationLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	score = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//stage demo
	auto content = "stage demo";
	auto title = Label::create(content, "Arial", 24);
	title->setPosition(Vec2(origin.x + visibleSize.width/2,
							origin.y + visibleSize.height - title->getContentSize().height));
	this->addChild(title);

	//game over
	auto gameover = "GAME OVER";
	auto gvLabel = Label::create(gameover, "Arial", 48);
	gvLabel->setColor(Color3B(255,0,0));
	gvLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(gvLabel,1,TAG_GAMEOVER);
	gvLabel->setVisible(false);

	//stage clear
	auto stageclear = "STAGE CLEAR !!";
	auto scLabel = Label::create(stageclear, "Arial", 48);
	scLabel->setColor(Color3B(251,216,96));
	scLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(scLabel,1,TAG_STAGECLEAR);
	scLabel->setVisible(false);

	//主角血条和MP条
	herohpbar = new HpBar(100,bar_type::hpbar);
	herohpbar->setHpbar(Vec2(origin.x + visibleSize.width/5, title->getPositionY()),1,1);
	this->addChild(herohpbar,0,TAG_HERO_HPBAR);
	herompbar = new HpBar(100,bar_type::mpbar);
	herompbar->setHpbar(Vec2(origin.x + visibleSize.width/5,title->getPositionY()-20),0.8,0.8);
	this->addChild(herompbar,0,TAG_HERO_MPBAR);

	//计分器
	scoreLabel = Label::create("Points: 0","Arial",24);
	scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/9, herompbar->progressTimer->getPositionY() - herompbar->background->getContentSize().height));
	this->addChild(scoreLabel);

	//暂停按钮
	auto pause = MenuItemImage::create("buttons\\pause.png","buttons\\pause.png",CC_CALLBACK_0(InformationLayer::pause,this));
	pausemenu = Menu::create(pause,NULL);
	pausemenu->setPosition(origin.x + visibleSize.width*0.9, origin.y + visibleSize.height*0.1);
	this->addChild(pausemenu,1);
	
	//暂停恢复选项
	auto resume = MenuItemImage::create("buttons\\resume.png","buttons\\resume.png",CC_CALLBACK_0(InformationLayer::resume,this));
	resume->setPositionX(resume->getPositionX()-50);
	auto back = MenuItemImage::create("buttons\\home.png","buttons\\home.png",CC_CALLBACK_0(InformationLayer::backToMenu,this));
	back->setPositionX(back->getPositionX()+50);
	resumemenu = Menu::create(resume,back,NULL);
	resumemenu->setVisible(false);
	this->addChild(resumemenu,1);

	//关卡结束选项
	auto replay = MenuItemImage::create("buttons\\replay.png","buttons\\replay.png",CC_CALLBACK_0(InformationLayer::replay,this));
	replay->setPosition(replay->getPositionX()-50,replay->getPositionY()-50);
	auto back2 = MenuItemImage::create("buttons\\home.png","buttons\\home.png",CC_CALLBACK_0(InformationLayer::backToMenu,this));
	back2->setPosition(back2->getPositionX()+50,back2->getPositionY()-50);
	endmenu = Menu::create(replay,back2,NULL);
	endmenu->setVisible(false);
	this->addChild(endmenu,1);

	//BOSS血条
	bosshpbar = new HpBar(300,bar_type::hpbar);
	bosshpbar->setHpbar(Vec2(origin.x + visibleSize.width * 0.8, title->getPositionY()),1,1);
	this->addChild(bosshpbar,0,TAG_BOSS_HPBAR);
	bosshpbar->setVisible(false);
	
	//关卡进度条
	auto progress = Sprite::create("hp.jpg");
	progressTimer = ProgressTimer::create(progress);
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer->setMidpoint(Vec2(0,1));
	progressTimer->setBarChangeRate(Vec2(1,0));
	progressTimer->setPercentage(0);
	progressTimer->setPosition(visibleSize.width/2,visibleSize.height*0.05);
	//progressTimer->setScaleX(8);
	//progressTimer->setScaleY(4);
	this->addChild(progressTimer);

	schedule(schedule_selector(InformationLayer::updateProgress),1.0f);

	return true;
}

void InformationLayer::changeScore(int change)
{
	score += change;
	auto temp = __String::createWithFormat("%d",score);
	auto temp2 = __String::create("Points: ");
	temp2->append(temp->getCString());
	scoreLabel->setString(temp2->getCString());
}

void InformationLayer::updateProgress(float time)
{
	auto stagescene = (StageScene*)this->getParent()->getChildByTag(1)->getChildByTag(TAG_STAGESCENE);
	auto progress = ProgressFromTo::create(1,progressTimer->getPercentage(),stagescene->currentPosition/stagescene->totalDistance*100);
	progressTimer->runAction(progress);
}

void InformationLayer::pause()
{
	Director::getInstance()->pause();
	resumemenu->setVisible(true);
	pausemenu->setVisible(false);
}

void InformationLayer::resume()
{
	Director::getInstance()->resume();
	resumemenu->setVisible(false);
	pausemenu->setVisible(true);
}

void InformationLayer::backToMenu()
{
	auto d = Director::getInstance();
	auto s = d->getRunningScene();
	d->replaceScene(GameMenu::createScene());
	d->resume();
}

int InformationLayer::getScore()
{
	return score;
}

void InformationLayer::replay()
{
	Director::getInstance()->replaceScene(StageScene::createScene());
}