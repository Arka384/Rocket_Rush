#include "Weapon.hpp"

Weapon::Weapon(sf::Vector2i windowSize)
{
	this->windowSize = windowSize;
}

void Weapon::fire(const sf::Vector2f& originPos, const float& fireAngle)
{
	Bullet* bullet = new Bullet(originPos);
	bullet->setFireAngle(fireAngle);
	bullets.push_back(std::shared_ptr<Bullet>(bullet));
}

void Weapon::update(float dt)
{
	for (auto it = bullets.begin(); it != bullets.end(); it++) {
		Bullet* b = it->get();
		b->update(dt);
	}
}

void Weapon::draw(sf::RenderWindow& window)
{
	for (auto &b : bullets) {
		window.draw(*b);
	}
}
