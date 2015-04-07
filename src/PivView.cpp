#include "PivView.hpp"

// class AxisBox : public sf::VertexArray
// {
// 	public:
// 		AxisBox(int x0, int x1, int y0, int y1);
// };
//
// AxisBox::AxisBox(int x0, int x1, int y0, int y1) : sf::VertexArray(sf::LinesStrip, 5)
// {
// 	std::cout << x0 << y0 << x1 << y1 << std::endl;
// 	std::cout << getVertexCount() << std::endl;
// }

PivView::PivView(PivEng::PivPoint::PivPointVec& vs) :
	m_pivPointVec(vs),
	piv_vectors(vs.size())
{
	get_piv_vectors_and_maximum_velocity();

	std::vector<sf::VertexArray> vel_vector_graphics(num_vectors);
	auto vel_vector_graphicsPtr = &vel_vector_graphics[0];

	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(612, 612), "BPPIV Vector Viewer", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	/* Set up the axis */
	sf::VertexArray ln(sf::Lines, 2);

	auto axisBox = make_axis_box(50, 50, 562, 562);

	auto xCross = sf::VertexArray(sf::Lines, 2);
	auto yCross = sf::VertexArray(sf::Lines, 2);
	xCross[0].position.x = 50;
	xCross[1].position.x = 562;
	yCross[0].position.y = 50;
	yCross[1].position.y = 562;

	std::for_each(m_pivPointVec.begin(), m_pivPointVec.end(), [&](auto& pointf) {
		auto point = pointf.get_piv_vector();
		if (point) {
			*(vel_vector_graphicsPtr++) = make_vector_graphic(*point);	
		}
	});

	/* Clear, draw, display frame rendering routine */
	auto renderFrame = [&]() {
		window.clear(sf::Color::Black);
		window.draw(axisBox);
		window.draw(xCross);
		window.draw(yCross);
		std::for_each(vel_vector_graphics.begin(), vel_vector_graphics.end(), [&](auto& dv) { window.draw(dv); });
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

void PivView::get_piv_vectors_and_maximum_velocity()
{
	auto vector_magnitude = 0.0;
	auto counter = 0;
	for(auto& piv_point : m_pivPointVec) {
		auto piv_vector = piv_point.get_piv_vector();
		if (piv_vector) {
			vector_magnitude = piv_vector->get_magnitude();
			piv_vectors[counter++] = *piv_vector;
			if (vector_magnitude > max_velocity_magnitude)
				max_velocity_magnitude = vector_magnitude;
		}
	}
	piv_vectors.resize(counter);
	num_vectors = counter;
}
		
sf::Color PivView::vector_color(const double vel_magnitude, const double max_vel_magnitude) const
{
			auto red = 255 - static_cast<uint8_t>(vel_magnitude / max_vel_magnitude * 255);
			auto green = static_cast<uint8_t>(0);
			auto blue = static_cast<uint8_t>(vel_magnitude / max_vel_magnitude * 255);
			return sf::Color(red, green, blue);
}

sf::VertexArray PivView::make_vector_graphic(PivEng::PivVector& piv_vector)
{
	auto factor = 3;
	auto x = piv_vector.get_x(),
		 y = piv_vector.get_y(),
		 u = piv_vector.get_u(),
		 v = piv_vector.get_v();

	sf::VertexArray vector_lines(sf::Lines, 2);

	vector_lines[0].position = sf::Vector2f(50 + x, 50 + y);
	vector_lines[1].position = sf::Vector2f(50 + x + factor * u, 50 + y + factor * v);

	auto mag = piv_vector.get_magnitude();
	sf::Color magnitude_color = vector_color(mag, max_velocity_magnitude);

	vector_lines[0].color = magnitude_color; 
	vector_lines[1].color = magnitude_color;

	return vector_lines;
}

sf::VertexArray PivView::make_axis_box(const int i_min, const int j_min, const int i_max, const int j_max) const
{
	auto axis_box = sf::VertexArray(sf::LinesStrip, 5);
	axis_box[0] = sf::Vector2f(i_min, j_max);
	axis_box[1] = sf::Vector2f(i_max, j_max);
	axis_box[2] = sf::Vector2f(i_max, j_min);
	axis_box[3] = sf::Vector2f(i_min, j_min);
	axis_box[4] = axis_box[0];
	return axis_box;
}
