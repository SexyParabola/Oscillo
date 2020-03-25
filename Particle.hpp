#pragma once
#include <SFML/Graphics.hpp>

class Particle {
private:
public:
	sf::Vector2f vel;
	sf::Vector2f acc;
	sf::CircleShape cir;
	double mass = 1;
	Particle(sf::Vector2f P) { cir.setPosition( P ); }
	void tick() {
		cir.setPosition( cir.getPosition().x + vel.x, cir.getPosition().y + vel.y );
		vel.x += acc.x;
		vel.y += acc.y;
		acc.x = 0;
		acc.y = 0;
	}
	void draw(sf::RenderWindow &window) {
		window.draw(cir);
	}
};