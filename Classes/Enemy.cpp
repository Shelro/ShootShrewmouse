#include "Enemy.h"

USING_NS_CC;

 Enemy* Enemy::createWithType(EnemyTypes enemyType)
{
	Enemy* enemy = new Enemy;
	if( enemyType == RedMouse ) 
	{
		enemy->bindSprite(Sprite::create("redshrew.png"));
		enemy->type = enemyType;
		enemy->flag = 0;
	}
	else if( enemyType == BlueMouse ) 
	{
		enemy->bindSprite(Sprite::create("blueshrew.png"));
		enemy->type = enemyType;
		enemy->flag = 1;
	}
	else if( enemyType == PurpleMouse ) 
	{
		enemy->bindSprite(Sprite::create("purpleshrew.png"));
		enemy->type = enemyType;
		enemy->flag = 2;
	}
	else if( enemyType == WhiteMouse ) 
	{
		enemy->bindSprite(Sprite::create("shrew.png"));
		enemy->type = enemyType;
		enemy->flag = 3;
	}
	
	return enemy;
}

 Enemy::~Enemy()
 {this->release();}
