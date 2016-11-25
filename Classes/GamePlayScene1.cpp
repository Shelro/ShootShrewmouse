#include "GamePlayScene1.h"

USING_NS_CC;

 GamePlayLayer::~GamePlayLayer()  
 {  
  if (_targets)  
  {  
    _targets->release();  
    _targets = NULL;  
  }  
  
  if (_projectiles)  
  {  
    _projectiles->release();  
    _projectiles = NULL;  
  }  
  // cpp不需要调用super释放，虚析构函数将会做这些事  
}  

GamePlayLayer::GamePlayLayer()  
:_targets(NULL)  ,_projectiles(NULL)  
{  }  

Scene* GamePlayLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GamePlayLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GamePlayLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	//初始化暂停按钮.
	auto pauseSprite = Sprite::create("gameplay_button_pause.png");
	auto pauseMenuItem = MenuItemSprite::create(pauseSprite, pauseSprite, 
		CC_CALLBACK_1(GamePlayLayer::menuPauseCallback, this));
	auto pauseMenu = Menu::create(pauseMenuItem, NULL);
	pauseMenu->setPosition(Point(30, visibleSize.height - 28));
	this->addChild(pauseMenu,20,999);

	_targets = CCArray::create();
	_targets->retain();
	_projectiles = CCArray::create();
	_projectiles->retain();

	//背景
	Sprite *bg = Sprite::create( "play1-back.png");
	bg->setPosition(Point(origin.x + visibleSize.width/2,
							origin.y + visibleSize.height/2));
	this->addChild(bg);

	//监听器
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GamePlayLayer::keyPressed,this);
	listener->onKeyReleased = CC_CALLBACK_2(GamePlayLayer::keyReleased,this);

	EventDispatcher *EventDispatcher = Director::getInstance()->getEventDispatcher();
	EventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	std::map<std::pair<int,int>,bool> map1;
	for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 3; j++ )
		{
			std::pair<int,int>	p(i,j);
			map1.insert(std::pair<std::pair<int,int>,int>(p,true));
		}

	schedule( schedule_selector(GamePlayLayer::update));

	//this->scheduleUpdate();
	schedule(schedule_selector(GamePlayLayer::enemyCreat),3.0f);

	//初始化
	this->TimeLeft = gametime;
	this->score = 0;

	//在状态栏中显示得分
	this->updateStatusBarScore();

	//开始计时
	this->startWatch();
    return true;
       
}
void GamePlayLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("GamePlayLayer onEnterTransitionDidFinish");	
	UserDefault *defaults  = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music, true);
	}
}

void GamePlayLayer::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    CCLOG("Key with keycode %d pressed", keyCode);
}
//发射子弹
void GamePlayLayer::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	Bullet *Rbullet = Bullet::createWithType(Red);
	Bullet *Bbullet = Bullet::createWithType(Blue);
	
	switch(keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:{	
	Rbullet->setPosition(Point(100,200));	
	Rbullet->setVisible(true);
	Rbullet->scheduleUpdate();
	Rbullet->runAction(MoveTo::create(1,Point(100,900)));
	this->addChild(Rbullet);
	_projectiles->addObject(Rbullet);
	break;
									   }
	case EventKeyboard::KeyCode::KEY_S:{
		Rbullet->setPosition(Point(200,200));
		Rbullet->setVisible(true);
		this->addChild(Rbullet);
		Rbullet->scheduleUpdate();
		Rbullet->runAction(MoveTo::create(1,Point(200,900)));
		_projectiles->addObject(Rbullet);
		break;}
	case EventKeyboard::KeyCode::KEY_D:{
		Rbullet->setPosition(Point(300,200));
		Rbullet->setVisible(true);
		this->addChild(Rbullet);
		Rbullet->runAction(MoveTo::create(1,Point(300,900)));
		_projectiles->addObject(Rbullet);
		break;}
	case EventKeyboard::KeyCode::KEY_F:{
		Rbullet->setPosition(Point(400,200));
		Rbullet->setVisible(true);
		this->addChild(Rbullet);
		Rbullet->runAction(MoveTo::create(1,Point(400,900)));
		_projectiles->addObject(Rbullet);
		break;
			}
    case EventKeyboard::KeyCode::KEY_H:{
		Bbullet->setPosition(Point(100,200));
		Bbullet->setVisible(true);
		this->addChild(Bbullet);
		Bbullet->runAction(MoveTo::create(1,Point(100,900)));
		_projectiles->addObject(Bbullet);
		break;}
    case EventKeyboard::KeyCode::KEY_J:{
		Bbullet->setPosition(Point(200,200));
		Bbullet->setVisible(true);
		this->addChild(Bbullet);
		Bbullet->runAction(MoveTo::create(1,Point(200,900)));
		_projectiles->addObject(Bbullet);
		break;}
	case EventKeyboard::KeyCode::KEY_K:{
		Bbullet->setPosition(Point(300,200));
		Bbullet->setVisible(true);
		this->addChild(Bbullet);
		Bbullet->runAction(MoveTo::create(1,Point(300,900)));
		_projectiles->addObject(Bbullet);
		break;}
	case EventKeyboard::KeyCode::KEY_L:{
		Bbullet->setPosition(Point(400,200));
		Bbullet->setVisible(true);
		this->addChild(Bbullet);
		Bbullet->runAction(MoveTo::create(1,Point(400,900)));
		_projectiles->addObject(Bbullet);
		break;}
	}
}

//地鼠的创建
void GamePlayLayer::enemyCreat(float dt)
{
	_targets->removeAllObjects();
	for(int x=0;x<4;x++)
	{ 
		removeChildByTag(x,true);
		log("removetag:%d",x);
	} 

	std::map<std::pair<int,int>,bool> map1;
	for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 3; j++ )
		{
			std::pair<int,int>	p(i,j);
			map1.insert(std::pair<std::pair<int,int>,int>(p,true));
		}
	std::map<std::pair<int,int>,bool>::iterator it;

	for(int num = 0; num < 4; num++ )
	{

		int i = rand() % 5 ;	
		static Point p1;
		static int i_1,i_2;					//坐标的选择

		i_1 = rand() % 4;
		i_2 = rand() % 3;
		p1 = Point( (i_1 * 100) + 100 , (i_2 * 75) + 425 );
		std::pair<int,int> p;
		p = std::make_pair(i_1,i_2);
		it = map1.find(p);
		bool b = it ->second;
		while(!b)
		{
			i_1 = rand() % 4;
			i_2 = rand() % 3;
			p1 = Point( (i_1 * 100) + 75 , (i_2 * 75) + 412.5 );
			std::pair<int,int> p;
			p = std::make_pair(i_1,i_2);
			it = map1.find(p);
			b = it ->second;
		}
		log("i_1=%d,i_2=%d",i_1,i_2);
		it -> second = false;

		if( i == 0 || i == 1 )
		{			
			log("start creat red");
			auto enemyRed = Enemy::createWithType( RedMouse );
			enemyRed->setVisible(true);
			enemyRed->setPosition(p1);
			this->addChild(enemyRed,1,num);
			_targets->addObject(enemyRed);
		}
		if( i == 2 || i == 3 ) 
		{
			log("start creat blue");
			auto enemyBlue = Enemy::createWithType( BlueMouse );
			enemyBlue->setPosition(p1);
			this->addChild(enemyBlue,1,num);
			_targets->addObject(enemyBlue);
		}
		if( i == 4 ) 
		{	
			log("start creat purple");
			auto enemyWhite = Enemy::createWithType( WhiteMouse );
			enemyWhite->setPosition(p1);
			this->addChild(enemyWhite,1,num);
			_targets->addObject(enemyWhite);
		}
	}
}

void GamePlayLayer::spriteMoveFinished(Entity* sender)  
 {  
  // CCSprite *sprite = (CCSprite *)sender;  
   this->removeChild(sender, true);  
  
   if (sender->flag == 0 ||sender->flag == 1 || sender->flag == 2 || sender->flag == 3)  // target  
   {  
     _targets->removeObject(sender);  
  }  
  else if (sender->flag == 4 || sender->flag == 5 || sender->flag == 6) // projectile  
  {  
    _projectiles->removeObject(sender);  
  }  
}  
void GamePlayLayer::update(float dt)  
{  
	CCArray *projectilesToDelete = CCArray::create();  
	projectilesToDelete->retain();
    CCArray* targetsToDelete =CCArray::create();  
	targetsToDelete->retain();
    CCObject* it = NULL;  
    CCObject* jt = NULL;  

    CCARRAY_FOREACH(_projectiles, it)  
   {  
	   Entity *projectile = (Entity*)(it); 
	   CCRect projectileRect = CCRectMake(  
                                          projectile->getPosition().x - 50,  
                                          projectile->getPosition().y - 37.5+350*dt,  
                                          90,  
                                          70); 
       CCARRAY_FOREACH(_targets, jt)  
       {  
           Entity *target = (Entity*)(jt);  
		   CCRect targetRect = CCRectMake(  
                                          target->getPosition().x - 50,  
                                          target->getPosition().y - 37.5,  
                                          90,  
                                          70);  
  
           if (projectileRect.intersectsRect(targetRect))  
           {  
			   	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
				{
					SimpleAudioEngine::getInstance()->playEffect(sound_2);
				}

               targetsToDelete->addObject(target);  
               projectilesToDelete->addObject(projectile);  

			   if( target->flag == 0 && projectile->flag == 4 )
				   score += EnemyRed_Red_Score;
			   else if( target->flag == 0 && projectile->flag == 5 )
				   score += EnemyRed_Blue_Score;
			   else if( target->flag == 1 && projectile->flag == 4 )
				   score += EnemyBlue_Red_Score;
			   else if( target->flag == 1 && projectile->flag == 5 )
				   score += EnemyBlue_Blue_Score;

			   this->updateStatusBarScore();

			   if( target->flag == 3)
			   {
				   log("GameOver");

				   auto gameOverLayer = GameOverLayer::createWithScore(score);
				   auto gameOverScene = Scene::create();
				   gameOverScene->addChild(gameOverLayer);

				   auto tsc = TransitionFade::create(1.0f, gameOverScene);
				   Director::getInstance()->replaceScene(tsc);
			   
			   }
           }  
       }  
   }  
  
   CCARRAY_FOREACH(targetsToDelete, jt)  
   {  
	   Entity *target =(Entity*)(jt);  
       this->_targets->removeObject(target);  
       this->removeChild(target, true);  
   }  
  
   CCARRAY_FOREACH(projectilesToDelete, it)  
   {  
       Entity* projectile = (Entity*)(it);  
       this->_projectiles->removeObject(projectile);  
       this->removeChild(projectile, true);  
   }  
  
   projectilesToDelete->release();  
   targetsToDelete->release();  


}

//在状态栏中显示得分
void GamePlayLayer::updateStatusBarScore()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//移除上次精灵
	Node* n = this->getChildByTag(303);			
	if (n) {
		this->removeChildByTag(303);
	}


	__String * score = __String::createWithFormat("%d", this->score);
	auto lblScore = Label::createWithTTF(score->getCString(), "fonts/hanyi.ttf", 20);

	lblScore->setColor(Color3B::BLACK);
	lblScore->setPosition(Point(visibleSize.width - 60 , visibleSize.height-15 ));
	this->addChild(lblScore, 20, 303);

}


void GamePlayLayer::menuPauseCallback(Ref* pSender)
{
	log("menuPauseCallback");

	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);		
	}

	//暂停当前层中的node
	this->pause();

	for(const auto& node:this->getChildren())
	{
		node->pause();
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//返回主菜单
	auto backNormal = Sprite::create("gameplay.button.back.png");
	auto backSelected = Sprite::create("gameplay.button.back-on.png");

	auto backMenuItem = MenuItemSprite::create(backNormal, backSelected, 
		CC_CALLBACK_1(GamePlayLayer::menuBackCallback, this));

	//继续游戏菜单
	auto resumeNormal = Sprite::create("gameplay.button.resume.png");
	auto resumeSelected = Sprite::create("gameplay.button.resume-on.png");

	auto resumeMenuItem = MenuItemSprite::create(resumeNormal, resumeSelected, 
		CC_CALLBACK_1(GamePlayLayer::menuResumeCallback, this));

	menu = Menu::create(backMenuItem,resumeMenuItem, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	addChild(menu,20,1000);

}


void GamePlayLayer::menuBackCallback(Ref* pSender)
{
	log("menuBackCallback");
	Director::getInstance()->popScene();
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void GamePlayLayer::menuResumeCallback(Ref* pSender)
{
	log("menuResumeCallback");
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	this->resume();

	for(const auto& node : this->getChildren())
	{
		node->resume();
	}
	removeChild(menu);
}

//计时器
void GamePlayLayer::startWatch(){
	schedule(schedule_selector(GamePlayLayer::downTime),1.0f);
}
void GamePlayLayer::stopWatch(){
	unschedule(schedule_selector(GamePlayLayer::downTime));
}
void GamePlayLayer::downTime(float dt){
    TimeLeft --;

 	Size visibleSize = Director::getInstance()->getVisibleSize();
	//移除上次精灵
	Node* n = this->getChildByTag(203);			
	if (n) {
		this->removeChildByTag(203);
	}
	Node* n2 = this->getChildByTag(103);			
	if (n2) {
		this->removeChildByTag(103);
	}

	__String * time = __String::createWithFormat("%d", TimeLeft);
	auto lblTime = Label::createWithTTF("The Time Left:", "fonts/hanyi.ttf", 20);
	lblTime->setColor(Color3B::BLACK);
	lblTime->setPosition(Point(visibleSize.width - 350 , visibleSize.height - 15));
	this->addChild(lblTime, 20, 203);

	auto lblTime2 = Label::createWithTTF(time->getCString(), "fonts/hanyi.ttf", 20);
	lblTime2->setColor(Color3B::BLACK);
	lblTime2->setPosition(Point(visibleSize.width - 260 , visibleSize.height - 15 ));
	this->addChild(lblTime2, 20, 103);


    if(TimeLeft == 0){
        stopWatch();
		 log("GameOver");

		 auto gameOverLayer = GameOverLayer2::createWithScore2(score);
		 auto gameOverScene = Scene::create();
		 gameOverScene->addChild(gameOverLayer);

		 auto tsc = TransitionFade::create(1.0f, gameOverScene);
		 Director::getInstance()->replaceScene(tsc);   
    }
}


