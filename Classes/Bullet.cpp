#include "Bullet.h"
#include "Enemy.h"

USING_NS_CC;



Bullet* Bullet::createWithType(BulletTypes bulletType)
{
	Bullet* bullet = new Bullet;
	if (bulletType ==  Red)
	{
		bullet->bindSprite(Sprite::create("redbone.png"));
		bullet->type = bulletType;
		bullet->flag = 4;
	}
	else if(bulletType ==  Blue) 
	{
		bullet->bindSprite(Sprite::create("bluebone.png"));
		bullet->type = bulletType;
		bullet->flag = 5;
	}
	else if(bulletType ==  Purple) 
	{
		bullet->bindSprite(Sprite::create("purplebone.png"));
		bullet->type = bulletType;
		bullet->flag = 6;
	}
	
	bullet->setVisible(false);
	return bullet;
}

Bullet::~Bullet()
{
	this->release();
}

void Bullet::update(float dt)
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	if (this->getPosition().y > screenSize.height) {
		//log("isVisible = %d",this->isVisible());
		this->setVisible(false);
		this->unscheduleUpdate();
		this->removeFromParent();

	} 
   
}
//bool Bullet::handleBulletCollidingWithEnemy(Enemy* enemy)
//{
//	Rect bulletRect = getBoundingBox();
//	Point enemyP = getPosition();
//	return bulletRect.containsPoint(enemyP);
//}