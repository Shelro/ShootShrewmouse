#ifndef __GAMEOVER_SCENE2_H__
#define __GAMEOVER_SCENE2_H__

#include "cocos2d.h"

#include "SystemHeader.h"

class GameOverLayer2 : public cocos2d::Layer
{
	//当前玩家比赛分数
	int score;
public:

	GameOverLayer2(int score);

	virtual bool init();
	virtual void onExit();

	static GameOverLayer2* createWithScore2(int score);
};

#endif // __GAMEOVER_SCENE_H__
