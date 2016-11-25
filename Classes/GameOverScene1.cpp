#include "GameOverScene1.h"

USING_NS_CC;


GameOverLayer::GameOverLayer(int score)
{
	this->score = score;
}

GameOverLayer* GameOverLayer::createWithScore(int score)
{
	GameOverLayer *gover = new GameOverLayer(score);

	if (gover && gover->init()) {
		gover->autorelease();        
		return gover;
	}
	CC_SAFE_DELETE(gover);
	return nullptr;
}

bool GameOverLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//Ìí¼Ó±³¾°µØÍ¼.
	Sprite *bg = Sprite::create("gameover-back.png");
	bg->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(bg);
	
	//×î¸ß·Ö
	UserDefault *defaults = UserDefault::getInstance();
	int highScore = defaults->getIntegerForKey(HIGHSCORE_KEY);    
	if (highScore < score) {
		highScore = score;
		defaults->setIntegerForKey(HIGHSCORE_KEY,highScore);
	}
	__String *text = __String::createWithFormat("%i points", highScore);
	auto lblHighScore = Label::createWithTTF("Highest scores is:", "fonts/hanyi.ttf", 35);
	lblHighScore->setAnchorPoint(Point(0,0));
	lblHighScore->setPosition(Point(visibleSize.width - 300, visibleSize.height - 260));
	addChild(lblHighScore);

	auto lblScore = Label::createWithTTF(text->getCString(), "fonts/hanyi.ttf", 34);
	lblScore->setColor(Color3B(75,255,255));	
	lblScore->setAnchorPoint(Point(0,0));
	lblScore->setPosition(Point( lblHighScore->getPosition() - Point(-30, 40)));
	addChild(lblScore);

	__String *text_now = __String::createWithFormat("%i points", score);
	auto lblNowScore =  Label::createWithTTF("Now scores is:", "fonts/hanyi.ttf", 35);
	lblNowScore->setAnchorPoint(Point(0,0));
	lblNowScore->setPosition(Point(lblHighScore->getPosition() - Point(-30,80)));
	addChild(lblNowScore);

	auto lblNScore = Label::createWithTTF(text_now->getCString(), "fonts/hanyi.ttf", 34);
	lblNScore->setColor(Color3B(75,255,255));	
	lblNScore->setAnchorPoint(Point(0,0));
	lblNScore->setPosition(Point(lblNowScore->getPosition() - Point(-20, 40)));
	addChild(lblNScore);


	auto text2 = Label::createWithTTF("Tap the Screen to Back to Main Menu", "fonts/hanyi.ttf", 30);
	text2->setPosition(visibleSize.width/2, 20);
	addChild(text2);

	//×¢²á ´¥ÃþÊÂ¼þ¼àÌýÆ÷
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [](Touch* touch, Event* event){ 
		Director::getInstance()->popScene();
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
			SimpleAudioEngine::getInstance()->playEffect(sound_1);
		}
		return false;
	};

	// Ìí¼Ó ´¥ÃþÊÂ¼þ¼àÌýÆ÷
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


void GameOverLayer::onExit()
{
	Layer::onExit();	
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}
