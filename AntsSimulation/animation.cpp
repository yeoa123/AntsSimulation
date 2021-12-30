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
void Animation::fadeMap(datamap* draw, datamap* constant)
{
	draw->initData("zero");
	float dimm = 0.8f;

	// passing in x direction
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			// local position
			vec2i position = vec2i(i, j);
			// variables for storing the summation over gauss-vektor
			unsigned int r = 0;
			unsigned int g = 0;
			unsigned int b = 0;

			// iterate over gaussvector to get data from map into rgb
			for (int k = 0; k < gauss_size; k++)
			{
				// get offset position (local position + x-gauss-index)
				vec2i offset = position + vec2i(0, k-(gauss_size-1)/2);
				unsigned int data = constant->getData(offset);
				// get color 
				r += R(data) * gauss[k];
				g += G(data) * gauss[k];
				b += B(data) * gauss[k];
			}

			// resize with magnitude of gaussvector & compress data 
			r /= gauss_faktor;
			g /= gauss_faktor;
			b /= gauss_faktor;
			unsigned int sum = RGB(
						static_cast<unsigned int>(r),
						static_cast<unsigned int>(g),
						static_cast<unsigned int>(b)
									);
			// write summation to the map
			draw->setData(position, sum);
		}
	}

	constant->initData("zero");
	// writing first results back to const map
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			vec2i position = vec2i(i, j);
			constant->setData(position, draw->getData(position) );
		}
	}
	

	// passing in y direction
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			// get out local position
			vec2i position = vec2i(i, j);
			// variables for storing the summation over gauss-vektor
			unsigned int r = 0;
			unsigned int g = 0;
			unsigned int b = 0;

			// iterate over gaussvector to get data from map into rgb
			for (int k = 0; k < gauss_size; k++)
			{
				// get offset position (local position + x-gauss-index)
				vec2i offset = position + vec2i(k - (gauss_size - 1) / 2, 0);
				unsigned int data = constant->getData(offset);
				// get color 
				r += R(data) * gauss[k];
				g += G(data) * gauss[k];
				b += B(data) * gauss[k];
			}
			r /= gauss_faktor;
			g /= gauss_faktor;
			b /= gauss_faktor;

			unsigned int sum = RGB(
				static_cast<unsigned int>(r),
				static_cast<unsigned int>(g),
				static_cast<unsigned int>(b)
			);
			// write summation to the map
			draw->setData(position, sum);
		}
	}
	
};
