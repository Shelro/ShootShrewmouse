#include "Entity.h"

Entity::Entity()
{
	_sprite=NULL;
	flag=0;
}
Entity::~Entity(){}
Sprite* Entity::getSprite()
{
	return this->_sprite;
}
void Entity::bindSprite(Sprite* sprite)
{
	this->_sprite=sprite;
	this->addChild(_sprite);
	
}