#ifndef __ENEMY__H__
#define __ENEMY__H__

#include "cocos2d.h"
#include "Entity.h"
using namespace cocos2d;

#define Red_tag 100
#define Blue_tag 200
#define Purple_tag 300
//定义地鼠类型
typedef enum
{
	RedMouse,		//红色地鼠
	BlueMouse,		//蓝色地鼠
	PurpleMouse,		//紫色地鼠
	WhiteMouse,         
} EnemyTypes;

class Enemy : public Entity
{
public:
	static Enemy* createWithType(EnemyTypes enemytype);
	~Enemy();
	void hit();
	EnemyTypes type;
	CREATE_FUNC(Enemy);
	//int flag;
};
#endif //__ENEMY__H__