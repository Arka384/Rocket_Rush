#include "ParticleSystem.hpp"
#include "Rocket.hpp"
#include "Weapon.hpp"

int main()
{
	srand(time(NULL));
	sf::Vector2i windowSize = sf::Vector2i(1920, 1080);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Testing", sf::Style::Fullscreen);
	sf::Vector2f mousePos;
	sf::Clock clk;
	sf::Time tme;
	float dt;
	float flame_generationTimer = 0;
	float flame_generationTime = 0.01f;
	float smoke_generationTimer = 0;
	float smoke_generationTime = 0.25f;
	bool w_down = false;

	ParticleSystem* smoke = new ParticleSystem(1, 25, std::pair<int, int>(4, 10), 0.005f, sf::Color(255, 255, 255, 255));
	ParticleSystem* flame = new ParticleSystem(1, 15, std::pair<int, int>(5, 10), 0.001f, sf::Color(255,246,0,255));

	Rocket* player = new Rocket(windowSize);
	Weapon* weapon = new Weapon(windowSize);

	while (window.isOpen()) {
		tme = clk.restart();
		dt = tme.asSeconds();

		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				return 0;
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					weapon->fire(player->getmPos(), player->getFireAngle());
				}
				break;

			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					w_down = true;
				break;

			case sf::Event::KeyReleased:
				if (e.key.code == sf::Keyboard::W)
					w_down = false;
				break;

			default:
				break;
			}
		}

		//////////////////////
		mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		//particle generation
		//smoke particles
		smoke_generationTimer += dt;
		if (smoke_generationTimer > smoke_generationTime) {
			smoke_generationTimer = 0;
			smoke_generationTime = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.25));
			if (player->getSpeed() != 0)
				smoke->emit(player->getPlayerEndPosition());
		}
		//flame particles
		flame_generationTimer += dt;
		if (flame_generationTimer > flame_generationTime) {
			flame_generationTimer = 0;
			if (w_down)
				flame->emit(player->getPlayerEndPosition());
		}

		player->update(dt);
		weapon->update(dt);

		smoke->update(dt, player->getParticleTargetPos());
		flame->update(dt, player->getParticleTargetPos());

		/////////////////////
		window.clear();

		smoke->render(window);
		flame->render(window);

		player->render(window);
		
		weapon->draw(window);

		window.display();
	}
}