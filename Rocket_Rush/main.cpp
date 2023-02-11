#include <iostream>
//#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"
#include "Rocket.hpp"

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Testing", sf::Style::Close);
	sf::Vector2f mousePos;
	sf::Clock clk;
	sf::Time tme;
	float dt;
	float generationTimer = 0;

	ParticleSystem* p_system = new ParticleSystem();
	Rocket* player = new Rocket();

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
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					//p_system->generate(mousePos);
					break;

			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();
				break;

			default:
				break;
			}
		}

		//////////////////////
		mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		//particle generation
		generationTimer += dt;
		if (generationTimer > 0.05f) {
			generationTimer = 0;
			if (player->getSpeed() != 0)
				p_system->generate(player->getPlayerEndPosition());
			//p_system->generate(sf::Vector2f(window.getSize().x / 2, window.getSize().y + 10));
		}

		player->update(dt);

		p_system->update(dt, player->getPlayerEndPosition());

		/////////////////////
		window.clear();

		p_system->render(window);
		player->render(window);

		window.display();
	}
}