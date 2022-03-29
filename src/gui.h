#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <memory>

class Gui {
public:
  Gui();
  ~Gui();

  void loop();
  void updateControls();
  std::vector<sf::CircleShape> updateBars();

  sf::RenderWindow _window;
};
