#pragma once
#include <SFML/Graphics.hpp>

class Particle {
private:
public:
	sf::Vector2f vel;
	sf::Vector2f acc;
	sf::CircleShape cir;
	double mass = 1.0f;
	Particle(sf::Vector2f P) { cir.setPosition( P ); }
	void tick() {

        // This here is the "BUG".. 
		cir.setPosition( cir.getPosition().x + vel.x, cir.getPosition().y + vel.y );
        // Swap these line of code to "fix"
		vel.x += acc.x;
		vel.y += acc.y;

		acc.x = 0;
		acc.y = 0;
	}
	void draw(sf::RenderWindow &window) {
		window.draw(cir);
	}

};