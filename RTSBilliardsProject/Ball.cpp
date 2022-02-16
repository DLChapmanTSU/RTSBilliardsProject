#include "Ball.h"
#include <iostream>

Ball::Ball(sf::Vector2f p, sf::Vector2f v, sf::Color c, unsigned int i) {
	m_position = p;
	m_velocity = v;
	//m_velocity.y = -m_velocity.y;
	m_colour = c;
	m_index = i;
}

void Ball::SetVelocity(sf::Vector2f v) {
	m_velocity = v;
	//m_velocity.y = -m_velocity.y;
}

void Ball::SetColor(sf::Color c)
{
	m_colour = c;
}

void Ball::Update() {
	//Updates position
	//Then multiplies the velocity by a set value to simulate friction
	m_position += m_velocity;

	m_velocity *= 0.9991f;
}

void Ball::Render(sf::RenderWindow& w) {
	//Renders the ball as a circle on the screen
	sf::CircleShape circle(m_radius);
	circle.setPosition(m_position);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setFillColor(m_colour);

	w.draw(circle);
}

void Ball::SetPosition(sf::Vector2f p)
{
	m_position = p;
}

//Returns the magnitude of the velocity vector
float Ball::GetRawVLength()
{
	return std::sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));;
}