#include "Node.h"

Node::Node(const std::string & p_dependencies, sf::Font* ptr_font) :
	m_position(sf::Vector2<int>(-1, -1)),
	ptr_font(ptr_font)
{
	unsigned int index = 0;

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

			for (int i = index; i < p_dependencies.size(); i++)
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

void Node::draw(sf::RenderWindow & p_renderWindow, const sf::Color & p_color, const bool & p_selected, std::vector<sf::Text> & p_texts)
{
	sf::CircleShape node(10);
	node.setFillColor(p_color);

	node.setOrigin(10, 10);
	node.setPosition(m_position.x, m_position.y);

	p_renderWindow.draw(node);

	if (p_selected)
	{
		sf::Text text;
		text.setColor(sf::Color::Black);
		text.setStyle(sf::Text::Style::Bold);
		text.setFont(*ptr_font);
		text.setString(m_identifier);

		text.setScale(0.5f, 0.5f);

		text.setPosition(m_position.x + 25, m_position.y - 10);
		
		if (text.getPosition().x + text.getGlobalBounds().width >= 640)
		{
			text.setPosition(m_position.x - text.getGlobalBounds().width - 25, text.getPosition().y);
		}

		p_texts.push_back(text);
	}
}
