#include "Particle.h"

Particle::Particle(int l, sf::Color c, sf::Vector2f p, sf::Vector2f v, float s)
{
	m_lifeLossRate = l;
	m_color = c;
	m_position = p;
	m_velocity = v;
	m_speed = s;
}

void Particle::Update()
{
	//Ticks the life of the particle down each frame
	//Sets the current alpha value to the current lifetime of the particle
	m_lifetime -= m_lifeLossRate;

	if (m_lifetime < 0) {
		m_lifetime = 0;
	}

	m_color.a = m_lifetime;
	m_position += m_velocity * m_speed;
}

void Particle::Render(sf::RenderWindow& w)
{
	sf::RectangleShape rect(sf::Vector2f(3.0f, 3.0f));
	rect.setOrigin(sf::Vector2f(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2));
	rect.setPosition(m_position);
	rect.setFillColor(m_color);

	w.draw(rect);
}
