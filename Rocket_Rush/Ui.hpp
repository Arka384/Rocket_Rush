#include "Rocket.hpp"

class Ui {
private:
	sf::Texture planet_inventory_tex;
	sf::Sprite planet_inventory;
	sf::Texture E_button_tex;
	sf::Sprite E_button;
	//planet inventory button sprites and textures
	sf::Texture addButtonTex;
	sf::Sprite addButton;
	sf::Texture removeButtonTex;
	sf::Sprite removeButton;
	sf::Texture collectButtonTex;
	sf::Sprite collectButton_1, collectButton_2;
	sf::Texture closeButtonTex;
	sf::Sprite closeButton;
	//texts
	sf::Text austro_text, fuel_text, rocks_text;



	bool show_planet_inventory = false;

public:
	Ui();
	void update(float dt, sf::Vector2f mousePos, LevelMaker& levelMaker, const Rocket& rocket);
	bool isHot(sf::Vector2f mousePos, sf::Vector2f uiElemPos, sf::FloatRect uiElemSize);
	void render(sf::RenderWindow& window);
};