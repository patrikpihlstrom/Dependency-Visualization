#include "Main.h"

int main()
{
	srand(static_cast<int>(time(NULL)));
	Main main = Main();
	return 0;
}

Main::Main() :
	m_window(sf::VideoMode(640, 640), "Transitive Dependency Visualizer"),
	m_running(true),
	m_active(true),
	m_levels(0)
{
	std::ifstream file;
	file.open("dependencies");

	if (file.is_open())
	{
		std::map<char, Node> temp;

		char last;

		while(!file.eof())
		{
			std::string line;
			std::getline(file, line);

			Node node(line);

			temp[node.m_identifier] = node;

			node.m_dependencies.clear();

			m_nodes[node.m_identifier] = node;

			last = node.m_identifier;
		}

		file.close();

		for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
		{
			for (int i = 0; i < 2; i++)
			{
				AddDependencies(it->second, temp);
			}

			std::cout << it->second.m_identifier;

			for (int i = 0; i < it->second.m_dependencies.size(); ++i)
			{
				std::cout << "<->" << it->second.m_dependencies[i];
			}

			std::cout << "\n";

			if (it->second.m_identifier != last)
			{
				std::cout << "|\n";
			}

			if (!it->second.m_dependencies.empty())
			{
				if (m_levels < it->second.m_dependencies.size())
				{
					m_levels = it->second.m_dependencies.size();
				}
			}
		}

		for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
		{
			setPosition(it->second);
		}

		run();
	}else
	{
		std::cout << "Unable to open file.\n";
	}


}

Main::~Main()
{

}

void Main::run()
{
	sf::Clock dt;
	sf::Time lag;
	sf::Time updateTime = sf::seconds(1.f/60.f);

	while (m_running)
	{
		lag += dt.getElapsedTime();
		dt.restart();

		handleEvents();
		render();
		while (lag >= updateTime)
		{
			update(updateTime);
			lag -= updateTime;
		}
	}
}

void Main::AddDependencies(Node & p_node, std::map<char, Node> & p_temp)
{
	for (int i = 0; i < p_temp[p_node.m_identifier].m_dependencies.size(); i++)
	{
		AddDependencies(p_node, p_temp[p_node.m_identifier].m_dependencies[i], p_temp);
	}
}

void Main::AddDependencies(Node & p_node, const char & p_identifier, std::map<char, Node> & p_temp)
{
	if (m_nodes.find(p_identifier) != m_nodes.end())
	{
		if (!find(p_node, p_identifier))
		{
			p_node.m_dependencies.push_back(p_identifier);
		}

		for (int i = 0; i < p_temp[p_identifier].m_dependencies.size(); ++i)
		{
			AddDependencies(p_node, p_temp[p_identifier].m_dependencies[i], p_temp);
		}
	}
}

bool Main::find(const Node & p_node, const char & p_identifier) const
{
	for (auto it = p_node.m_dependencies.begin(); it != p_node.m_dependencies.end(); ++it)
	{
		if (*it == p_identifier)
		{
			return true;
		}
	}

	return false;
}

void Main::setPosition(Node & p_node)
{
	float angle = math::random(0, 360);


	angle = math::toRadians(angle);

	float radius = 320 - (310/m_levels)*p_node.m_dependencies.size();

	//std::cout << p_node.m_identifier << ": " << radius << "\n";

	p_node.m_position.x = std::cos(angle)*radius + 320;
	p_node.m_position.y = std::sin(angle)*radius + 320;
}

void Main::handleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
			m_running = false;
		}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_running = false;
		}else if (event.type == sf::Event::GainedFocus){
			m_active = true;
		} else if (event.type == sf::Event::LostFocus) {
			m_active = false;
		}
	}
}

void Main::update(const sf::Time & p_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
		{
			setPosition(it->second);
		}
	}
}

void Main::render()
{
	m_window.clear(sf::Color(50, 50, 50));
	sf::VertexArray lines;
	lines.setPrimitiveType(sf::PrimitiveType::Lines);

	for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		for (auto iter = it->second.m_dependencies.begin(); iter != it->second.m_dependencies.end(); ++iter)
		{
			sf::Vertex point;
			point.position = (sf::Vector2<float>)it->second.m_position;
			point.color = sf::Color::White;

			lines.append(point);

			sf::Vertex _point;
			_point.position = (sf::Vector2<float>)m_nodes[*iter].m_position;
			_point.color = sf::Color::Black;

			lines.append(_point);
		}
	}

	m_window.draw(lines);

	for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		sf::CircleShape node(10);

		node.setOrigin(5, 5);

		node.setPosition(it->second.m_position.x, it->second.m_position.y);

		node.setFillColor(sf::Color::White);

		m_window.draw(node);
	}

	m_window.display();
}