#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Bullet : public Entity
{
private:
	float bulletSize = 15.f;
	float speed = 1000.f;
	float fireAngle = 0.f;

public:
	Bullet();
	Bullet(sf::Vector2f position);
	void setFireAngle(float angle);
	void update(float dt);

};

