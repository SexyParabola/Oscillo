// Oscillo Project Started 3 / 13 / 2020

#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include <math.h>
#include <vector>

sf::Color getRainbow(double theta) {
	sf::Color color;
	color.r = 128 * (sin(theta) + 1);
	color.g = 128 * (sin(theta + 2.0943951) + 1);
	color.b = 128 * (sin(theta + 4.1887902) + 1);
	return color;
}

int main()
{
	sf::Clock clock;
	sf::Time timer;
    sf::Vector2i windowSize = sf::Vector2i(1200, 800);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Oscillo");
	sf::Event event;

	std::vector<Particle> particles;

	particles.push_back( Particle(sf::Vector2f(windowSize.x * (1.0/2.0), windowSize.y * (1.0/2.0) + 10)) );
	particles[0].cir.setRadius(5);
	particles[0].cir.setFillColor(sf::Color::Red);
    particles[0].cir.setOutlineThickness(2);
	//particles[0].cir.setPointCount(3);
	particles[0].vel.x = 4;
	//particles[0].vel.y = -0.1;

	particles.push_back( Particle(sf::Vector2f(windowSize.x * (1.0/2.0), windowSize.y * (1.0/2.0) - 10)) );
	particles[1].cir.setRadius(5);
	particles[1].cir.setFillColor(sf::Color::Blue);
	//particles[1].cir.setPointCount(3);
	particles[1].vel.x = -4;
	//particles[1].vel.y = 0.1;

	// particles.push_back( Particle(sf::Vector2f(windowSize.x * (1.0/2.0), windowSize.y * (1.0/2.0) + 0)) );
	// particles[2].cir.setRadius(3);
	// particles[2].cir.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				window.close();
			}
			if (event.type == sf::Event::KeyReleased) {}
		}
		if ((clock.getElapsedTime().asMilliseconds() - timer.asMilliseconds()) > 16.6) {
			timer = clock.getElapsedTime();

			sf::Vector2f delta;
			sf::Vector2f acc;
			double force;

			for (unsigned int i = 0; i < particles.size(); i++) {
				for (unsigned int j = 0; j < particles.size(); j++) {
					if (i != j) {
						delta = sf::Vector2f(
							particles[j].cir.getPosition().x - particles[i].cir.getPosition().x,
							particles[j].cir.getPosition().y - particles[i].cir.getPosition().y
						);
                        double mag = sqrt(delta.x * delta.x + delta.y * delta.y);
						force = 0.1;
						acc = sf::Vector2f((delta.x / mag) * force, (delta.y / mag) * force);
						particles[i].acc += acc;
					}
				}
			}

			for (unsigned int i = 0; i < 2; i++) { // Ticks and colors particles
				particles[i].tick();
				double distance = sqrt(
					pow((windowSize.x * 0.5) - particles[i].cir.getPosition().x, 2) +
					pow((windowSize.y * 0.5) - particles[i].cir.getPosition().y, 2)
				); // (i + 1) *
				double newScale = 0.05 * distance * (1 + i);
                particles[i].cir.setRadius(newScale);
				particles[i].cir.setOrigin(sf::Vector2f(newScale, newScale));
			}
		}

		//window.clear(sf::Color::Black);

		for (unsigned int i = 0; i < particles.size(); i++) {
			particles[i].cir.setFillColor(getRainbow(i + clock.getElapsedTime().asSeconds()));
			particles[i].draw(window);
		}
		window.display();
	}
}
