#pragma once
#include "main.hpp"

static const int gauss_size = 5;
static const int gauss[gauss_size] = { 1, 4, 6, 4, 1 };
static const int filter_size = 4;
static const vec2i filter[filter_size] =
{
	vec2i(1, 0),
	vec2i(-1, 0),
	vec2i(0, -1),
	vec2i(0, 1)
};

class Animation
{
public: // static functions

	// translates the datamap into pixels
	static void updateVertexArray(sf::VertexArray* va, datamap *map);

	// gaussian blur of constant-frame, safe into draw-frame
	static void fadeMap1(datamap* draw, datamap* constant);
	static void fadeMap2(datamap* draw, datamap* constant);

private:
};
