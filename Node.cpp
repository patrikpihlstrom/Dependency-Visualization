#include "Node.h"

Node::Node(const std::string & p_dependencies) :
	m_position(sf::Vector2<int>(-1, -1))
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
