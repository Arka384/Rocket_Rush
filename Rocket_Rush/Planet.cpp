#include "Planet.hpp"

Planet::Planet() = default;

Planet::Planet(const sf::Vector2f& pos, const float& size, const sf::Sprite& sprite)
{
	this->circle_pos = pos;
	this->m_radius = size;
	this->m_sprite = sprite;
	
	this->m_circle.setRadius(this->m_radius);
	this->m_circle.setOrigin(sf::Vector2f(m_circle.getGlobalBounds().width / 2, m_circle.getGlobalBounds().height / 2));
	this->m_circle.setPosition(pos);

}

bool Planet::isColliding(const Entity& other)
{
	return this->m_circle.getGlobalBounds().intersects(other.getGlobalBounds());
}

void Planet::render(sf::RenderWindow& window)
{
	window.draw(m_circle);
}
