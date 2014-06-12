#pragma once

#include "GeneralMath.h"

template <typename T>
float math::distance(sf::Vector2<T> const& lhs, sf::Vector2<T> const& rhs){
	return (float)std::sqrt(std::pow(std::abs(rhs.x - lhs.x), 2) + std::pow(std::abs(lhs.y - rhs.y), 2));
}

template <typename T>
bool math::LineIntersectsLine(const sf::Vector2<T> & l1p1, const sf::Vector2<T> & l1p2, const sf::Vector2<T> & l2p1, const sf::Vector2<T> & l2p2)
{
	float q = (l1p1.y - l2p1.y) * (l2p2.x - l2p1.x) - (l1p1.x - l2p1.x) * (l2p2.y - l2p1.y);
	float d = (l1p2.x - l1p1.x) * (l2p2.y - l2p1.y) - (l1p2.y - l1p1.y) * (l2p2.x - l2p1.x);

	if( d == 0 )
	{
		return false;
	}

	float r = q / d;

	q = (l1p1.y - l2p1.y) * (l1p2.x - l1p1.x) - (l1p1.x - l2p1.x) * (l1p2.y - l1p1.y);
	float s = q / d;

	if( r < 0 || r > 1 || s < 0 || s > 1 )
	{
		return false;
	}

	return true;
}

template <typename T>
bool math::LineIntersectsRect(const sf::Vector2<T> &  p1, const sf::Vector2<T> &  p2, const sf::Rect<T> & r)
{
	return LineIntersectsLine(p1, p2, sf::Vector2<T>(r.left, r.top), sf::Vector2<T>(r.left + r.width, r.top)) ||
		LineIntersectsLine(p1, p2, sf::Vector2<T>(r.left + r.width, r.top), sf::Vector2<T>(r.left + r.width, r.top + r.height)) ||
		LineIntersectsLine(p1, p2, sf::Vector2<T>(r.left + r.width, r.top + r.height), sf::Vector2<T>(r.left, r.top + r.height)) ||
		LineIntersectsLine(p1, p2, sf::Vector2<T>(r.left, r.top + r.height), sf::Vector2<T>(r.left, r.top)) ||
		(r.contains(p1) || r.contains(p2));
}

template <typename T>
bool math::LineIntersectsCircle(const sf::Vector2<T> & p1, const sf::Vector2<T> & p2, const sf::Vector2<T> & p_pos, const float & p_radius){
	if ((p1.x < (p_pos.x - p_radius) && p2.x < (p_pos.x)) ||
		(p1.x > (p_pos.x + p_radius) && p2.x > (p_pos.x + p_radius)) ||
		(p1.y < (p_pos.y - p_radius) && p2.y < (p_pos.y - p_radius)) ||
		(p1.y > (p_pos.y + p_radius) && p2.y > (p_pos.y + p_radius)))
	{
		return false;
	}else if (distance(p1, p_pos) <= p_radius || distance(p2, p_pos) <= p_radius)
	{
		return true;
	}
	
	/*
		   b
	   A______C
		\	 /|
		 \	/ |
		  \/  |a
		  D\  |
			\ |
			 \|
			  B
	*/
	
	float a = distance(p2, p_pos), b = distance(p1, p_pos), D = distance(p1, p2);
	float A = std::acos((std::pow(a, 2) - (std::pow(b, 2) + std::pow(D, 2)))/(-2*b*D));
	float CD = (std::sin(A)*b)/std::sin(90);

	return CD <= p_radius;
}