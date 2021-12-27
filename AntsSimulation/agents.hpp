#pragma once
#include "main.hpp"


// static variables


static const int circle_size = 16;
static const vec2i circle[circle_size] =
{
	vec2i(0, -10),
	vec2i(0, 10),
	vec2i(-10, 0),
	vec2i(10, 0),

	vec2i(4, -9),
	vec2i(-4, -9),
	vec2i(-4, 9),
	vec2i(4, 9),

	vec2i(7, -7),
	vec2i(-7, -7),
	vec2i(-7, 7),
	vec2i(7, 7),

	vec2i(9, -4),
	vec2i(-9, -4),
	vec2i(-9, 4),
	vec2i(9, 4)
};


class Agents
{
public: 
	// -------- CONSTRUCTORS --------
	Agents(int _number, unsigned int _color);
	~Agents();


public: 
	// -------- PUBLIC FUNCTIONS --------

	// initialize "random", "middle"
	void initialize(std::string s);
	// allows to set the velocity of all agents
	void setv0(double a);
	// changes positions according to velocity and delta time
	void update(double dt, datamap *map);
	// sets the datamap-pixels to 255 at the agent-positions
	void mapPositions(datamap *map);
	vec2f getPosition(int n)
	{
		return (*positions)[n];
	};


private: 
	// -------- PRIVATE VARIABLES --------
	int number;
	double v0;
	unsigned int color;
	std::vector<vec2f> *positions;
	std::vector<vec2f> *velocities;

		
private: 
	// -------- PRIVATE FUNCTIONS --------
	void normalizeVelocities();
	void checkPositionsBounds();
	static float invsqrt(float number);

private:
	// -------- UPDATE FUNCTIONS --------
	void updatePositions(double dt);
	void randomizeVelocities(double dt);
	void attractAgents1(double dt, datamap *map);
	void attractAgents2(double dt, datamap *map);


private: 
	// -------- STATIC PRIVATE FUNCTIONS --------
	static vec2i toVec2i(vec2f a)
	{
		vec2i v;
		v.x = static_cast<int>(a.x);
		v.y = static_cast<int>(a.y);
		return v;
	};
	static vec2f toVec2f(vec2i a)
	{
		vec2f v;
		v.x = static_cast<float>(a.x);
		v.y = static_cast<float>(a.y);
		return v;
	};
};


