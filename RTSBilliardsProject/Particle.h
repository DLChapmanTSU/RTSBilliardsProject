#pragma once
#include <SFML/Graphics.hpp>

class Particle {
private:
	int m_lifetime{ 0 };
	int m_lifeLossRate{ 1 };
	sf::Color m_color;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_speed{ 1.0f };
public:
	Particle(int l, sf::Color c, sf::Vector2f p, sf::Vector2f v, float s);
	void Update();
	void Render(sf::RenderWindow& w);

	friend class ParticleSystem;
};