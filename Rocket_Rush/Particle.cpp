#include "Particle.hpp"

Particle::Particle() = default;

Particle::Particle(const sf::Vector2f& size, const sf::Sprite& particleSprite, const sf::Color& color, const sf::Vector2f& pos, const float& dissolveTime)
{
	this->m_particle_size = size;
	this->m_particle_color = color;
	this->m_pos = pos;
	this->m_dissolveTime = dissolveTime;
	this->m_sprite = particleSprite;

	this->m_sprite.setOrigin(this->m_sprite.getGlobalBounds().width / 2, this->m_sprite.getGlobalBounds().height / 2);
	this->m_sprite.setScale(m_particle_size.x / 48, m_particle_size.y / 48);
	this->m_sprite.setPosition(m_pos);
}

void Particle::update(float dt, const float& angle, const float& speed)
{
	this->m_sprite.move(std::cos(angle) * dt * speed, 0);
	this->m_sprite.move(0, std::sin(angle) * dt * speed);
	
	this->m_pos = this->m_sprite.getPosition();
	float rotation_angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.1));
	this->m_sprite.rotate(rotation_angle);

	m_dissolveTimer += dt;
	if (m_dissolveTimer > m_dissolveTime) {
		m_dissolveTimer = 0;
		this->m_particle_color = sf::Color(this->m_particle_color.r, this->m_particle_color.g,
			this->m_particle_color.b, this->m_particle_color.a - dt);
		this->m_sprite.setColor(this->m_particle_color);
		if (this->m_particle_color.a <= 0)
			this->m_dissolved = true;
	}

}

void Particle::renderParticle(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
