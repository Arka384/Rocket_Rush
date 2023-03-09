#include "LevelMaker.hpp"
#include <iostream>

LevelMaker::LevelMaker(sf::Vector2i windowSize) {
	this->windowSize = windowSize;
	if (!backgroundTex.loadFromFile("Assets/Background/dark_space.png"))
		exit(1);
	backgroundSprite.setTexture(backgroundTex);
	backgroundSprite.setPosition(0, 0);

	if (!itemsTex.loadFromFile("Assets/Levels/items.png"))
		exit(1);
	items.setTexture(itemsTex);

	uint32_t fontSize = 20;
	font.loadFromFile("Assets/Fonts/Spaceline.otf");
	austro_text.setFont(font);
	austro_text.setCharacterSize(fontSize);
	fuel_text.setFont(font);
	fuel_text.setCharacterSize(fontSize);
	rocks_text.setFont(font);
	rocks_text.setCharacterSize(fontSize);

	//collision_particles = new ParticleSystem(1, 25, std::pair<int, int>(4, 10), 0.005f, sf::Color(255, 0, 0, 255));
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
	Planet* p2 = new Planet(sf::Vector2f(-1000, 900), 100, s);
	planets.push_back(std::shared_ptr<Planet>(p2));
}

void LevelMaker::update(float dt, const Entity& rocket)
{
	bool b_flag = false;
	for (auto it = planets.begin(); it != planets.end(); it++) {
		Planet* p = it->get();
		//if (p->isColliding(rocket) && !collided) {
		if (p->isColliding(rocket)) {
			//collided = true;
			//collision_particles->emit(rocket.getPosition());
			p->m_circle.setFillColor(sf::Color::Yellow);
		}
		else {
			//collided = false;
			p->m_circle.setFillColor(sf::Color::White);
		}

		//updating the planet inventroy
		float dx = rocket.getPosition().x - p->m_circle.getPosition().x;
		float dy = rocket.getPosition().y - p->m_circle.getPosition().y;
		float dist = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
		if (dist < (p->m_circle.getRadius() + 130.f)) {
			float items_pos_x = p->m_circle.getPosition().x - items.getGlobalBounds().width / 2;
			float items_pos_y = p->m_circle.getPosition().y - items.getGlobalBounds().height * 1.5;
			items.setPosition(sf::Vector2f(items_pos_x, items_pos_y));
			p->setShowInventory(true);
			b_flag = true;
		}
		else
			p->setShowInventory(true);
	}

	if (b_flag)	showPlanetInventory = true;
	else showPlanetInventory = false;

	//collision_particles->update(dt, sf::Vector2f(rocket.getPosition().x, 0));
	
}

void LevelMaker::render(sf::RenderWindow& window)
{
	for (auto sprites : levelSprites)
		window.draw(sprites);

	for (auto& p : planets)
		p->render(window);

	//collision_particles->render(window);
	if(showPlanetInventory)
		window.draw(items);
}
