#pragma once

// SFML
#include "SFML/Graphics.hpp"


// STD
#include <vector>
#include <iostream>
#include <string>


// DEFINES LOGS
#define LOG(x) std::cout << #x << " = " << x << std::endl;
#define LOGS(x, y) std::cout << x << " = " << y << std::endl;
#define LOGRAW(x) std::cout << "\n\n" << x << std::endl;
#define LOGTYPE(x) std::cout << #x << " type is: " << typeid(x).name() << std::endl;



// DEFINES CONSTS
#define WIDTH 1000
#define HEIGHT 500

#define RGB(r,g,b) ( ((r & 0xFF)<<16) | ((g & 0xFF)<<8) | (b & 0xFF) )
#define R(x) (x & 0x00FF0000) >> 16
#define G(x) (x & 0x0000FF00) >> 8
#define B(x) (x & 0x000000FF)



struct vec2i
{
    int x;
    int y;

    vec2i()
    {
        x = 0;
        y = 0;
    }
    vec2i(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    vec2i operator+(const vec2i foo) const
    {
        vec2i v = foo;
        v.x += x;
        v.y += y;
        return v;
    }
};

struct vec2f
{
    float x;
    float y;

    vec2f()
    {
        x = 0;
        y = 0;
    };
    vec2f(float _x, float _y)
    {
        x = _x;
        y = _y;
    }; 
    float abs()
    {
        return (x * x) + (y * y);
    };
    vec2f right()
    {
        vec2f v;
        v.x = y;
        v.y = -x;
        return v;
    };
    vec2f left()
    {
        vec2f v;
        v.x = -y;
        v.y = x;
        return v;
    };

    vec2f operator+(const vec2f foo) const
    {
        vec2f v = foo;
        v.x += x;
        v.y += y;
        return v;
    };
    vec2f operator*(const float a) const
    {
        vec2f v;
        v.x = x * a;
        v.y = y * a;
        return v;
    };
};


struct datamap
{
    unsigned int* data = new unsigned int[WIDTH * HEIGHT];

    datamap()
    {
        initData("zero");
    };

    ~datamap()
    {
        delete[] data;
    };

    // return data at i
    unsigned int getData( int i)
    {
        if ( inMap(i) )
            return data[i];
        return 0;
    };

    // return data at x,y 
    unsigned int getData( vec2i v)
    {
        if ( inMap(v) )
            return data[v.x + (WIDTH*v.y)];
        return 0;
    };

    // set data at x,y to value
    void setData(vec2i v, unsigned int value)
    {
        if ( inMap(v) )
            data[v.x + (WIDTH*v.y)] = value;
    };
    void addData(vec2i v, unsigned int value)
    {
        if (inMap(v))
            data[v.x + (WIDTH * v.y)] += value;
    };
    void divData(vec2i v, unsigned int value)
    {
        if (inMap(v))
            data[v.x + (WIDTH * v.y)] /= value;
    };


    // set all data: "zero", "random", "bright"
    void initData(std::string s)
    {
        if (s == "zero")
        {
            for (int i = 0; i < WIDTH*HEIGHT; i++)
                data[i] = 0;
        }
        if (s == "random")
        {
            for (int i = 0; i < WIDTH * HEIGHT; i++)
                data[i] = rand()%255;
        }
        if (s == "bright")
        {
            for (int i = 0; i < WIDTH * HEIGHT; i++)
                data[i] = 255;
        }
    };

    static bool inMap(vec2i v)
    {
        if ((v.x >= 0) &&
            (v.x < WIDTH) &&
            (v.y >= 0) &&
            (v.y < HEIGHT))
        {
            return true;
        }
        return false;
    };

    static bool inMap(int i)
    {
        if ( (i >= 0) && (i < WIDTH*HEIGHT) )
        {
            return true;
        }
        return false;
    };
};