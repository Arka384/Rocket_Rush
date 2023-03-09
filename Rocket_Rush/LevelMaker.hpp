#pragma once
#include "Planet.hpp"
#include "ParticleSystem.hpp"
#include <list>

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
	
	std::list<sf::Sprite> levelSprites;
	std::pair<int, int> level_1 = std::make_pair<int, int>(3, 3);
	std::pair<int, int> currentLevelMaxMin = std::make_pair<int, int>(-level_1.first / 2, level_1.second / 2);

	sf::Vector2f level_width_spread;
	sf::Vector2f level_height_spread;
	sf::Vector2i windowSize;

	int maxPlanets = 5;
	
	bool collided = false;
	bool showPlanetInventory = false;

public:
	std::list<std::shared_ptr<Planet>> planets;

	LevelMaker(sf::Vector2i windowSize);
	std::pair<int, int> getCurrLevelSize() { return currentLevelMaxMin; }
	sf::Vector2f getBgSpriteSize() {
		return sf::Vector2f(backgroundSprite.getGlobalBounds().width,
			backgroundSprite.getGlobalBounds().height);
	}
	sf::Vector2f get_LevelWidthSpread() { return level_width_spread; }
	sf::Vector2f get_LevelHeightSpread() { return level_height_spread; }

	void loadLevel();
	void spawn(void);
	void update(float dt, const Entity& rocket);
	void render(sf::RenderWindow& window);

};

