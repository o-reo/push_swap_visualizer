#include "gui.h"
#include "utils.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <random>

Gui::Gui()
    : generateNumberSize{0}, speed{1}, state{STATE::Stopped}, scale{1.0f},
      _window{sf::VideoMode::getDesktopMode(), "Push Swap Visualizer"} {
  _window.setFramerateLimit(60);
}
Gui::~Gui() {}

std::list<int> Gui::_generateValues(const unsigned int size) {
  std::vector<int> values;
  for (unsigned int v = 1; v <= size; ++v) {
    values.push_back(v);
  }
  std::shuffle(values.begin(), values.end(),
               std::mt19937{std::random_device{}()});
  std::list<int> shuffledList;
  std::move(values.begin(), values.end(), back_inserter(shuffledList));
  return shuffledList;
}

void Gui::_updateBars() {
  this->barsA.clear();
  this->barsB.clear();
  const sf::Vector2f windowSize = this->_window.getDefaultView().getSize();
  const uint64_t queuesSize{this->queues.queueA.size() +
                            this->queues.queueB.size()};
  if (queuesSize == 0) {
    return;
  }
  const float barWidth = static_cast<float>(windowSize.y) / queuesSize;
  const float barUnit = static_cast<float>(windowSize.x) / (2 * queuesSize + 2);

  const auto updateBar = [=](std::list<int> queue,
                             std::vector<sf::RectangleShape> &bar,
                             int deltaX = 0) {
    int index{0};
    for (const int val : queue) {
      bar.push_back(
          sf::RectangleShape(sf::Vector2f((1 + val) * barUnit, barWidth)));
      bar.back().setPosition(deltaX, index * barWidth);
      bar.back().setFillColor(this->_rgb(static_cast<float>(val) / queuesSize));
      index++;
    }
  };

  updateBar(this->queues.queueA, this->barsA);
  updateBar(this->queues.queueB, this->barsB, windowSize.x / 2);
}

void Gui::_updateControls() {
  ImGui::Begin("Controls");
  ImGui::SliderInt("Speed", &this->speed, 1, 500, "%i/s");

  if (ImGui::Button("Start")) {
    this->state = STATE::Running;
  }

  ImGui::SameLine();
  if (ImGui::Button("Reverse")) {
    this->state = STATE::Reverse;
  }

  ImGui::SameLine();
  if (ImGui::Button("Pause")) {
    this->state = STATE::Stopped;
  }

  ImGui::SameLine();
  if (ImGui::Button("Step")) {
    this->state = STATE::Stopped;
    this->queues.step();
  }

  ImGui::SameLine();
  if (ImGui::Button("Step Back")) {
    this->state = STATE::Stopped;
    this->queues.stepBack();
  }

  ImGui::SliderFloat("Scale UI", &this->scale, 0.5f, 3.0f, "%.2f");
  ImGui::End();

  ImGui::Begin("Values");
  ImGui::Text("Values to generate");
  ImGui::InputInt("Count", &this->generateNumberSize);
  if (this->generateNumberSize < 0) {
    this->generateNumberSize = 0;
  }

  if (ImGui::Button("Shuffle")) {
    unsigned int size = static_cast<unsigned int>(this->generateNumberSize);
    std::list<int> valueInts = this->_generateValues(size);
    std::string values;
    for (const int value : valueInts) {
      values += std::to_string(value) + ' ';
    }
    this->numbers = values;
  }

  ImGui::Text("Space separated values");
  ImGui::InputText("Values", &this->numbers);

  ImGui::Text("push_swap file path");
  ImGui::InputText("", &this->pushswap.path);
  if (ImGui::Button("Compute")) {
    this->pushswap.run(this->numbers);
    this->state = STATE::Stopped;
    this->queues.start(Utils::SplitStringToInt(this->numbers, ' '));
    this->queues.commands = this->pushswap.commands;
    this->queues.executedCommands.clear();
  }

  std::string status{"..."};
  if (!this->pushswap.commands.empty()) {
    status = "OK";
  }
  ImGui::SameLine();
  ImGui::Text("%s", status.c_str());

  ImGui::End();

  ImGui::Begin("Commands");
  ImGui::Text("Count: %zu", this->pushswap.commands.size());
  ImGui::BeginChild("Scrolling");
  for (const auto &cmd : this->queues.commands) {
    ImGui::Text("%s", cmd.c_str());
  }
  ImGui::EndChild();
  ImGui::End();
}

void Gui::_drawBars() {
  for (const auto &shape : this->barsA) {
    this->_window.draw(shape);
  }
  for (const auto &shape : this->barsB) {
    this->_window.draw(shape);
  }
}

void Gui::_animateQueue(sf::Clock &clock) {
  float delta = clock.getElapsedTime().asSeconds();
  if (delta >= (1.0 / this->speed)) {
    clock.restart();
  }
  switch (this->state) {
  case STATE::Running: {
    int steps = static_cast<int>(delta * this->speed);
    for (int i = 0; i < steps; ++i) {
      this->queues.step();
    }
    break;
  }
  case STATE::Reverse: {
    int steps = static_cast<int>(delta * this->speed);
    for (int i = 0; i < steps; ++i) {
      this->queues.stepBack();
    }
    break;
  }
  case STATE::Stopped:
    break;
  }
}

void Gui::loop() {
  ImGui::SFML::Init(_window);

  sf::Clock deltaClock;
  sf::Clock stepClock;
  while (_window.isOpen()) {
    sf::Event event;
    while (_window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        _window.close();
      }
    }
    ImGui::GetIO().FontGlobalScale = this->scale;
    this->_updateBars();
    ImGui::SFML::Update(this->_window, deltaClock.restart());

    this->_updateControls();

    this->_animateQueue(stepClock);

    _window.clear();

    this->_drawBars();

    ImGui::SFML::Render(_window);
    _window.display();
  }
  ImGui::SFML::Shutdown();
}

sf::Color Gui::_rgb(const double ratio) {
  int normalized = static_cast<int>(ratio * 256 * 4);
  int region = normalized / 256;
  int x = normalized % 256;

  sf::Color color;
  color.a = 255;
  switch (region) {
  case 0:
    color.r = 0;
    color.g = x;
    color.b = 255;
    break;
  case 1:
    color.r = 0;
    color.g = 255;
    color.b = 255 - x;
    break;
  case 2:
    color.r = x;
    color.g = 255;
    color.b = 0;
    break;
  case 3:
    color.r = 255;
    color.g = 255 - x;
    color.b = 0;
    break;
  }
  return color;
}
