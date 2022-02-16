#include "ParticleSystem.h"

#include <iostream>

ParticleSystem::ParticleSystem(int l, int p, sf::Vector2f r, float max, float min, int life, sf::Color c, float s)
{
	m_loops = l;
	m_particlesPerLoop = p;
	m_rootPosition = r;
	m_maximumAngle = max;
	m_minimumAngle = min;
	//sf::Color color = sf::Color::Green;

	//Generates our pool of particles
	//Gives each one a random velocity based on the angle limitations set
	for (int i = 0; i < (l * p) + 10; i++)
	{
		sf::Vector2f v = sf::Vector2f(1.0f, 0.0f);

		float angle = (float)(std::rand() % (int)(m_maximumAngle - m_minimumAngle) + m_minimumAngle);
		angle = angle * 3.14159265359f / 180.0f;
		float cosAngle = std::cos(angle);
		float sinAngle = std::sin(angle);
		float x = v.x * cosAngle - v.y * sinAngle;
		float y = v.x * sinAngle + v.y * cosAngle;
		m_particles.push_back(std::make_shared<Particle>(life, c, m_rootPosition, sf::Vector2f(x, y), s));
	}
}

void ParticleSystem::Update()
{
	if (m_isActive == false) {
		return;
	}

	//Activates new loops worth of particles
	if (m_currentLoop < m_loops) {
		for (size_t i = 0; i < m_particlesPerLoop; i++)
		{
			if (m_currentParticle >= m_particles.size()) {
				m_currentParticle = 0;
			}

			if (m_particles[m_currentParticle]->m_lifetime == 0) {
				m_particles[m_currentParticle]->m_lifetime = 255;
				m_particles[m_currentParticle]->m_position = m_rootPosition;

				m_activeParticles.push_back(m_particles[m_currentParticle]);
			}

			m_currentParticle++;
		}

		m_currentLoop++;
	}

	if (m_activeParticles.size() == 0) {
		return;
	}

	//std::cout << m_activeParticles.size() << std::endl;

	//Updates each particle that is currently active
	for (int i = 0; i < m_activeParticles.size(); i++) {
		if (m_activeParticles.size() == 0 || i >= m_activeParticles.size()) {
			break;
		}

		if (m_activeParticles[i]->m_lifetime > 0) {
			m_activeParticles[i]->Update();
		}
		else {
			m_activeParticles.erase(m_activeParticles.begin() + (size_t)i);
			i--;
		}
	}
}

void ParticleSystem::Render(sf::RenderWindow& w)
{
	if (m_isActive == false || m_activeParticles.size() == 0) {
		return;
	}

	//Renders each particle that is still alive
	for (size_t i = 0; i < m_activeParticles.size(); i++)
	{
		if (m_activeParticles[i]->m_lifetime > 0) {
			m_activeParticles[i]->Render(w);
		}
	}
}

void ParticleSystem::Reset()
{
	m_currentLoop = 0;
	m_currentParticle = 0;
	m_isActive = true;

	for (std::shared_ptr<Particle> p : m_activeParticles) {
		p->m_lifetime = 0;
	}

	m_activeParticles.clear();
}

void ParticleSystem::SetRootPosition(sf::Vector2f& r)
{
	m_rootPosition = r;
}
