#include "Rocket.hpp"

Rocket::Rocket(const sf::Vector2i& windowSize)
{
	this->windowSize = windowSize;
	rocket.setSize(sf::Vector2f(20, 80));
	m_pos = sf::Vector2f(200, 200);
	rocket.setOrigin(sf::Vector2f(rocket.getGlobalBounds().width / 2, rocket.getGlobalBounds().height / 4));
	rocket.setPosition(m_pos);

	dot.setFillColor(sf::Color::Red);
	dot.setRadius(5.f);
	dot.setOrigin(sf::Vector2f(dot.getGlobalBounds().width / 2, dot.getGlobalBounds().height / 2));
}

void Rocket::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		speed += acc * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		speed -= acc * dt;
	}

	if (speed > max_speed)
		speed = max_speed;
	speed = (speed > 0) ? speed - friction * dt : speed + friction * dt;

	int f = (speed > 0) ? 1 : -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		angle -= angle_movement_factor * dt * f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle += angle_movement_factor * dt * f;
	}

	//update player position and rotaion
	m_pos.x -= std::sin(-angle) * speed;
	m_pos.y -= std::cos(-angle) * speed;

	if (m_pos.x < 0)	m_pos.x = 0;
	if (m_pos.x > windowSize.x) m_pos.x = windowSize.x;
	if (m_pos.y < 0) m_pos.y = 0;
	if (m_pos.y > windowSize.y) m_pos.y = windowSize.y;

	rocket.setRotation((angle * (180 / 3.1415)));
	rocket.setPosition(m_pos);
	m_endPos.x = m_pos.x + std::sin(-angle) * 60;
	m_endPos.y = m_pos.y + std::cos(-angle) * 60;

	dot.setPosition(m_endPos);

	//update fireangle
	float dx = m_pos.x - m_endPos.x;
	float dy = m_pos.y - m_endPos.y;
	fireAngle = std::atan2(dy, dx);
	
}

void Rocket::render(sf::RenderWindow& window)
{
	window.draw(rocket);
	window.draw(dot);
}
