#ifndef __BULLET__H__
#define __BULLET__H__

#include "cocos2d.h"
#include "Entity.h"
#include "Enemy.h"
using namespace cocos2d;

//定义子弹类型
typedef enum
{
    Red,    //红色子弹
    Blue,       //蓝色子弹  
    Purple,       //紫色子弹
} BulletTypes;

class Bullet : public Entity
{ 
public :
   static Bullet* createWithType(BulletTypes bulletType);
	~Bullet();
	virtual void update(float dt);
	void hit();
	BulletTypes type;
	CREATE_FUNC(Bullet);
	//int flag;
	//处理子弹与敌人的碰撞检测
	//bool handleBulletCollidingWithEnemy(Enemy* enemy);
};

#endif //__BULLET__H__
