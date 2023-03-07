#pragma once
#include "Planet.hpp"
#include <list>

class LevelMaker
{
private:
	sf::Texture backgroundTex;
	sf::Sprite backgroundSprite;
	
	std::list<sf::Sprite> levelSprites;
	std::pair<int, int> level_1 = std::make_pair<int, int>(3, 3);
	std::pair<int, int> currentLevelMaxMin = std::make_pair<int, int>(-level_1.first / 2, level_1.second / 2);

	sf::Vector2f level_width_spread;
	sf::Vector2f level_height_spread;

	int maxPlanets = 5;

public:
	std::list<std::shared_ptr<Planet>> planets;

	LevelMaker();
	inline std::pair<int, int> getCurrLevelSize() { return currentLevelMaxMin; }
	inline sf::Vector2f getBgSpriteSize() {
		return sf::Vector2f(backgroundSprite.getGlobalBounds().width,
			backgroundSprite.getGlobalBounds().height);
	}
	inline sf::Vector2f get_LevelWidthSpread() { return level_width_spread; }
	inline sf::Vector2f get_LevelHeightSpread() { return level_height_spread; }

	void loadLevel();
	void spawn(void);
	void update(const Entity& rocket);
	void render(sf::RenderWindow& window);

};

