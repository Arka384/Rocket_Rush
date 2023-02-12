#pragma once
#include <SFML/Graphics.hpp>

class Particle
{
private:
	sf::RectangleShape m_particle;
	sf::Vector2f m_particle_size;
	sf::Color m_particle_color;
	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;
	float m_dissolveTimer = 0.f;
	float m_dissolveTime = 0.0f;
	bool m_dissolved = false;

public:
	Particle();
	Particle(const sf::Vector2f& size, const sf::Color& color, const sf::Vector2f& pos, const float& dissolveTime);

	inline void setVelocity(sf::Vector2f vel) { this->m_velocity = vel; }
	inline sf::Vector2f getVelocity() { return this->m_velocity; }
	inline void setmPos(sf::Vector2f pos) { this->m_pos = pos; }
	inline sf::Vector2f getmPos() { return this->m_pos; }
	inline bool isDissolved() { return m_dissolved; }

	void update(float dt, const float& angle, const float& speed);
	void renderParticle(sf::RenderWindow& window);
};

