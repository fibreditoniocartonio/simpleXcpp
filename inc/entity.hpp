class Player;
class Level;

class Entity {
 public:
	int x, y, width, height;
	std::string id;
	virtual void Physics(Player* player) {}
	virtual void Render(sf::RenderWindow* window){}
	virtual ~Entity() {}
	Entity (){}
 	Entity (int x, int y, int width, int height){
		this->x=x; this->y=y; this->width=width; this->height=height;
	}
};

class Blocco : public Entity{
 public:
	sf::RectangleShape shape;
	sf::Color color;
	void CreateHitbox(){
		this->shape.setSize(sf::Vector2f(this->width, this->height));
		this->shape.setPosition(this->x, this->y);
		this->shape.setFillColor(this->color);
	}
	void Render(sf::RenderWindow* window) override{
		window->draw(shape);
	}
};
