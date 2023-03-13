#pragma once
#include "Planet.hpp"
#include "ParticleSystem.hpp"
#include <iostream>
#include <list>
#include <sstream>

class LevelMaker
{
private:
	//sprites and txtures
	sf::Texture backgroundTex;
	sf::Sprite backgroundSprite;
	sf::Texture itemsTex;
	sf::Sprite items;

	//texts and fronts
	sf::Font font;
	sf::Text austro_text, fuel_text, rocks_text;

	//ParticleSystem* collision_particles;
	Planet* activePlanet = nullptr;
	std::list<sf::Sprite> levelSprites;
	std::pair<int, int> level_1 = std::make_pair<int, int>(3, 3);
	std::pair<int, int> currentLevelMaxMin = std::make_pair<int, int>(-level_1.first / 2, level_1.second / 2);

	sf::Vector2f level_width_spread;
	sf::Vector2f level_height_spread;
	sf::Vector2i windowSize;
	sf::Vector2f detailed_inventory_pos;

	int maxPlanets = 5;
	
	bool collided = false;
	bool showPlanetInventory = false;
	bool show_Detailed_PlanetInventory = false;

public:
	std::list<std::shared_ptr<Planet>> planets;

	LevelMaker(sf::Vector2i windowSize);
	Planet* getActivePlanet() { return this->activePlanet; }
	std::pair<int, int> getCurrLevelSize() { return currentLevelMaxMin; }
	sf::Vector2f getBgSpriteSize() {
		return sf::Vector2f(backgroundSprite.getGlobalBounds().width,
			backgroundSprite.getGlobalBounds().height);
	}
	sf::Vector2f get_LevelWidthSpread() { return level_width_spread; }
	sf::Vector2f get_LevelHeightSpread() { return level_height_spread; }
	sf::Vector2f get_Detailed_planet_inventory_pos() { return detailed_inventory_pos; }
	sf::Text get_austro_text() { return austro_text; }
	sf::Text get_fuel_text() { return fuel_text; }
	sf::Text get_rocks_text() { return rocks_text; }
	bool is_show_Detailed_PlanetInventory() { return show_Detailed_PlanetInventory; }
	void set_show_Detailed_PlanetInventory(bool val) { this->show_Detailed_PlanetInventory = val; }

	void loadLevel();
	void spawn(void);
	void update(float dt, const Entity& rocket);
	void render(sf::RenderWindow& window);

};

