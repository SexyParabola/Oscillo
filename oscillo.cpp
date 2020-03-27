// Oscillo Project Started 3 / 13 / 2020

#include <SFML/Graphics.hpp>
#include "oscillo.hpp"
#include "Particle.hpp"
#include <math.h>
#include <vector>

sf::Color OscilloProject::getRainbow(double theta) {
	sf::Color color;
	color.r = 128 * (sin(theta) + 1);
	color.g = 128 * (sin(theta + 2.0943951) + 1);
	color.b = 128 * (sin(theta + 4.1887902) + 1);
	return color;
}

void OscilloProject::exec()
{
	sf::Clock clock;
	sf::Time timer;
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Oscillo");
	sf::Event event;

	std::vector<Particle> particles;

	particles.push_back( Particle(sf::Vector2f(windowSize.x * (1.0/2.0), windowSize.y * (1.0/2.0) + 0.1)) );
	particles[0].cir.setRadius(5);
	particles[0].cir.setFillColor(sf::Color::Red);
	//particles[0].cir.setPointCount(3);
	particles[0].vel.x = 0.01;
	//particles[0].vel.y = -0.1;

	particles.push_back( Particle(sf::Vector2f(windowSize.x * (1.0/2.0), windowSize.y * (1.0/2.0) - 0.1)) );
	particles[1].cir.setRadius(5);
	particles[1].cir.setFillColor(sf::Color::Blue);
	//particles[1].cir.setPointCount(3);
	particles[1].vel.x = -0.01;
	//particles[1].vel.y = 0.1;

	// particles.push_back( Particle(sf::Vector2f(windowSize.x * (1.0/2.0), windowSize.y * (1.0/2.0) + 0)) );
	// particles[2].cir.setRadius(3);
	// particles[2].cir.setFillColor(sf::Color::Green);

	//double k = 1000.0;

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
			// sf::Vector2f unitDelta;
			// double distance;
			double force;
			sf::Vector2f acc;
			// std::vector<sf::Vector2f> currentPos;
			// currentPos.clear();
			// for (unsigned int i = 0; i < particles.size(); i++) {
			// 	currentPos.push_back(particles[i].cir.getPosition());
			// }

			for (unsigned int i = 0; i < particles.size(); i++) {
				for (unsigned int j = 0; j < particles.size(); j++) {
					if (i != j) {
						delta = sf::Vector2f(
							particles[j].cir.getPosition().x - particles[i].cir.getPosition().x,
							particles[j].cir.getPosition().y - particles[i].cir.getPosition().y
						);
						// distance = sqrt((delta.x * delta.x) + (delta.y * delta.y));
						// unitDelta = sf::Vector2f(delta.x / distance, delta.y / distance);
						// force = k / (distance * distance);
						force = 0.01;
						acc = sf::Vector2f(delta.x * force, delta.y * force);
						particles[i].acc += acc;
						//std::cout << i << ", " << j << ": " << force << std::endl;
					}
				}
			}
			//std::cout << std::endl;
			for (unsigned int i = 0; i < 2; i++) {
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
