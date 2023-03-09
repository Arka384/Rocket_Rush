#pragma once
//#include "Entity.hpp"
#include "LevelMaker.hpp"

class Rocket : public Entity
{
private:
	sf::CircleShape dot;
	sf::Texture rocket_texture;
	sf::Sprite m_sprite;
	sf::Vector2f sprite_scale = sf::Vector2f(3.2, 2.8);
	//sf::RectangleShape rocket;
	sf::Vector2f m_pos;
	sf::Vector2f m_spritePos = sf::Vector2f(0, -20);
	sf::Vector2f m_endPos;
	sf::Vector2f particle_target_pos;
	sf::Vector2i windowSize;
	float speed = 0.f;
	float max_speed = 3.f;
	float acc = 1.6f;
	float friction = 0.5f;
	float fireAngle = 0.f;
	float angle = 0.f;
	float angle_movement_factor = 2.f;

	int m_max_austro = 5;
	int m_austornauts = 4;
	int m_max_fuel = 40;
	int m_fuel = 40;
	int m_max_rock = 10;
	int m_rocks = 0;


public:
	Rocket(const sf::Vector2i& windowSize);
	void update(float dt, LevelMaker& level_maker);

	sf::Vector2f getPlayerEndPosition() { return m_endPos; }
	sf::Vector2f getParticleTargetPos() { return particle_target_pos; }
	sf::Vector2f getmPos() { return m_pos; }
	float getSpeed() { return speed; }
	float getRocketAngle() { return angle; }
	float getFireAngle() { return fireAngle; }
	void setAustronauts(int austro) { this->m_austornauts = austro; }
	int getAsutronauts(void) { return this->m_austornauts; }
	void setFuel(int fuel) { this->m_fuel = fuel; }
	int getFuel(void) { return this->m_fuel; }
	void setRocks(int rock) { this->m_rocks = rock; }
	int getRocks(void) { return this->m_rocks; }


	void render(sf::RenderWindow& window);
};

