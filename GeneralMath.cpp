#pragma once
#include "GeneralMath.h"

int math::random(int low, int high){
	if (low > high){
		int temp = low;
		low = high;
		high = temp;
	}
	return low + (std::rand() % (high - low + 1));
}

int math::random(int low, int high, int exclude){
	if (low > high){
		int temp = low;
		low = high;
		high = temp;
	}
	int i = low + (std::rand() % (high - low + 1));
	while (i == exclude)
	{
		i = random(low, high, exclude);
	}
	return i;
}

int math::random(int low, int high, std::vector<int> exclude){
	if (low > high){
		int temp = low;
		low = high;
		high = temp;
	}
	int i = low + (std::rand() % (high - low + 1));
	for (unsigned int j = 0; j < exclude.size(); j++)
	{
		if (i == exclude[j])
		{
			random(low, high, exclude);
		}
	}
	return i;
}

float math::toDegrees(float x)
{
	return x * 180 / (float)std::_Pi;
}

float math::toRadians(float x)
{
	return x / 180 * (float)std::_Pi;
}

float math::interpolate(float v0, float v1, float t)
{
	return v0+(v1-v0)*t;
}

sf::Vector2f math::interpolateVector(sf::Vector2f v0, sf::Vector2f v1, float t)
{
	return sf::Vector2f(interpolate(v0.x, v1.x, t), interpolate(v0.y, v1.y, t));
}