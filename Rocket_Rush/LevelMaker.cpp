#include "LevelMaker.hpp"

LevelMaker::LevelMaker(sf::Vector2i windowSize) {
	this->windowSize = windowSize;
	if (!backgroundTex.loadFromFile("Assets/Background/dark_space.png"))
		exit(1);
	backgroundSprite.setTexture(backgroundTex);
	backgroundSprite.setPosition(0, 0);

	if (!itemsTex.loadFromFile("Assets/Ui/items.png"))
		exit(1);
	items.setTexture(itemsTex);

	uint32_t fontSize = 20;
	font.loadFromFile("Assets/Fonts/Gameplay.ttf");
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
	Planet* p2 = new Planet(sf::Vector2f(-1400, 900), 100, s);
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
			
			//normally detailed inventory will be on the left side
			if ((items_pos_x - 500) < level_width_spread.x)	//if goes beyond map
				detailed_inventory_pos.x = items_pos_x + items.getGlobalBounds().width * 1.3; //place on right side
			else detailed_inventory_pos.x = items_pos_x - 500;	//on the left side
			detailed_inventory_pos.y = items_pos_y;
			
			p->setShowInventory(true);
			activePlanet = p;
			b_flag = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !show_Detailed_PlanetInventory)
				show_Detailed_PlanetInventory = true;
		}
		else
			p->setShowInventory(false);
	}

	if (b_flag)	showPlanetInventory = true;
	else {
		showPlanetInventory = false;
		show_Detailed_PlanetInventory = false;
	}

	//updating inventory texts
	if (showPlanetInventory) {
		std::stringstream ss;
		ss << activePlanet->getAsutronauts();
		austro_text.setString(ss.str());
		austro_text.setPosition(items.getPosition().x + 54, items.getPosition().y + 174);
		ss.str("");
		ss << activePlanet->getFuel();
		fuel_text.setString(ss.str());
		fuel_text.setPosition(items.getPosition().x + 174, items.getPosition().y + 174);
		ss.str("");
		ss << activePlanet->getRocks();
		rocks_text.setString(ss.str());
		rocks_text.setPosition(items.getPosition().x + 280, items.getPosition().y + 174);
	}

	//collision_particles->update(dt, sf::Vector2f(rocket.getPosition().x, 0));
	
}

void LevelMaker::render(sf::RenderWindow& window)
{
	for (auto sprites : levelSprites)
		window.draw(sprites);

	for (auto& p : planets)
		p->render(window);

	//collision_particles->render(window);
	if (showPlanetInventory) {
		window.draw(items);
		window.draw(austro_text);
		window.draw(fuel_text);
		window.draw(rocks_text);
	}
		
}
