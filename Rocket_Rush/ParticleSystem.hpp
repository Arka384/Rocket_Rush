#pragma once
#include "Particle.hpp"
#include <list>


class ParticleSystem
{
private:
	std::list<std::shared_ptr<Particle>> particles;
	int n_particles = 10;	//generates 10 particles

public:
	ParticleSystem();
	void generate(const sf::Vector2f& position);
	void update(float dt, const sf::Vector2f& targetPosition);
	void render(sf::RenderWindow& window);
};

