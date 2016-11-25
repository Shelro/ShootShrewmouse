#ifndef _Entity_H_
#define _Entity_H_
#include "cocos2d.h"
USING_NS_CC;

class Entity:public Node{
public:
	Entity();
	~Entity();
	Sprite* getSprite();   //»ñÈ¡¾«Áé
	void bindSprite(Sprite* sprite);
	int flag;
private:
	Sprite* _sprite;
};

#endif