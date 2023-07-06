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

AABB::AABB(Entity* e1){
    if(e1->xv > 0){
        this->x = e1->x;
    }else{
        this->x = e1->x+e1->xv;
    }
    if(this->yv > 0){
        this->y = e1->y;
    }else{
        this->y = e1->y+e1->yv;
    }
    this->width = e1->width + std::abs(e1->xv); 
    this->height = e1->height + std::abs(e1->yv);
    this->xv = e1->xv;
    this->yv = e1->yv; 
}

void Blocco::CreateHitbox(){
		this->shape.setSize(sf::Vector2f(this->width, this->height));
		this->shape.setPosition(this->x, this->y);
		this->shape.setFillColor(this->color);
}
void Blocco::Render(sf::RenderWindow* window){
	window->draw(shape);
}
