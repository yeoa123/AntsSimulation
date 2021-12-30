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
			// variables for storing the summation over gauss-vektor
			float r = 0.f, g = 0.f, b = 0.f;
			for (int k = 0; k < gauss_size; k++)
			{
				// get offset position (local position + x-gauss-index)
				vec2i offset = position + vec2i(0, k-(gauss_size-1)/2);
				unsigned int data = constant->getData(offset);
				// get color and multiply by gauss blur value
				r += static_cast<float>(R(data)) * gauss[k] / gauss_faktor;
				g += static_cast<float>(G(data)) * gauss[k] / gauss_faktor;
				b += static_cast<float>(B(data)) * gauss[k] / gauss_faktor;	
			}
			unsigned int sum = RGB(
						static_cast<unsigned int>(r),
						static_cast<unsigned int>(g),
						static_cast<unsigned int>(b)
									);
			// write summation to the map
			draw->setData(position, sum);
		}
	}

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
			float r = 0.f, g = 0.f, b = 0.f;
			for (int k = 0; k < gauss_size; k++)
			{
				// get offset position (local position + x-gauss-index)
				vec2i offset = position + vec2i(k - (gauss_size-1) / 2, 0);
				unsigned int data = constant->getData(offset);
				// get color and multiply by gauss blur value
				r += static_cast<float>(R(data)) * gauss[k] / gauss_faktor;
				g += static_cast<float>(G(data)) * gauss[k] / gauss_faktor;
				b += static_cast<float>(B(data)) * gauss[k] / gauss_faktor;
			}
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
