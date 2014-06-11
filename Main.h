#pragma once
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\CircleShape.hpp>

#include "Node.h"
#include "GeneralMath.h"

class Main
{
public:
	Main();
	~Main();

private:
	std::map<char, Node> m_nodes;

	void AddDependencies(Node & p_node, std::map<char, Node> & p_temp);

	void AddDependencies(Node & p_node, const char & p_identifier, std::map<char, Node> & p_temp);

	bool find(const Node & p_node, const char & p_identifier) const;

	sf::RenderWindow m_window;

	void run();

	void handleEvents();

	void update(const sf::Time & p_deltaTime);

	void render();

	bool m_running, m_active;

	void setPosition(Node & p_node);

	int m_levels;
};