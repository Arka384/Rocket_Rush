#pragma once
#include "Planet.hpp"
#include <list>

class LevelMaker
{
private:
	int maxPlanets = 5;

public:
	std::list<std::shared_ptr<Planet>> planets;

	LevelMaker();
	void spawn(void);
	void update(const Entity& rocket);
	void render(sf::RenderWindow& window);

};

