// Copyright 2022  Emmanuel Ruaud
#include "gui.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <random>
#include <sstream>

std::list<int> Gui::_generateValues(const int size) {
  if (size <= 0) {
    return {};
  }

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
  this->barsA = {};
  this->barsB = {};
  const auto windowSize = this->_window.getSize();
  const uint64_t queuesSize{this->queues.queueA.size() +
                            this->queues.queueB.size()};
  if (queuesSize == 0) {
    return;
  }
  const float barWidth = static_cast<float>(windowSize.y) / queuesSize;
  const float barUnit = static_cast<float>(windowSize.x) / (2 * queuesSize - 2);

  int index{0};
  for (const int valA : this->queues.queueA) {
    this->barsA.push_back(
        sf::RectangleShape(sf::Vector2f((1 + valA) * barUnit, barWidth)));
    this->barsA.back().setPosition(0, index * barWidth);
    this->barsA.back().setFillColor(
        this->_rgb(static_cast<float>(valA) / queuesSize));
    index++;
  }
  index = 0;
  for (const int valB : this->queues.queueB) {
    this->barsB.push_back(
        sf::RectangleShape(sf::Vector2f((1 + valB) * barUnit, barWidth)));
    this->barsB.back().setPosition(windowSize.x / 2, index * barWidth);
    this->barsB.back().setFillColor(
        this->_rgb(static_cast<float>(valB) / queuesSize));
    index++;
  }
}

std::list<int> Gui::_split(const std::string &s, const char delimitor) {
  std::stringstream ss(s);
  std::string item;
  std::list<int> elems;
  while (std::getline(ss, item, delimitor)) {
    elems.push_back(std::stoi(item));
  }
  return elems;
}

void Gui::_updateControls() {
  ImGui::Begin("Controls");
  ImGui::SliderInt("Speed", &this->speed, 1, 240, "%i/s");

  if (ImGui::Button("Load")) {
    this->running = false;
    this->queues.start(this->_split(this->numbers, ' '));
    this->queues.commands = this->pushswap.commands;
  }

  ImGui::SameLine();
  if (ImGui::Button("Start")) {
    this->running = true;
  }

  ImGui::SameLine();
  if (ImGui::Button("Pause")) {
    this->running = false;
  }

  ImGui::SameLine();
  if (ImGui::Button("Step")) {
    this->queues.step();
  }
  ImGui::End();

  ImGui::Begin("Values");
  ImGui::Text("Values to generate");
  ImGui::InputInt("Count", &this->generateNumberSize);

  if (ImGui::Button("Shuffle")) {
    std::list<int> valueInts = this->_generateValues(this->generateNumberSize);
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
  }

  std::string status{"..."};
  if (!this->pushswap.commands.empty()) {
    status = "OK";
  }
  ImGui::SameLine();
  ImGui::Text(status.c_str());

  ImGui::End();

  ImGui::Begin("Commands");
  for (const auto &cmd : this->queues.commands) {
    ImGui::Text(cmd.c_str());
  }
  ImGui::End();
}

Gui::Gui()
    : _window{sf::VideoMode::getDesktopMode(), "Push Swap Visualizer"},
      generateNumberSize{0}, speed{1}, running{false} {
  _window.setFramerateLimit(60);
  ImGui::SFML::Init(_window);
}

void Gui::loop() {
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

    this->_updateBars();

    ImGui::SFML::Update(_window, deltaClock.restart());

    this->_updateControls();

    float delta = stepClock.getElapsedTime().asSeconds();
    if (delta >= (1.0 / this->speed)) {
        stepClock.restart();
    }
    if (this->running) {
      int steps = static_cast<int>(delta * this->speed);
      for (int i = 0; i < steps; ++i) {
        this->queues.step();
      }
    }

    _window.clear();

    for (const auto &shape : this->barsA) {
      _window.draw(shape);
    }
    for (const auto &shape : this->barsB) {
      _window.draw(shape);
    }

    ImGui::SFML::Render(_window);
    _window.display();
  }
  ImGui::SFML::Shutdown();
}

Gui::~Gui() {}

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
