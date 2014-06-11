#pragma once
#include <vector>
#include <string>
#include <SFML\System\Vector2.hpp>

struct Node
{
	Node(const std::string & p_dependencies = "");
	~Node();

	char m_identifier;

	std::vector<char> m_dependencies;

	sf::Vector2<int> m_position;
};