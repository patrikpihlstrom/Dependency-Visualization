#pragma once
#include <vector>
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

struct Node
{
	Node(const std::string & p_dependencies = "", sf::Font* ptr_font = NULL);
	~Node();

	std::string m_identifier;

	std::vector<std::string> m_dependencies;

	sf::Vector2<int> m_position;
	
	sf::Font* ptr_font;

	void draw(sf::RenderWindow & p_renderWindow, const sf::Color & p_color, const bool & p_selected, std::vector<sf::Text> & p_texts);
};
