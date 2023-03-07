#pragma once
#include "LevelMaker.hpp"

class Camera
{
private:
	int maxPlayerOffset = 300;
	float moveSpeed = 400.f;
	float shakeTime = 0.1f, shakeTimer = 0.f;

	sf::Vector2f width_spread;
	sf::Vector2f height_spread;

public:
	sf::View playerView;
	bool triggerShake = false;

	Camera(sf::Vector2i windowSize);
	void setViewSpreads(LevelMaker& level_maker);
	void update(sf::Vector2f playerPos, sf::RenderWindow& window, float dt);
	void cameraShake(float dt);
};
