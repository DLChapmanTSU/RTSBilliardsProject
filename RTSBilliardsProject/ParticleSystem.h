#pragma once
#include <SFML/Graphics.hpp>

#include "Particle.h"

class ParticleSystem {
private:
	std::vector<std::shared_ptr<Particle>> m_particles;
	std::vector<std::shared_ptr<Particle>> m_activeParticles;
	int m_loops{ 1 };
	int m_currentLoop{ 0 };
	int m_particlesPerLoop{ 1 };
	size_t m_currentParticle{ 0 };
	float m_minimumAngle;
	float m_maximumAngle;
	sf::Vector2f m_rootPosition;
	bool m_isActive{ false };
public:
	ParticleSystem(int l, int p, sf::Vector2f r, float max, float min, int life, sf::Color c, float s);
	void Update();
	void Render(sf::RenderWindow& w);
	void Reset();
	void SetRootPosition(sf::Vector2f& r);
};