// OWN ENTITY
#include "agents.hpp"
#include "animation.hpp"
#include "main.hpp"


// globals
bool state = false;



int main()
{
    
    // SFML setup stuff
    sf::RenderWindow window(sf::VideoMode( WIDTH , HEIGHT), "hot damn!");
    window.setFramerateLimit(144);

    // make maps to hold pixel values
    datamap *map_a = new datamap();
    datamap *map_b = new datamap();
    map_a->initData("zero");
    map_b->initData("zero");

    // create vertex array
    sf::VertexArray *va = new sf::VertexArray(sf::Points, WIDTH*HEIGHT);

    // create and setup agents
    Agents ants = Agents(10000, 0x00FFFFFF);
    ants.initialize("middle");
    ants.setGroupVelocity(30.0f);
    ants.setRandomness(30.0f);
    ants.setAttraction(100.0f);

    // start the clock
    sf::Clock clk;

    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // do timing-updates
        float dt = clk.restart().sf::Time::asSeconds();
        

        // change buffers 
        // update agents
        // write onto new map
        // fade map
        // load map into vertex array
        if (state)
        {
            // B is current map, loading things into A
            ants.update(dt, map_b);
            ants.mapPositions(map_b);
            Animation::fadeMap(map_a, map_b);
            Animation::updateVertexArray(va, map_a);
            state = !state;
        }
        else
        {
            // A is current map, loading things into B
            ants.update(dt, map_a);
            ants.mapPositions(map_a);
            Animation::fadeMap(map_b, map_a);
            Animation::updateVertexArray(va, map_b);
            state = !state;
        }
        
        
        // do the window displaying stuff
        window.clear();
        window.draw(*va);
        window.display();
    }

    // delete heap stuff
    delete va;
    delete map_a;
    delete map_b;

    return 0;
}