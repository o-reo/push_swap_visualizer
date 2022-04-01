#pragma once

#include "queues.h"
#include "pushswap.h"
#include <vector>
#include <string>
#include <list>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Gui {
private:
    Queues queues;
    PushSwap pushswap;

    std::vector<sf::RectangleShape> barsA;
    std::vector<sf::RectangleShape> barsB;
    int generateNumberSize;
    std::string numbers;
    int speed;
    bool running;

    std::list<int> _split(const std::string &, char);
    void _updateControls();
    std::list<int> _generateValues(const int size);
    void _updateBars();
    sf::Color _rgb(const double ratio);

public:
    sf::RenderWindow _window;

    Gui();
    ~Gui();

    void loop();
};
