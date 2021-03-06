#pragma once
#include "main.hpp"


class Agents
{
public: 
	// -------- CONSTRUCTORS --------
	Agents(int _number, unsigned int _color);
	~Agents();


public: 
	// -------- PUBLIC CONTROLL FUNCTIONS --------
	// initialize "random", "middle"
	void initialize(std::string s);
	// changes positions according to velocity and delta time
	void update(double dt, datamap *map);
	// sets the datamap-pixels to 255 at the agent-positions
	void mapPositions(datamap *map);

	// -------- PUBLIC PARAMETERS FUNCTIONS --------
	// allows to set the velocity of all agents
	void setGroupVelocity(double a);
	// allows to set the randomness of all agents
	void setRandomness(float a);
	// allows to set the attraction of all agents
	void setAttraction(float a);

private: 
	// -------- PRIVATE VARIABLES --------
	int number;
	double v0;
	float randomness;
	float attraction;
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
	void attractAgents(double dt, datamap *map);


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


