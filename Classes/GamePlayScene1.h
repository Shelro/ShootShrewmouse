#ifndef __GAME_PLAY_SCENE_H__
#define __GAME_PLAY_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Entity.h"
#include "SystemHeader.h"
#include "GameOverScene1.h"
#include "GameOverScene2.h"

//�������ʱ��
#define gametime 60
//���� �������˻�õķ���.
typedef enum
{
	EnemyBlue_Blue_Score = 3,		//��ɫ�ӵ�������ɫ����
	EnemyRed_Red_Score = 3,
	EnemyBlue_Red_Score = -1,
	EnemyRed_Blue_Score = -1,
} EnemyScores;

class GamePlayLayer : public cocos2d::Layer
{
public:

	GamePlayLayer();
	~GamePlayLayer();
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual void onEnterTransitionDidFinish();
	//virtual void onExit();
	//virtual void onEnter();

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);


	//��������
	void enemyCreat(float dt);
	static std::map<std::pair<int,int>,bool> map1;

	//��״̬���и��µ÷�.
	void updateStatusBarScore();

	//�˵��ص�����
	void menuPauseCallback(cocos2d::Ref* pSender);
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuResumeCallback(cocos2d::Ref* pSender);

	//��ʱ��
	int TimeLeft;
	void startWatch();
	void stopWatch();
	void downTime(float dt);

	virtual void update(float dt);
	
	CREATE_FUNC(GamePlayLayer);

	void spriteMoveFinished(Entity* sender);

protected:  
    cocos2d::CCArray *_targets;  
    cocos2d::CCArray *_projectiles; 
	//����
	int score;
private:
	cocos2d::Menu* menu;

};
#endif // __GAME_PLAY_SCENE_H__
