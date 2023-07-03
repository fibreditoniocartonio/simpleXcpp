#include "../inc/entity.hpp"
#include "../inc/player.hpp"
#include "../inc/level.hpp"

void Entity::Physics(Player* player) {}
void Entity::Render(sf::RenderWindow* window){}
Entity::~Entity() {}
Entity::Entity (){}
Entity::Entity (float x, float y, int width, int height){
	this->x=x; this->y=y; this->width=width; this->height=height;
}

void Blocco::CreateHitbox(){
		this->shape.setSize(sf::Vector2f(this->width, this->height));
		this->shape.setPosition(this->x, this->y);
		this->shape.setFillColor(this->color);
}
void Blocco::Render(sf::RenderWindow* window){
	window->draw(shape);
}
