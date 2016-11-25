#include "HelpingScene.h"

USING_NS_CC;

Scene* Helping::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Helping::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Helping::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    Sprite *bg = Sprite::create("helping-back.png");
    
    // position the label on the center of the screen
    bg->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height /2));
    this->addChild(bg);

    
	auto backMenuItem  = MenuItemImage::create( 
                             "back-up.png",
                             "back-down.png",
							 CC_CALLBACK_1(Helping::menuBackCallback, this));

	backMenuItem->setPosition(Director::getInstance()->convertToGL(Point(410, 600)));

    Menu* mn = Menu::create(backMenuItem, NULL);
	mn->setPosition(Point::ZERO);
    this->addChild(mn);

    return true;
}

void Helping::menuBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
