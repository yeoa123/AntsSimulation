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

	// passing in x direction
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			// get out local position
			vec2i position = vec2i(i, j);
			// variable for storing the summation over gauss-vektor
			unsigned int sum;
			for (int k = 0; k < gauss_size; k++)
			{
				// get offset position (local position + x-gauss-index)
				vec2i offset = position + vec2i(0, k-(gauss_size)/2);
				// individual color data variables
				float r = 0.f, g = 0.f, b = 0.f;
				if (datamap::inMap(offset))
				{
					unsigned int data = constant->getData(offset);
					// get color and multiply by gauss blur value
					r += static_cast<float>(R(data)) * gauss[k];
					g += static_cast<float>(G(data)) * gauss[k];
					b += static_cast<float>(B(data)) * gauss[k];
				}
				sum = RGB(
							static_cast<unsigned int>(r),
							static_cast<unsigned int>(g),
							static_cast<unsigned int>(b)
										);
			}
			// write summation to the map
			draw->addData(position, sum);
		}
	}

	// passing in y direction
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			// get out local position
			vec2i position = vec2i(i, j);
			// variable for storing the summation over gauss-vektor
			unsigned int sum;
			for (int k = 0; k < gauss_size; k++)
			{
				// get offset position (local position + y-gauss-index)
				vec2i offset = position + vec2i(k - (gauss_size) / 2, 0);
				// individual color data variables
				float r = 0.f, g = 0.f, b = 0.f;
				if (datamap::inMap(offset))
				{
					unsigned int data = constant->getData(offset);
					// get color and multiply by gauss blur value
					r += static_cast<float>(R(data)) * gauss[k];
					g += static_cast<float>(G(data)) * gauss[k];
					b += static_cast<float>(B(data)) * gauss[k];
				}
				sum = RGB(
					static_cast<unsigned int>(r),
					static_cast<unsigned int>(g),
					static_cast<unsigned int>(b)
				);
			}
			// write summation to the map
			draw->addData(position, sum);
		}
	}

	// resizing the whole map
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			vec2i position = vec2i(i, j);
			draw->divData( position, 256 );
		}
	}
};
