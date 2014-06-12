#include "Main.h"

int main(int argc, char* argv[])
{
	srand(static_cast<int>(time(NULL)));
	Main main = Main(argv[1]);
	return 0;
}

Main::Main(const std::string & p_path) :
	m_window(sf::VideoMode(640, 640), "Transitive Dependency Visualizer"),
	m_running(true),
	m_active(true),
	m_levels(0)
{
	m_font.loadFromFile("SourceCodePro-Regular.ttf");

	std::vector<std::string> files;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (p_path.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			files.push_back(ent->d_name);
		}
		closedir (dir);
	}

	std::map<std::string, Node> temp;

	std::string last;

	for (int i = 2; i < files.size(); i++)
	{
		if ((files[i][files[i].size() - 1] == 'h' && files[i][files[i].size() - 2] == '.') ||
			(files[i][files[i].size() - 1] == 'p' && files[i][files[i].size() - 2] == 'p' && files[i][files[i].size() - 3] == 'h' && files[i][files[i].size() - 4] == '.') ||
			(files[i][files[i].size() - 1] == 'l' && files[i][files[i].size() - 2] == 'n' && files[i][files[i].size() - 3] == 'i' && files[i][files[i].size() - 4] == '.') ||
			(files[i][files[i].size() - 1] == 'p' && files[i][files[i].size() - 2] == 'p' && files[i][files[i].size() - 3] == 'c' && files[i][files[i].size() - 4] == '.'))
		{
			std::ifstream file;
			file.open(p_path + files[i]);

			if (file.is_open())
			{
				std::string dependencies;

				dependencies.insert(dependencies.begin(), files[i].begin(), files[i].end());
				dependencies.push_back(':');

				while (!file.eof())
				{
					std::string line;
					std::getline(file, line);

					if (line.size() > 8)
					{
						std::string tag;
						tag.insert(tag.begin(), line.begin(), line.begin() + 8);

						if (tag == "#include")
						{
							tag.clear();
							tag.insert(tag.begin(), line.begin() + 10, line.begin() + line.size() - 1);

							if (!find(tag, files))
							{
								Node lib = Node(tag, &m_font);
								m_nodes[tag] = lib;
							}

							dependencies.insert(dependencies.end(), tag.begin(), tag.end());
							dependencies.push_back(';');

							//std::cout << tag << "\n";
						}
					}
				}

				Node node(dependencies, &m_font);

				temp[node.m_identifier] = node;

				node.m_dependencies.clear();

				m_nodes[node.m_identifier] = node;

				last = node.m_identifier;

				file.close();
			}
		}
	}

	for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		AddDependencies(it->second, temp);

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

void Main::AddDependencies(Node & p_node, std::map<std::string, Node> & p_temp)
{
	for (int i = 0; i < p_temp[p_node.m_identifier].m_dependencies.size(); i++)
	{
		AddDependencies(p_node, p_temp[p_node.m_identifier].m_dependencies[i], p_temp);
	}
}

void Main::AddDependencies(Node & p_node, const std::string & p_identifier, std::map<std::string, Node> & p_temp)
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

bool Main::find(const Node & p_node, const std::string & p_identifier) const
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

bool Main::find(const std::string & p_identifier, const std::vector<std::string> & p_vector) const
{
	for (int i = 0; i < p_vector.size(); i++)
	{
		if (p_vector[i] == p_identifier)
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

	float radius = 310 - (310/m_levels)*p_node.m_dependencies.size();

	//std::cout << p_node.m_identifier << ": " << radius << "\n";

	p_node.m_position.x = std::cos(angle)*radius + 320;
	p_node.m_position.y = std::sin(angle)*radius + 320;

	for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		if (it->second.m_identifier != p_node.m_identifier && it->second.m_position != sf::Vector2<int>(-1, -1))
		{
			if (math::distance(p_node.m_position, it->second.m_position) <= 10)
			{
				setPosition(p_node);
			}
		}
	}
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

}

void Main::render()
{
	m_window.clear(sf::Color(50, 50, 50));
	sf::VertexArray lines;
	lines.setPrimitiveType(sf::PrimitiveType::LinesStrip);

	for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		sf::Color color = sf::Color(255, 255, 255, 500*((float)((float)it->second.m_dependencies.size()/(float)m_levels)));

		if (color.a < 50)
		{
			color.a = 50;
		}

		for (auto iter = it->second.m_dependencies.begin(); iter != it->second.m_dependencies.end(); ++iter)
		{
			sf::Vertex point;
			point.position = sf::Vector2<float>(it->second.m_position.x, it->second.m_position.y);
			point.color = color;

			lines.append(point);

			sf::Color _color = sf::Color(255, 255, 255, 500*((float)((float)m_nodes[*iter].m_dependencies.size()/(float)m_levels)));

			if (_color.a < 50)
			{
				_color.a = 50;
			}

			sf::Vertex _point;
			_point.position = sf::Vector2<float>(m_nodes[*iter].m_position.x, m_nodes[*iter].m_position.y);
			_point.color = _color;

			lines.append(_point);
		}
	}

	m_window.draw(lines);

	std::vector<sf::Text> texts;

	for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		sf::Color color = sf::Color(255, 255, 255, 500*((float)((float)it->second.m_dependencies.size()/(float)m_levels)));

		if (color.a < 50)
		{
			color.a = 50;
		}

		

		it->second.draw(m_window, color, (math::distance(sf::Mouse::getPosition(m_window), it->second.m_position) <= 10), texts);
	}

	if (!texts.empty())
	{
		m_window.draw(texts[0]);
	}

	m_window.display();
}