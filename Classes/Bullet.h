#ifndef __BULLET__H__
#define __BULLET__H__

#include "cocos2d.h"
#include "Entity.h"
#include "Enemy.h"
using namespace cocos2d;

//�����ӵ�����
typedef enum
{
    Red,    //��ɫ�ӵ�
    Blue,       //��ɫ�ӵ�  
    Purple,       //��ɫ�ӵ�
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
	//�����ӵ�����˵���ײ���
	//bool handleBulletCollidingWithEnemy(Enemy* enemy);
};

#endif //__BULLET__H__
