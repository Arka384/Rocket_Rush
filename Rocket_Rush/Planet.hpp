#pragma once
//#include "Rocket.hpp"
//#include "LevelMaker.hpp"
#include "Entity.hpp"

class Planet
{
private:
	/*sf::CircleShape m_circle;*/
	sf::Sprite m_sprite;
	sf::Vector2f sprite_scale;
	float m_radius = 10.f;
	float m_collision_offset = 20.f;
	sf::Vector2f circle_pos;
	sf::Vector2f sprite_pos;

public:
	sf::CircleShape m_circle;
	Planet();
	Planet(const sf::Vector2f& pos, const float& size, const sf::Sprite& sprite);
	bool isColliding(const Entity& other);
	void render(sf::RenderWindow& window);
};

