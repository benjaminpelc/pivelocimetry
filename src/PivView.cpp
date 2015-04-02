#include "PivView.hpp"

class AxisBox : public sf::VertexArray
{
	public:
		AxisBox(int x0, int x1, int y0, int y1);
};

AxisBox::AxisBox(int x0, int x1, int y0, int y1) : sf::VertexArray(sf::LinesStrip, 5)
{
	std::cout << x0 << y0 << x1 << y1 << std::endl;
	std::cout << getVertexCount() << std::endl;
}

PivView::PivView(PivEng::PivPoint::PivPointVec& vs) :
	m_pivPointVec(vs)
{

	auto factor(3);
	std::vector<sf::VertexArray> dvs(vs.size());
	auto dvsPtr = &dvs[0];

	auto me = AxisBox(1,2,3,4);

	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(612, 612), "BPPIV Vector Viewer", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	/* Set up the axis */
	sf::VertexArray ln(sf::Lines, 2);

	auto axisBox = sf::VertexArray(sf::LinesStrip, 5);
	axisBox[0] = sf::Vector2f(50, 562);
	axisBox[1] = sf::Vector2f(562, 562);
	axisBox[2] = sf::Vector2f(562, 50);
	axisBox[3] = sf::Vector2f(50, 50);
	axisBox[4] = sf::Vector2f(50, 562);

	auto xCross = sf::VertexArray(sf::Lines, 2);
	auto yCross = sf::VertexArray(sf::Lines, 2);
	xCross[0].position.x = 50;
	xCross[1].position.x = 562;
	yCross[0].position.y = 50;
	yCross[1].position.y = 562;

	auto maxV = 0.0;
	auto mag = 0.0;
	auto red = 0;
	auto blue = 0;

	/* Loop through and find maximum velocity magnitude */
	for(auto& pointf : m_pivPointVec) {
		auto point = pointf.getDv();
		if (point) {
			mag = point->mag();
			if (mag > maxV)
				maxV = mag;
		}
	}

	std::for_each(m_pivPointVec.begin(), m_pivPointVec.end(), [&](auto& pointf) {
		auto point = pointf.getDv();
		if (point) {
			ln[0].position = sf::Vector2f(50 + point->x, 50 + point->y);
			ln[1].position = sf::Vector2f(50 + point->x + factor * point->u, 50 + point->y + factor * point->v);

			mag = point->mag();

			red = 255 - static_cast<int>(mag / maxV * 255);
			blue = static_cast<int>(mag / maxV * 255);

			ln[0].color = sf::Color(red, 0, blue);
			ln[1].color = sf::Color(red, 0, blue);

			*(dvsPtr++) = ln;
		}
	});

	/* Clear, draw, display frame rendering routine */
	auto renderFrame = [&]() {
		window.clear(sf::Color::Black);
		window.draw(axisBox);
		window.draw(xCross);
		window.draw(yCross);
		std::for_each(dvs.begin(), dvs.end(), [&](auto& dv) { window.draw(dv); });
		window.display();
	};

	auto mouse = sf::Vector2i();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			switch (event.type) {
				case sf::Event::Closed:
					window.close();

				case sf::Event::Resized:
					renderFrame();

				case sf::Event::MouseMoved:
					mouse = sf::Mouse::getPosition(window);
					if (mouse.x > 50 && mouse.x < 562 && mouse.y > 50 && mouse.y < 562) {
						xCross[0].position.y = mouse.y;
						xCross[1].position.y = mouse.y;
						yCross[0].position.x = mouse.x;
						yCross[1].position.x = mouse.x;
						renderFrame();
					}

				default:
					;
			}
		}
		renderFrame();
	}
}

PivView::~PivView()
{
}
