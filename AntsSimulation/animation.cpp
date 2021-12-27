#pragma once
#include "animation.hpp"

	 
void Animation::updateVertexArray1(sf::VertexArray* va,  datamap *map)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			unsigned int a = map->getData(vec2i(i, j));
			(*va)[i + j*WIDTH] = sf::Vertex::Vertex( sf::Vector2f(i, j), sf::Color::Color(a, a, a) );
		}
	}
};

void Animation::updateVertexArray2(sf::VertexArray* va, datamap* map)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			unsigned int a = map->getData(vec2i(i, j));
			unsigned int r = R(a);
			unsigned int g = G(a);
			unsigned int b = B(a);
			(*va)[i + j * WIDTH] = sf::Vertex::Vertex(sf::Vector2f(i, j), sf::Color::Color(r, g, b));
		}
	}
};

void Animation::fadeMap1(datamap *draw, datamap *constant)
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
			float dimm = 0.5f;
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

void Animation::fadeMap2(datamap* draw, datamap* constant)
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
