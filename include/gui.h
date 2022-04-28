#pragma once

#include "pushswap.h"
#include "queues.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <list>
#include <string>
#include <vector>

class Gui {
private:
  enum class STATE {Running, Reverse, Stopped};
  Queues queues;
  PushSwap pushswap;

  std::vector<sf::RectangleShape> barsA;
  std::vector<sf::RectangleShape> barsB;
  int generateNumberSize;
  std::string numbers;
  int speed;
  STATE state;
  float scale;

  void _updateControls();
  void _drawBars();
  void _animateQueue(sf::Clock &clock);
  std::list<int> _generateValues(const unsigned int size);
  void _updateBars();
  sf::Color _rgb(const double ratio);

public:
  sf::RenderWindow _window;

  Gui();
  ~Gui();

  void loop();
};
