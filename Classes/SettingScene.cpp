#include "SettingScene.h"

USING_NS_CC;

Scene* Setting::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Setting::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Setting::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    Sprite *bg = Sprite::create("setting-back.png");
    
    // position the label on the center of the screen
    bg->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height /2));
    this->addChild(bg);

	//音效
    auto soundOnMenuItem = MenuItemImage::create(
                             "on.png",
                             "on.png");
    auto soundOffMenuItem = MenuItemImage::create(
                             "off.png",
                             "off.png");
    
    auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuSoundToggleCallback, this), 
												soundOnMenuItem,
												soundOffMenuItem, 
												NULL);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Point(400, 110)));
    

    //音乐
    auto musicOnMenuItem  = MenuItemImage::create(
                             "on.png",
                             "on.png");
	auto musicOffMenuItem  = MenuItemImage::create(
                             "off.png",
                             "off.png");
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this),
                                                    musicOnMenuItem,
                                                    musicOffMenuItem,
                                                    NULL );
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Point(400, 262)));

    
	auto okMenuItem  = MenuItemImage::create( 
                             "ok-up.png",
                             "ok-down.png",
							 CC_CALLBACK_1(Setting::menuOkCallback, this));

	okMenuItem->setPosition(Director::getInstance()->convertToGL(Point(250, 450)));

    Menu* mn = Menu::create( soundToggleMenuItem,musicToggleMenuItem,okMenuItem, NULL);
	mn->setPosition(Point::ZERO);
    this->addChild(mn);

	//设置音效和音乐选中状态
	UserDefault *defaults  = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		musicToggleMenuItem->setSelectedIndex(0);
	} else {
		musicToggleMenuItem->setSelectedIndex(1);		
	}
	if (defaults->getBoolForKey(SOUND_KEY)) {
		soundToggleMenuItem->setSelectedIndex(0);
	} else {
		soundToggleMenuItem->setSelectedIndex(1);
	}

    
    return true;
}

void Setting::menuOkCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void Setting::menuSoundToggleCallback(Ref* pSender)
{
	UserDefault *defaults  = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY)) {
		defaults->setBoolForKey(SOUND_KEY, false);
	} else {
		defaults->setBoolForKey(SOUND_KEY, true);
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}


void Setting::menuMusicToggleCallback(Ref* pSender)
{
	UserDefault *defaults  = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		defaults->setBoolForKey(MUSIC_KEY, false);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	} else {
		defaults->setBoolForKey(MUSIC_KEY, true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music, true);
	}  
}