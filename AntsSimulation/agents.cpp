#pragma once
#include "agents.hpp"


// -------- CONSTRUCTORS --------
Agents::Agents(int _number, unsigned int _color)
{
	v0 = 35.0f;
	randomness = 10.0f;
	attraction = 5000.0f;
	color = _color;
	number = _number;
	initialize("middle");
};
Agents::~Agents()
{
	delete[] positions;
	delete[] velocities;
};


// -------- PUBLIC CONTROLL FUNCTIONS --------
void Agents::initialize(std::string s)
{
	// allocate positions and velocities on the heap
	positions = new std::vector<vec2f>(number);
	velocities = new std::vector<vec2f>(number);

	if (s == "random")
	{
		for (auto i = 0; i < number; i++)
		{
			// get the position and velocity of the i-th agent
			vec2f p;
			vec2f v;

			// x:
			p.x = rand() % WIDTH;
			v.x = (rand() % 30) - 15;

			// y:
			p.y = rand() % HEIGHT;
			v.y = (rand() % 30) - 15;

			// set the position and velocity of the i-th agent
			(*positions)[i] = p;
			(*velocities)[i] = v;
		}
	}
	
	if (s == "middle")
	{
		for (auto i = 0; i < number; i++)
		{
			// get the position and velocity of the i-th agent
			vec2f p;
			vec2f v;

			// x:
			p.x = WIDTH/2;
			v.x = (rand() % 30) - 15;

			// y:
			p.y = HEIGHT/2;
			v.y = (rand() % 30) - 15;

			// set the position and velocity of the i-th agent
			(*positions)[i] = p;
			(*velocities)[i] = v;
		}
	}
	normalizeVelocities();
};
void Agents::update(double dt, datamap *map)
{
	// add velocitites*dt to positions
	updatePositions(dt);
	// add random component to velocities
	randomizeVelocities(dt);
	// change velocities into direction of pheromones
	// velocity dependend directionary attractor
	attractAgents(dt, map);
	// check if they are in the cage and change velocities if necessary
	checkPositionsBounds();
	normalizeVelocities();
}
void Agents::mapPositions(datamap *map)
{
	// iterate over agents positions
	for (auto i = 0; i < number; i++)
	{
		vec2f pf = (*positions)[i];
		vec2i pi = vec2i(static_cast<int>(pf.x), static_cast<int>(pf.y));
		map->setData( pi , color);
	}
}


// -------- PUBLIC PARAMETERS FUNCTIONS --------
void Agents::setGroupVelocity(double a)
{
	 if (a > 0)
	 {
		 v0 = a;
	 }
	 else
	 {
		 v0 = 0;
	 }
	 normalizeVelocities();
};
void Agents::setRandomness(float a)
{
	if (a > 0)
	{
		randomness = a;
	}
	else
	{
		randomness = 0;
	}
};
void Agents::setAttraction(float a)
{
	if (a > 0)
	{
		attraction = a;
	}
	else
	{
		attraction = 0;
	}
};


// -------- PRIVATE FUNCTIONS --------
void Agents::normalizeVelocities()
{
	for (auto i = 0; i < number; i++)
	{
		// get the velocity of the i-th agent
		vec2f v = (*velocities)[i];
		// calculate the inverse magnitude of velocity
		float f = invsqrt(v.abs());
		// normalize velocity
		v.x = v.x * f * v0;
		v.y = v.y * f * v0;
		// set the velocity of the i-th agent
		(*velocities)[i] = v;
	}
};
void Agents::checkPositionsBounds()
{
	for (auto i = 0; i < number; i++)
	{
		if (static_cast<int>((*positions)[i].x) < 0)
		{
			// agent exited to the left
			(*positions)[i].x = 0.f;
			(*velocities)[i].x = -(*velocities)[i].x;
		}
		if (static_cast<int>((*positions)[i].x) > WIDTH - 1)
		{

			// agent exited to the right
			(*positions)[i].x = static_cast<double>(WIDTH - 1);
			(*velocities)[i].x = -(*velocities)[i].x;
		}
		if (static_cast<int>((*positions)[i].y) < 0)
		{
			// agent exited to the top
			(*positions)[i].y = 0.f;
			(*velocities)[i].y = -(*velocities)[i].y;
		}
		if (static_cast<int>((*positions)[i].y) > HEIGHT - 1)
		{
			// agent exited to the bottom
			(*positions)[i].y = static_cast<double>(HEIGHT - 1);
			(*velocities)[i].y = -(*velocities)[i].y;
		}
	}
};
float Agents::invsqrt(float number)
{
	double y = static_cast<float>(number);
	double x2 = y * 0.5;
	std::int64_t i = *(std::int64_t*)&y;
	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	y = *(double*)&i;
	y = y * (1.5 - (x2 * y * y));   // 1st iteration
	// y  = y * ( 1.5 - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	return static_cast<float>(y);
};


// -------- UPDATE FUNCTIONS --------
void Agents::updatePositions(double dt)
{
	for (auto i = 0; i < number; i++)
	{
		// calculate new positions
		(*positions)[i].x += (*velocities)[i].x * dt;
		(*positions)[i].y += (*velocities)[i].y * dt;
	}
};
void Agents::randomizeVelocities(double dt)
{
	for (auto i = 0; i < number; i++)
	{
		// randomize velocities
		(*velocities)[i].x += randomness * dt * static_cast<float>(rand() % 100 - 50) * 0.1f;
		(*velocities)[i].y += randomness * dt * static_cast<float>(rand() % 100 - 50) * 0.1f;
	}
};
void Agents::attractAgents(double dt, datamap* map)
{
	for (auto i = 0; i < number; i++)
	{
		vec2f v = (*velocities)[i];
		// unit vector in direction of velocity
		vec2f ve = v * invsqrt(v.abs());
		vec2f pos = (*positions)[i];
		vec2f global;
		vec2f dv = vec2f(0.f, 0.f);
		unsigned int value, antivalue;
		unsigned int r, g, b;

		// front
		v = (ve * 5);
		global = v + pos;
		value = color & map->getData(toVec2i(global));
		r = R(value);
		g = G(value);
		b = B(value);
		value = r + g + b;
		dv = dv + (v * value);

		// front right
		v = (ve * 4) + (ve.right() * 2);
		global = v + pos;
		value = color & map->getData(toVec2i(global));
		r = R(value);
		g = G(value);
		b = B(value);
		value = r + g + b;
		dv = dv + (v * value);

		// front left
		v = (ve * 4) + (ve.left() * 2);
		global = v + pos;
		value = color & map->getData(toVec2i(global));
		r = R(value);
		g = G(value);
		b = B(value);
		value = r + g + b;
		dv = dv + (v * value);

		// change velocities
		(*velocities)[i].x += dv.x * attraction * dt;
		(*velocities)[i].y += dv.y * attraction * dt;
	}
};
