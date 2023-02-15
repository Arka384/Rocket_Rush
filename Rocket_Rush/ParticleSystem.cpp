#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem() = default;

ParticleSystem::ParticleSystem(const int& maxNumber, const int& maxScatter, const std::pair<int, int>& size, const float& dissolveTime, const sf::Color& color)
{
	this->size = size;
	this->m_color = color;
	this->n_particles = maxNumber;
	this->max_scatter = maxScatter;
	this->dissolveTime = dissolveTime;

	this->glowTexture.loadFromFile("Assets/Particles/my_glow.png");
	this->glowSprite.setTexture(this->glowTexture);
	this->glowSprite.setColor(this->m_color);
}

void ParticleSystem::emit(const sf::Vector2f& position)
{
	for (int i = 0; i < n_particles; i++) {
		float size = rand() % this->size.second + this->size.first;
		float pos_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / this->max_scatter)); //scattering
		int r_x = rand() % 2;
		int r_y = rand() % 2;
		float pos_offset_x = r_x ? -pos_offset : pos_offset;
		float pos_offset_y = r_y ? -pos_offset : pos_offset;
		sf::Vector2f pos = sf::Vector2f(position.x + pos_offset_x, position.y + pos_offset_y);
		Particle* particle = new Particle(sf::Vector2f(size, size), this->glowSprite, this->m_color, pos, this->dissolveTime);
		particles.push_back(std::shared_ptr<Particle>(particle));
	}
}

void ParticleSystem::update(float dt, const sf::Vector2f& targetPosition)
{
	for (auto it = particles.begin(); it != particles.end(); it++) {
		Particle* current = it->get();
		float dx = targetPosition.x - current->getmPos().x;
		float dy = targetPosition.y - current->getmPos().y;
		float angle = std::atan2(dy, dx);
		float speed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100));
		current->update(dt, angle, speed);
		if (current->isDissolved())
			it = particles.erase(it);
	}
}

void ParticleSystem::render(sf::RenderWindow& window)
{
	for (auto p : particles) {
		p->renderParticle(window);
	}
}
