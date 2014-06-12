#pragma once
#include <vector>
#include <string>
#include <SFML\System\Vector2.hpp>

struct Node
{
	Node(const std::string & p_dependencies = "");
	~Node();

	std::string m_identifier;

	std::vector<std::string> m_dependencies;

	sf::Vector2<int> m_position;
};