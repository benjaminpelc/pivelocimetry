#ifndef BPPIV_PIV_VIEW_H
#define BPPIV_PIV_VIEW_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "PivPoint.hpp"

class PivView
{
	public:
		PivView(PivEng::PivPoint::PivPointVec& vs);
		~PivView();

	private:
		PivEng::PivPoint::PivPointVec& m_pivPointVec;
		
};

PivView::PivView(PivEng::PivPoint::PivPointVec& vs) :
	m_pivPointVec(vs)
{

	auto factor(2.5);
	std::vector<sf::VertexArray> dvs;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(612, 612), "BPPIV Vector Viewer", sf::Style::Default, settings);
	window.setFramerateLimit(5);

	sf::VertexArray ln(sf::Lines, 2);

	auto xAxis = sf::VertexArray(sf::Lines, 2);
	auto yAxis = sf::VertexArray(sf::Lines, 2);

	xAxis[0].position = sf::Vector2f(50, 562);
	xAxis[1].position = sf::Vector2f(562, 562);
	
	yAxis[0].position = sf::Vector2f(50, 50);
	yAxis[1].position = sf::Vector2f(50, 562);

	std::for_each(m_pivPointVec.begin(), m_pivPointVec.end(), [&](auto& pointf) {
		auto point = pointf.getDv();
		if (point.u < 6.0 && point.v < 6.0) {
			ln[0].position = sf::Vector2f(50 + point.x, 50 + point.y);
			ln[1].position = sf::Vector2f(50 + point.x + factor * point.u, 50 + point.y + factor * point.v);
			ln[0].color = sf::Color::Blue;
			ln[1].color = sf::Color::Blue;
			dvs.push_back(ln);
		}
	});

	// sf::CircleShape shape{100.f};
	// shape.setFillColor(sf::Color::Red);

		window.clear(sf::Color::Black);
		window.draw(xAxis);
		window.draw(yAxis);
		std::for_each(dvs.begin(), dvs.end(), [&](auto& dv) { window.draw(dv); });
		window.display();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::cout << "Closing window" << std::endl;
				window.close();
			}
		}

	}
}

PivView::~PivView()
{
}

#endif
