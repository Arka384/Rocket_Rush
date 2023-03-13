#include "Ui.hpp"

Ui::Ui()
{
	planet_inventory_tex.loadFromFile("Assets/Ui/Planet_inventory.png");
	planet_inventory.setTexture(planet_inventory_tex);

	addButtonTex.loadFromFile("Assets/Ui/add.png");
	removeButtonTex.loadFromFile("Assets/Ui/remove.png");
	collectButtonTex.loadFromFile("Assets/Ui/collect.png");
	closeButtonTex.loadFromFile("Assets/Ui/close.png");

	addButton.setTexture(addButtonTex);
	removeButton.setTexture(removeButtonTex);
	collectButton_1.setTexture(collectButtonTex);
	collectButton_2.setTexture(collectButtonTex);
	closeButton.setTexture(closeButtonTex);
}

void Ui::update(float dt, sf::Vector2f mousePos, LevelMaker& levelMaker, const Rocket& rocket)
{
	show_planet_inventory = levelMaker.is_show_Detailed_PlanetInventory();
	
	if (show_planet_inventory) {	//update only when it is on
		sf::Vector2f planetInventoryPos = levelMaker.get_Detailed_planet_inventory_pos();
		planet_inventory.setPosition(planetInventoryPos);
		//update planet_inventory buttons
		addButton.setPosition(planetInventoryPos.x + 255, planetInventoryPos.y + 138);
		addButton.setScale(1, 1);
		removeButton.setPosition(planetInventoryPos.x + 255, planetInventoryPos.y + 200);
		removeButton.setScale(1, 1);
		collectButton_1.setPosition(planetInventoryPos.x + 255, planetInventoryPos.y + 322);
		collectButton_1.setScale(1, 1);
		collectButton_2.setPosition(planetInventoryPos.x + 255, planetInventoryPos.y + 462);
		collectButton_2.setScale(1, 1);
		closeButton.setPosition(planetInventoryPos.x + 132, planetInventoryPos.y + 552);
		closeButton.setScale(1, 1);
		//update texts
		this->austro_text = levelMaker.get_austro_text();
		this->fuel_text = levelMaker.get_fuel_text();
		this->rocks_text = levelMaker.get_rocks_text();
		austro_text.setScale(1.5, 1.5);
		austro_text.setPosition(planetInventoryPos.x + 155, planetInventoryPos.y + 170);
		fuel_text.setScale(1.5, 1.5);
		fuel_text.setPosition(planetInventoryPos.x + 155, planetInventoryPos.y + 325);
		rocks_text.setScale(1.5, 1.5);
		rocks_text.setPosition(planetInventoryPos.x + 155, planetInventoryPos.y + 464);

		//planet_inventory buttons and mouse interactions
		if (isHot(mousePos, addButton.getPosition(), addButton.getGlobalBounds())) {
			addButton.setScale(1.1, 1.1);
			addButton.setPosition(addButton.getPosition().x - 5, addButton.getPosition().y - 3);
		}
		else if (isHot(mousePos, removeButton.getPosition(), removeButton.getGlobalBounds())) {
			removeButton.setScale(1.1, 1.1);
			removeButton.setPosition(removeButton.getPosition().x - 5, removeButton.getPosition().y - 3);
		}
		else if (isHot(mousePos, collectButton_1.getPosition(), collectButton_1.getGlobalBounds())) {
			collectButton_1.setScale(1.1, 1.1);
			collectButton_1.setPosition(collectButton_1.getPosition().x - 5, collectButton_1.getPosition().y - 3);
		}
		else if (isHot(mousePos, collectButton_2.getPosition(), collectButton_2.getGlobalBounds())) {
			collectButton_2.setScale(1.1, 1.1);
			collectButton_2.setPosition(collectButton_2.getPosition().x - 5, collectButton_2.getPosition().y - 3);
		}
		else if (isHot(mousePos, closeButton.getPosition(), closeButton.getGlobalBounds())) {
			closeButton.setScale(1.1, 1.1);
			closeButton.setPosition(closeButton.getPosition().x - 5, closeButton.getPosition().y - 3);
		}
	}
	


}

bool Ui::isHot(sf::Vector2f mousePos, sf::Vector2f uiElemPos, sf::FloatRect uiElemSize)
{
	if (mousePos.x > uiElemPos.x && mousePos.x < uiElemPos.x + uiElemSize.width &&
		mousePos.y > uiElemPos.y && mousePos.y < uiElemPos.y + uiElemSize.height)
		return true;
	return false;
}

void Ui::render(sf::RenderWindow& window) 
{
	if (show_planet_inventory) {
		window.draw(planet_inventory);
		window.draw(addButton);
		window.draw(removeButton);
		window.draw(collectButton_1);
		window.draw(collectButton_2);
		window.draw(closeButton);
		window.draw(austro_text);
		window.draw(fuel_text);
		window.draw(rocks_text);
	}
		
}