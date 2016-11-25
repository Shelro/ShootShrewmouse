#ifndef __GAMEOVER_SCENE1_H__
#define __GAMEOVER_SCENE1_H__

#include "cocos2d.h"

#include "SystemHeader.h"

class GameOverLayer : public cocos2d::Layer
{
	//��ǰ��ұ�������
	int score;
public:

	GameOverLayer(int score);

	virtual bool init();
	virtual void onExit();

	static GameOverLayer* createWithScore(int score);
};

#endif // __GAMEOVER_SCENE_H__
