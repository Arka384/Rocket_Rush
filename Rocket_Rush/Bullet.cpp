#include "Bullet.hpp"

Bullet::Bullet()
{
	//loading of assets
}

Bullet::Bullet(sf::Vector2f position)
{
	this->setSize(sf::Vector2f(bulletSize, bulletSize));
	this->setOrigin(bulletSize / 2, bulletSize / 2);
	this->setFillColor(sf::Color::Red);
	this->setPosition(position);
}

void Bullet::setFireAngle(float angle)
{
	fireAngle = angle;
	//this->sprite.setRotation(fireAngle * (180 / 3.1415));
}

void Bullet::update(float dt)
{
	this->move(std::cos(fireAngle) * dt * speed, 0);
	this->move(0, std::sin(fireAngle) * dt * speed);
}
