#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create( "background.png");
	bg->setPosition(Point(origin.x + visibleSize.width/2,
							origin.y + visibleSize.height/2));
	this->addChild(bg);

	Sprite *startSpriteNormal = Sprite::create("start1-up.png");
    Sprite *startSpriteSelected = Sprite::create("start1-down.png");

	MenuItemSprite *startMenuItem = MenuItemSprite::create(startSpriteNormal, 
													startSpriteSelected,
												   CC_CALLBACK_1(HelloWorld::menuItemStartCallback, this));
	startMenuItem->setPosition(Director::getInstance()->convertToGL(Point(250, 250)));
    
	// ÉèÖÃÍ¼Æ¬²Ëµ¥
    MenuItemImage *settingMenuItem = MenuItemImage::create(
                             "setting-up.png",
                             "setting-down.png",
							 CC_CALLBACK_1(HelloWorld::menuItemSettingCallback, this)); 
	settingMenuItem->setPosition(Director::getInstance()->convertToGL(Point(250, 350)));
	
	// °ïÖúÍ¼Æ¬²Ëµ¥
    MenuItemImage *helpMenuItem = MenuItemImage::create(
                             "help-up.png",
                             "help-down.png",
							 CC_CALLBACK_1(HelloWorld::menuItemHelpCallback, this));	
	helpMenuItem->setPosition(Director::getInstance()->convertToGL(Point(250, 450)));

	Menu* mu = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);	
	mu->setPosition(Point::ZERO);
	this->addChild(mu);

    return true;
}


void HelloWorld::menuItemSettingCallback(Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) 
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	auto sc = Setting::createScene();
	//Director::getInstance()->replaceScene(sc);
	Director::getInstance()->pushScene(sc);

}
void HelloWorld::menuItemHelpCallback(Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) 
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
    auto sc = Helping::createScene();
	Director::getInstance()->pushScene(sc);
}

void HelloWorld::menuItemStartCallback(Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) 
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
    auto sc = GamePlayLayer::createScene();
	Director::getInstance()->pushScene(sc);
} 


void HelloWorld::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("BaseLayer onEnterTransitionDidFinish");	
	UserDefault *defaults  = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music, true);
	}
}