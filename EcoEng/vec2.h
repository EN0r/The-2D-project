#pragma once

struct vec2 // takes two floats x,y
{
	float x, y;
	vec2(float x, float y) { this->x = x; this->y = y; }
	inline void operator +(vec2 a)
	{
		x = x + a.x;
		y = y + a.y;
	}
	inline void operator -(vec2 a)
	{
		x = x - a.x;
		y = y - a.y;
	}
	inline bool operator ==(vec2 a)
	{
		if (x == a.x && y == a.y)
			return true;
		return false;
	}
};