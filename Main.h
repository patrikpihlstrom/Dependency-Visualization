#pragma once
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\Graphics\Font.hpp>
#include <dirent.h>

#include "Node.h"
#include "GeneralMath.h"

class Main
{
public:
	Main(const std::string & p_path = "");
	~Main();

private:
	std::map<std::string, Node> m_nodes;

	void AddDependencies(Node & p_node, std::map<std::string, Node> & p_temp);

	void AddDependencies(Node & p_node, const std::string & p_identifier, std::map<std::string, Node> & p_temp);

	bool find(const Node & p_node, const std::string & p_identifier) const;

	sf::RenderWindow m_window;

	void run();

	void handleEvents();

	void update(const sf::Time & p_deltaTime);

	void render();

	bool m_running, m_active;

	void setPosition(Node & p_node);

	int m_levels;
};