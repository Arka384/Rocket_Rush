#include "LevelMaker.hpp"
#include <iostream>

LevelMaker::LevelMaker() {
	if (!backgroundTex.loadFromFile("Assets/Background/dark_space.png"))
		exit(1);
	backgroundSprite.setTexture(backgroundTex);
	backgroundSprite.setPosition(0, 0);
}

void LevelMaker::loadLevel()
{
	sf::Vector2f bg_sp_size;
	bg_sp_size.x = backgroundSprite.getGlobalBounds().width;
	bg_sp_size.y = backgroundSprite.getGlobalBounds().height;
	
	for (int i = -level_1.first/2; i <= level_1.first/2; i++) {	//divide by 2 cause I want -1 to 1 for 3
		for (int j = -level_1.second/2; j <= level_1.second/2; j++) {
			backgroundSprite.setPosition(j * bg_sp_size.x, i * bg_sp_size.y);
			levelSprites.push_back(backgroundSprite);
		}
	}

	level_width_spread = sf::Vector2f(currentLevelMaxMin.first * backgroundSprite.getGlobalBounds().width,
		currentLevelMaxMin.second * backgroundSprite.getGlobalBounds().width + backgroundSprite.getGlobalBounds().width);
	level_height_spread = sf::Vector2f(currentLevelMaxMin.first * backgroundSprite.getGlobalBounds().height,
		currentLevelMaxMin.second * backgroundSprite.getGlobalBounds().height + backgroundSprite.getGlobalBounds().height);
}

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
	for (auto sprites : levelSprites)
		window.draw(sprites);

	for (auto& p : planets)
		p->render(window);
}
