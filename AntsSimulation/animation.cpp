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

void Animation::fadeMap(datamap *draw, datamap *constant)
{
	// this is simple gaussian 3x3 blur
	// set draw-map to zero
	draw->initData("zero");
	// add (constant-map + offsets) * factor onto draw-map
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			// setup some variables
			unsigned int r = 0;
			unsigned int g = 0;
			unsigned int b = 0;

			vec2i position = vec2i(i, j);
			vec2i offset;

			// get the values from constant with offset and factor
			for (auto f = 0; f < filter_size; f++)
			{
				offset = position + filter[f];
				if (datamap::inMap(offset))
				{
					unsigned int data = constant->getData(offset);
					r += R(data);
					g += G(data);
					b += B(data);
				}
			}
			// faktoring value with inverse kernel
			r >>= 2;
			g >>= 2;
			b >>= 2;
			// load value into draw
			float dimm = 0.8f;
			float foor = static_cast<float>(r);
			foor *= dimm;
			float foog = static_cast<float>(g);
			foog *= dimm;
			float foob = static_cast<float>(b);
			foob *= dimm;
			r = static_cast<unsigned int>(foor);
			g = static_cast<unsigned int>(foog);
			b = static_cast<unsigned int>(foob);
			draw->setData(position, RGB(r, g, b));
		}
	}
};