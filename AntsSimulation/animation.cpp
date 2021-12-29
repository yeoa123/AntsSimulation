#pragma once
#include "animation.hpp"

	 
void Animation::updateVertexArray(sf::VertexArray* va, datamap* map)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			unsigned int a = map->getData(vec2i(i, j));
			unsigned int r = R(a);
			unsigned int g = G(a);
			unsigned int b = B(a);
			(*va)[i + (j * WIDTH)] = sf::Vertex::Vertex(sf::Vector2f(i, j), sf::Color::Color(r, g, b));
		}
	}
};

// two steps vector window to fade
void Animation::fadeMa(datamap* draw, datamap* constant)
{
	draw->initData("zero");
	float value;
	// passing in x direction
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			vec2i position = vec2i(i, j);
			value = 0.f;
			for (int g = 0; g < gauss_size; g++)
			{
				vec2i offset = position + vec2i(0, g-2);
				if (datamap::inMap(offset))
					value += static_cast<float>(constant->getData(offset) * gauss[g]);
			}
			draw->addData(position, static_cast<int>(value));
		}
	}

	// passing in y direction
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			vec2i position = vec2i(i, j);
			value = 0.f;
			for (int g = 0; g < gauss_size; g++)
			{
				vec2i offset = position + vec2i(g - 2, 0);
				if (datamap::inMap(offset))
					value += static_cast<float>(constant->getData(offset) * gauss[g]);
			}
			draw->addData(position, static_cast<int>(value));
		}
	}
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			vec2i position = vec2i(i, j);
			draw->divData( position, 256 );
		}
	}
};
