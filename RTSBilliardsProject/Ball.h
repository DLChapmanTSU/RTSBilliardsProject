#pragma once
#include <SFML/Graphics.hpp>

class Ball {
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Color m_colour;
	float m_radius{ 10 };
	unsigned int m_index;
public:
	Ball(sf::Vector2f p, sf::Vector2f v, sf::Color c, unsigned int i);
	void SetVelocity(sf::Vector2f v);
	sf::Vector2f& GetVelocity() { return m_velocity; };
	sf::Vector2f& GetPosition() { return m_position; };
	float GetRadius() { return m_radius; };
	unsigned int GetIndex() { return m_index; };
	sf::Color& GetColor() { return m_colour; };
	void SetColor(sf::Color c);
	void Update();
	void Render(sf::RenderWindow& w);
	void SetPosition(sf::Vector2f p);
	float GetRawVLength();
};