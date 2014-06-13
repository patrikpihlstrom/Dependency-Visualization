#pragma once
#include <vector>
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Sprite.hpp>

struct Node
{
	Node(const std::string & p_dependencies = "", sf::Font* ptr_font = NULL, const sf::Texture & p_texture = sf::Texture());
	~Node();

	std::string m_identifier;

	std::vector<std::string> m_dependencies;

	sf::Vector2<int> m_position;
	
	sf::Font* ptr_font;

	sf::Sprite m_sprite;

	void draw(sf::RenderWindow & p_renderWindow, const bool & p_selected, std::vector<sf::Text> & p_texts);
};
