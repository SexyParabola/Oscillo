// Oscillo Project Started 3 / 13 / 2020

#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include <math.h>
#include <vector>
#include <fstream>
#include <string>

sf::Color getRainbow(double theta) {
	sf::Color color;
	color.r = 128 * (sin(theta) + 1);
	color.g = 128 * (sin(theta + 2.0943951) + 1);
	color.b = 128 * (sin(theta + 4.1887902) + 1);
	return color;
}

sf::Color getRainbowSpike(double theta) {
	sf::Color color;
	color.r = 128 * (sin(theta * sin(theta)) + 1);
	color.g = 128 * ((sin(theta * sin(theta)) + 3) + 1);
	color.b = 128 * ((sin(theta * sin(theta)) + 5) + 1);
	return color;
}

int main()
{
	sf::Clock clock;
	sf::Time timer;
    sf::Vector2i windowSize = sf::Vector2i(1000, 1000);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Oscillo");
	window.setPosition(sf::Vector2i(0, 0));
    sf::Image icon;
    icon.loadFromFile("res/icon512x512.png");
    window.setIcon(512, 512, icon.getPixelsPtr());
	sf::Event event;

	std::vector<Particle> particles;

	/* Particle initial conditions */
	// ------------------------------------------------------------------
	particles.push_back( Particle(sf::Vector2f(windowSize.x * (1.0/2.0), windowSize.y * (1.0/2.0) + 2)) );
	particles[0].cir.setRadius(5);
	///particles[0].cir.setFillColor(sf::Color::Red);
	//particles[0].cir.setPointCount(3);
	particles[0].mass = 0.2f;
	particles[0].vel.x = 0.02;
	//particles[0].vel.y = -0.1;

	particles.push_back( Particle(sf::Vector2f(windowSize.x * (1.0/2.0), windowSize.y * (1.0/2.0) - 2)) );
	particles[1].cir.setRadius(5);
	particles[1].mass = 0.2f;
	//particles[1].cir.setFillColor(sf::Color::Blue);
	//particles[1].cir.setPointCount(3);
	particles[1].vel.x = -0.02;
	//particles[1].vel.y = 0.1;

	// particles.push_back( Particle(sf::Vector2f(windowSize.x * (1.0/2.0) + 0.1, windowSize.y * (1.0/2.0) + 0.1)) );
	// particles[2].cir.setRadius(3);
	// particles[2].mass = 0.1f;
	// particles[2].cir.setFillColor(sf::Color::Green);

	// ------------------------------------------------------------------
	

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::S) { // Save window 
					const std::string filename = "capture";
					int num = 0;
					// checks for same filename
					std::ifstream f("saves/" + filename + std::to_string(num) + ".png");
					while (f.good()){
						num++;
						f.close();
						f.open("saves/" + filename + std::to_string(num) + ".png");
					}
					f.close();
					sf::Texture texture;
					texture.create(windowSize.x, windowSize.y);
					texture.update(window);
					sf::Image screenshot = texture.copyToImage();
					screenshot.saveToFile("saves/" + filename + std::to_string(num) + ".png");
				}
			}
			if (event.type == sf::Event::KeyReleased) {}
		}
		if ((clock.getElapsedTime().asMilliseconds() - timer.asMilliseconds()) > 16.6) {
			timer = clock.getElapsedTime();

			// Update Forces
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
						force = 0.1 / particles[i].mass;
						acc = sf::Vector2f((delta.x / mag) * force, (delta.y / mag) * force);
						particles[i].acc += acc;
					}
				}
			}

			for (unsigned int i = 0; i < particles.size(); i++) { // Ticks, update particles assets
				particles[i].tick();
				double distance = sqrt(
					pow((windowSize.x * 0.5) - particles[i].cir.getPosition().x, 2) +
					pow((windowSize.y * 0.5) - particles[i].cir.getPosition().y, 2)
				); // (i + 1) *
				double newScale = 0.05 * distance * (1 + i);
				// if (i == 0) { 
				// 	particles[0].cir.setOutlineThickness(newScale / 6);
				// 	particles[0].cir.setOutlineColor(getRainbowSpike(3.14159f + clock.getElapsedTime().asSeconds()));
				// }
                particles[i].cir.setRadius(newScale);
				particles[i].cir.setOrigin(sf::Vector2f(newScale, newScale));
				particles[i].cir.setFillColor(getRainbow(i + clock.getElapsedTime().asSeconds()));
			}
		}

		//window.clear(sf::Color::Black);

		for (unsigned int i = 0; i < particles.size(); i++) {
			particles[i].draw(window);
			
		}
		window.display();
	}
}
