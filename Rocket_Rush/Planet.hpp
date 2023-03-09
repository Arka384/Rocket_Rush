#pragma once
//#include "Rocket.hpp"
//#include "LevelMaker.hpp"
#include "Entity.hpp"

class Planet
{
private:
	/*sf::CircleShape m_circle;*/
	sf::Vector2f sprite_scale;
	float m_radius = 10.f;
	float m_collision_offset = 20.f;
	sf::Vector2f circle_pos;
	sf::Vector2f sprite_pos;
	bool showInventory = false;

	//gameplay
	int n_austronauts = 0;
	int n_fuel = 0;
	int n_rocks = 0;
	float resource_update_time = 5.f;
	float resource_update_timer = 0.f;

	//sprites and txtures
	sf::Sprite m_sprite;

public:
	sf::CircleShape m_circle;
	Planet();
	Planet(const sf::Vector2f& pos, float size, const sf::Sprite& sprite);
	
	void setAustronauts(int austro) { this->n_austronauts = austro; }
	int getAsutronauts(void) { return this->n_austronauts; }
	void setFuel(int fuel) { this->n_fuel = fuel; }
	int getFuel(void) { return this->n_fuel; }
	void setRocks(int rock) { this->n_rocks = rock; }
	int getRocks(void) { return this->n_rocks; }
	void setShowInventory(bool value) { this->showInventory = value; }
	bool isShowInventory(void) { return this->showInventory; }

	void update(float dt);
	bool isColliding(const Entity& other);
	void render(sf::RenderWindow& window);
};

