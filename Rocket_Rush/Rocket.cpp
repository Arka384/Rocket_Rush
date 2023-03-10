#include "Rocket.hpp"

Rocket::Rocket(const sf::Vector2i& windowSize)
{
	this->windowSize = windowSize;
	this->setFillColor(sf::Color::Yellow);
	this->setSize(sf::Vector2f(26, 80));
	m_pos = sf::Vector2f(200, 200);
	this->setOrigin(sf::Vector2f(this->getGlobalBounds().width / 2, this->getGlobalBounds().height / 4));
	this->setPosition(m_pos);

	dot.setFillColor(sf::Color::Red);
	dot.setRadius(5.f);
	dot.setOrigin(sf::Vector2f(dot.getGlobalBounds().width / 2, dot.getGlobalBounds().height / 2));

	this->rocket_texture.loadFromFile("Assets/Rocket/rocket_glow.png");
	this->m_sprite.setTexture(this->rocket_texture);
	this->m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 4));
	this->m_sprite.setScale(sprite_scale);
	
	this->m_sprite.setPosition(m_spritePos);
}

void Rocket::update(float dt, LevelMaker& level_maker)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		speed += acc * dt;
	}/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		speed -= acc * dt;
	}*/

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

	//level based position clampping
	if (m_pos.x < level_maker.get_LevelWidthSpread().x)	m_pos.x = level_maker.get_LevelWidthSpread().x;
	if (m_pos.x > level_maker.get_LevelWidthSpread().y) m_pos.x = level_maker.get_LevelWidthSpread().y;
	if (m_pos.y < level_maker.get_LevelHeightSpread().x) m_pos.y = level_maker.get_LevelHeightSpread().x;
	if (m_pos.y > level_maker.get_LevelHeightSpread().y) m_pos.y = level_maker.get_LevelHeightSpread().y;

	this->setRotation((angle * (180 / 3.1415)));
	m_sprite.setRotation((angle * (180 / 3.1415)));
	this->setPosition(m_pos);
	
	m_spritePos.x = m_pos.x - std::sin(-angle) * 20;
	m_spritePos.y = m_pos.y - std::cos(-angle) * 20;
	m_sprite.setPosition(m_spritePos);

	m_endPos.x = m_pos.x + std::sin(-angle) * 80;
	m_endPos.y = m_pos.y + std::cos(-angle) * 80;
	particle_target_pos.x = m_pos.x + std::sin(-angle) * 160;
	particle_target_pos.y = m_pos.y + std::cos(-angle) * 160;

	dot.setPosition(m_endPos);

	//update fireangle
	float dx = m_pos.x - m_endPos.x;
	float dy = m_pos.y - m_endPos.y;
	fireAngle = std::atan2(dy, dx);
	
}

void Rocket::render(sf::RenderWindow& window)
{
	//window.draw(*this);
	window.draw(m_sprite);

	window.draw(dot);
}
