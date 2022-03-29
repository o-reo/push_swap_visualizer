#include "gui.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

std::vector<sf::CircleShape> Gui::updateBars() {
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    return std::vector<sf::CircleShape>{shape};
}

void Gui::updateControls() {
    ImGui::Begin("Controls");
    int speed{1};
    ImGui::SliderInt("Speed", &speed, 1, 60, "%i/s");
    ImGui::Button("Run");
    ImGui::SameLine();
    ImGui::Button("Pause");
    ImGui::SameLine();
    ImGui::Button("Reset");
    ImGui::End();

    ImGui::Begin("Values");
    ImGui::Text("Values to generate");
    int generateNumberCount = 0;
    ImGui::InputInt("Count", &generateNumberCount);

    if (ImGui::Button("Shuffle")) {
    }

    ImGui::Text("Space separated values");
    char values[1024*16];
    ImGui::InputTextMultiline("Values", values, IM_ARRAYSIZE(values), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16));

    ImGui::Text("push_swap file path");
    char path[256]{"./push_swap"};
    ImGui::InputText("", path, IM_ARRAYSIZE(path));
    ImGui::Button("Compute");
    ImGui::End();

    ImGui::Begin("Commands");
    ImGui::Text("pa");
    ImGui::End();
}

Gui::Gui() : _window(sf::VideoMode::getDesktopMode(),
                          "Push Swap Visualizer"){
  _window.setFramerateLimit(60);
  ImGui::SFML::Init(_window);
}

void Gui::loop() {
  sf::Clock deltaClock;
  while (_window.isOpen()) {
    sf::Event event;
    while (_window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        _window.close();
      }
    }

    const std::vector<sf::CircleShape> shapes = this->updateBars();
    ImGui::SFML::Update(_window, deltaClock.restart());

    this->updateControls();

    _window.clear();

    for (const auto &shape : shapes) {
        _window.draw(shape);
    }

    ImGui::SFML::Render(_window);
    _window.display();
  }
}

Gui::~Gui() {
  ImGui::SFML::Shutdown();
}
