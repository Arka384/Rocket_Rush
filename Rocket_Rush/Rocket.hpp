#pragma once
#include <SFML/Graphics.hpp>

class Rocket
{
private:
	sf::CircleShape dot;
	sf::RectangleShape rocket;
	sf::Vector2f m_pos;
	sf::Vector2f m_endPos;
	float speed = 0.f;
	float max_speed = 5.f;
	float acc = 1.1f;
	float friction = 0.4f;
	float angle = 0.f;
	float angle_movement_factor = 2.f;

public:
	Rocket();
	void update(float dt);
	inline sf::Vector2f getPlayerEndPosition() { return m_endPos; }
	inline float getSpeed() { return speed; }
	void render(sf::RenderWindow& window);
};

