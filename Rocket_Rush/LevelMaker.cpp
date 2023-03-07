#include "LevelMaker.hpp"
#include <iostream>

LevelMaker::LevelMaker() = default;

void LevelMaker::spawn(void)
{
	sf::Vector2f windowSize = sf::Vector2f(1920, 1080);
	sf::Sprite s;
	Planet* p = new Planet(sf::Vector2f(500, 500), 100, s);
	planets.push_back(std::shared_ptr<Planet>(p));
}

void LevelMaker::update(const Entity& rocket)
{
	for (auto it = planets.begin(); it != planets.end(); it++) {
		Planet* p = it->get();
		if (p->isColliding(rocket)) {
			p->m_circle.setFillColor(sf::Color::Yellow);
		}
		else
			p->m_circle.setFillColor(sf::Color::White);
	}
}

void LevelMaker::render(sf::RenderWindow& window)
{
	for (auto& p : planets)
		p->render(window);
}
