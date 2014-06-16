#include "Node.h"

Node::Node(const std::string & p_dependencies, sf::Font* ptr_font, const sf::Texture & p_texture) :
	m_position(sf::Vector2<int>(-1, -1)),
	ptr_font(ptr_font)
{
	unsigned int index = 0;

	m_sprite.setTexture(p_texture);
	m_sprite.setOrigin(10, 10);

	if (!p_dependencies.empty())
	{
		for (int i = 0; i < p_dependencies.size(); i++)
		{
			if (p_dependencies[i] != ':')
			{
				m_identifier.push_back(p_dependencies[i]);
			}else
			{
				index = i;
				break;
			}
		}

		if (index != 0)
		{
			std::string dependency;

			for (int i = index + 1; i < p_dependencies.size(); i++)
			{
				if (p_dependencies[i] != ';')
				{
					dependency.push_back(p_dependencies[i]);
				}else
				{
					m_dependencies.push_back(dependency);
					dependency.clear();
				}
			}
		}
	}
}

Node::~Node()
{

}

void Node::draw(sf::RenderWindow & p_renderWindow, const bool & p_selected, sf::Text & p_text, const std::map<std::string, Node> & p_nodes, const unsigned int & p_levels, sf::VertexArray & p_lines) const
{
	p_renderWindow.draw(m_sprite);

	if (p_selected)
	{
		p_lines.setPrimitiveType(sf::PrimitiveType::Lines);

		sf::Color color = sf::Color(255, 255, 255, 500*((float)((float)m_dependencies.size()/(float)p_levels)));

		if (color.a < 50)
		{
			color.a = 50;
		}

		for (auto it = m_dependencies.begin(); it != m_dependencies.end(); ++it)
		{
			sf::Vertex point;
			point.position = sf::Vector2<float>(m_position.x, m_position.y);
			point.color = color;

			p_lines.append(point);

			sf::Color _color = sf::Color(255, 255, 255, 500*((float)((float)p_nodes.at(*it).m_dependencies.size()/(float)p_levels)));

			if (_color.a < 50)
			{
				_color.a = 50;
			}

			sf::Vertex _point;
			_point.position = sf::Vector2<float>(p_nodes.at(*it).m_position.x, p_nodes.at(*it).m_position.y);
			_point.color = _color;

			p_lines.append(_point);
		}

		sf::Text text;
		text.setColor(sf::Color::White);
		text.setStyle(sf::Text::Style::Bold);
		text.setFont(*ptr_font);
		text.setString(m_identifier);

		text.setScale(0.5f, 0.5f);

		text.setPosition(m_position.x + 25, m_position.y - 10);

		if (text.getPosition().x + text.getGlobalBounds().width >= 640)
		{
			text.setPosition(m_position.x - text.getGlobalBounds().width - 25, text.getPosition().y);
		}

		p_text = text;
	}
}
