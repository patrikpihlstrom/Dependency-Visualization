#include "Node.h"

Node::Node(const std::string & p_dependencies) :
	m_position(sf::Vector2<int>(-1, -1))
{
	if (!p_dependencies.empty())
	{
		m_identifier = *p_dependencies.begin();
		for (int i = 1; i < p_dependencies.size(); i += 2)
		{
			if (p_dependencies[i] != ':')
			{
				m_dependencies.push_back(p_dependencies[i]);
			}
		}
	}
}

Node::~Node()
{

}
