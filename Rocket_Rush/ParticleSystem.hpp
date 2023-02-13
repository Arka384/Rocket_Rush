#pragma once
#include "Particle.hpp"
#include <list>


class ParticleSystem
{
private:
	std::list<std::shared_ptr<Particle>> particles;
	int n_particles = 10;	//generates 10 particles
	std::pair<int, int> size;
	sf::Color m_color;
	float max_scatter = 0.f;
	float dissolveTime = 0.f;

	sf::Texture glowTexture;
	sf::Sprite glowSprite;

public:
	ParticleSystem();
	ParticleSystem(const int& maxNumber, const int& maxScatter, const std::pair<int, int>& size, const float& dissolveTime, const sf::Color& color);
	void emit(const sf::Vector2f& position);
	void update(float dt, const sf::Vector2f& targetPosition);
	void render(sf::RenderWindow& window);
};

