#pragma once
#include "Bullet.hpp"
#include <list>

class Weapon
{
private:
	sf::Vector2i windowSize;

public:
	std::list<std::shared_ptr<Bullet>> bullets;

	Weapon(sf::Vector2i windowSize);
	void fire(const sf::Vector2f& originPos, const float& fireAngle);
	void update(float dt);
	void draw(sf::RenderWindow& window);
};

