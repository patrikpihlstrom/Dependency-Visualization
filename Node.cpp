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

void Node::draw(sf::RenderWindow & p_renderWindow, const bool & p_selected, sf::Text & p_text)
{
	p_renderWindow.draw(m_sprite);

	if (p_selected)
	{

		for (int i = 0; i < m_dependencies.size(); ++i)
		{
			std::cout << m_dependencies[i] << "\n";
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
