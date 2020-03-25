#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class OscilloProject {
private:
	sf::Vector2i windowSize = sf::Vector2i(1200, 800);
	sf::Color getRainbow(double theta);
public:
	void exec();
};