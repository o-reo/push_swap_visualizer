#include "queues.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Gui {
private:
    Queues queues;
    int generateNumberSize;
    char valueString[1024*16];

    void _updateControls();
    std::list<int> _generateValues(const int size);
    std::vector<sf::RectangleShape> _updateBars();

public:
    sf::RenderWindow _window;

    Gui();
    ~Gui();

    void loop();
};
