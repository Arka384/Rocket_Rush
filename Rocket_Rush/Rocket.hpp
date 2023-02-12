#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Rocket : public Entity
{
private:
	sf::CircleShape dot;
	sf::RectangleShape rocket;
	sf::Vector2f m_pos;
	sf::Vector2f m_endPos;
	sf::Vector2i windowSize;
	float speed = 0.f;
	float max_speed = 2.f;
	float acc = 1.2f;
	float friction = 0.6f;
	float fireAngle = 0.f;
	float angle = 0.f;
	float angle_movement_factor = 2.f;

public:
	Rocket(const sf::Vector2i& windowSize);
	void update(float dt);
	inline sf::Vector2f getPlayerEndPosition() { return m_endPos; }
	inline sf::Vector2f getmPos() { return m_pos; }
	inline float getSpeed() { return speed; }
	inline float getRocketAngle() { return angle; }
	inline float getFireAngle() { return fireAngle; }
	void render(sf::RenderWindow& window);
};

