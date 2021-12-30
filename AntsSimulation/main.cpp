// OWN ENTITY
#include "agents.hpp"
#include "animation.hpp"
#include "main.hpp"


// globals
bool state = false;


int main()
{
    // SFML TEXT-DEBUG EXAMPLE
    /*
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("ArialCE.ttf"))
    {
        std::cout << "error" << std::endl;
    }
    text.setFont(font);

    sf::VertexArray dp = sf::VertexArray::VertexArray(sf::Points, 1);
    dp[0] = sf::Vertex::Vertex(sf::Vector2f(), sf::Color::Blue);
    vec2f p = ants.debuggyPosition();
    dp[0] = sf::Vertex::Vertex(sf::Vector2f(p.x, p.y), sf::Color::Red);

    std::string s = std::to_string(p.x) + "  :  " + std::to_string(p.y);

    text.setString(s);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    */
    

    
    // SFML setup stuff
    sf::RenderWindow window(sf::VideoMode( WIDTH , HEIGHT), "hot damn!");
    window.setFramerateLimit(144);
    sf::Clock clk;

    // make maps to hold pixel values
    datamap *map_a = new datamap();
    datamap *map_b = new datamap();
    map_a->initData("zero");
    map_b->initData("zero");

    // create vertex array
    sf::VertexArray *va = new sf::VertexArray(sf::Points, WIDTH*HEIGHT);

    // create and setup agents
    Agents ants1 = Agents(1, 0x00FFFFFF);
    ants1.initialize("random");

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
            ants1.update(dt, map_b);
            ants1.mapPositions(map_b);
            Animation::fadeMap(map_a, map_b);
            Animation::updateVertexArray(va, map_a);
            state = !state;
        }
        else
        {
            // A is current map, loading things into B
            ants1.update(dt, map_a);
            ants1.mapPositions(map_a);
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