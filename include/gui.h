#pragma once

#include "queues.h"
#include "pushswap.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Gui {
private:
    Queues queues;
    PushSwap pushswap;

    int generateNumberSize;
    std::string numbers;

    void _updateControls();
    std::list<int> _generateValues(const int size);
    std::vector<sf::RectangleShape> _updateBars();

public:
    sf::RenderWindow _window;

    Gui();
    ~Gui();

    void loop();
};
