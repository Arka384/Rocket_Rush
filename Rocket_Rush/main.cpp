#include "ParticleSystem.hpp"
//#include "Rocket.hpp" // => level_maker
#include "Ui.hpp"	// => rocket
//#include "Weapon.hpp"
#include "Camera.hpp" // => level_maker

int main()
{
	srand(time(NULL));
	sf::Vector2i windowSize = sf::Vector2i(1920, 1080);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Testing", sf::Style::Fullscreen);
	window.setFramerateLimit(300);
	sf::Vector2f mousePos;
	bool mousePressed = false;
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

	LevelMaker* l_maker = new LevelMaker(windowSize);
	Rocket* player = new Rocket(windowSize);
	//Weapon* weapon = new Weapon(windowSize);
	Camera* cam = new Camera(windowSize);
	Ui* ui = new Ui();

	l_maker->loadLevel();
	l_maker->spawn();
	cam->setViewSpreads(*l_maker);

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
				mousePressed = true;
				break;
			case sf::Event::MouseButtonReleased:
				mousePressed = false;
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
		sf::Vector2i tempMousePos = sf::Mouse::getPosition(window);
		mousePos = window.mapPixelToCoords(tempMousePos);

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

		player->update(dt, *l_maker);
		//weapon->update(dt);
		l_maker->update(dt, *player);
		cam->update(player->getPosition(), window, dt);
		ui->update(dt, mousePos, mousePressed, *l_maker, *player);

		smoke->update(dt, player->getParticleTargetPos());
		flame->update(dt, player->getParticleTargetPos());

		/////////////////////
		window.clear();

		l_maker->render(window);
		smoke->render(window);
		flame->render(window);


		player->render(window);
		//weapon->draw(window);
		ui->render(window);

		window.display();
	}
}