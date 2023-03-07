#include "Camera.hpp"
#include <iostream>

Camera::Camera(sf::Vector2i windowSize)
{
	playerView.setSize(sf::Vector2f(windowSize.x, windowSize.y));

	if (windowSize.x <= 1280 && windowSize.y <= 720)
		playerView.zoom(1.4);
	else if (windowSize.x <= 1366 && windowSize.y <= 768)
		playerView.zoom(1.25);

}

void Camera::setViewSpreads(LevelMaker& level_maker)
{
	//need to be called when a level is loaded
	width_spread = level_maker.get_LevelWidthSpread();
	height_spread = level_maker.get_LevelHeightSpread();
}

void Camera::update(sf::Vector2f playerPos, sf::RenderWindow& window, float dt)
{
	//level based view clampping
	sf::Vector2f newViewCenter = playerPos;
	playerView.setCenter(newViewCenter);
	float view_left = playerView.getCenter().x - playerView.getSize().x / 2;
	float view_right = playerView.getCenter().x + playerView.getSize().x / 2;
	float view_up = playerView.getCenter().y - playerView.getSize().y / 2;
	float view_down = playerView.getCenter().y + playerView.getSize().y / 2;

	if (view_left < width_spread.x)
		newViewCenter.x = width_spread.x + playerView.getSize().x / 2;
	if (view_right > width_spread.y) 
		newViewCenter.x = width_spread.y - playerView.getSize().x / 2;
	if (view_up < height_spread.x)
		newViewCenter.y = height_spread.x + playerView.getSize().y / 2;
	if (view_down > height_spread.y) 
		newViewCenter.y = height_spread.y - playerView.getSize().y / 2;

	playerView.setCenter(newViewCenter);

	/*if (triggerShake)
		cameraShake(dt);*/

	window.setView(playerView);
}

void Camera::cameraShake(float dt)
{
	shakeTimer += dt;
	if (shakeTimer >= shakeTime) {
		shakeTimer = 0;
		triggerShake = false;
		return;
	}

	float offset = 5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (10 - 5)));
	float direction = rand() % 2;
	float newCenterX = playerView.getCenter().x + ((direction == 0) ? offset : -offset);
	float newCenterY = playerView.getCenter().y + ((direction == 0) ? offset : -offset);
	playerView.setCenter(newCenterX, newCenterY);

}
