#include "Planet.hpp"

Planet::Planet() = default;

Planet::Planet(const sf::Vector2f& pos, float size, const sf::Sprite& sprite)
{
	this->circle_pos = pos;
	this->m_radius = size;
	this->m_sprite = sprite;
	
	this->m_circle.setRadius(this->m_radius);
	this->m_circle.setOrigin(sf::Vector2f(m_circle.getGlobalBounds().width / 2, m_circle.getGlobalBounds().height / 2));
	this->m_circle.setPosition(pos);

}

void Planet::update(float dt)
{
	if (n_austronauts != 0) {
		resource_update_timer += dt;
		if (resource_update_timer > resource_update_time) {
			resource_update_timer = 0;
			
			n_rocks += n_austronauts / 2;
			n_fuel += n_austronauts;
		}
	}
}

bool Planet::isColliding(const Entity& other)
{
	//return this->m_circle.getGlobalBounds().intersects(other.getGlobalBounds());

	//circle and rectangle collision
	sf::Vector2f circleDist;
	circleDist.x = std::abs(this->circle_pos.x - other.getPosition().x);
	circleDist.y = std::abs(this->circle_pos.y - other.getPosition().y);

	if (circleDist.x > (other.getGlobalBounds().width / 2 + this->m_radius - m_collision_offset))
		return false;
	if (circleDist.y > (other.getGlobalBounds().height / 2 + this->m_radius - m_collision_offset))
		return false;

	if (circleDist.x <= (other.getGlobalBounds().width / 2))
		return true;
	if (circleDist.y <= (other.getGlobalBounds().height / 2))
		return true;

	float cornerDist = std::pow((circleDist.x - other.getGlobalBounds().width / 2), 2) +
		std::pow((circleDist.y - other.getGlobalBounds().height / 2), 2);

	return (cornerDist <= std::pow(this->m_radius - m_collision_offset, 2));

}

void Planet::render(sf::RenderWindow& window)
{
	window.draw(m_circle);
}
