
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SettingScene.h"
#include "GamePlayScene1.h"
#include "HelpingScene.h"

#include "SystemHeader.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual void onEnterTransitionDidFinish();

    void menuItemHelpCallback(cocos2d::Ref* pSender);
    void menuItemStartCallback(cocos2d::Ref* pSender);
	void menuItemSettingCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	std::thread* _loadingAudioThread;
	void loadingAudio();
};

#endif // __HELLOWORLD_SCENE_H__
