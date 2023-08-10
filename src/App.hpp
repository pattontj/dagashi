#pragma once
#include "config.hpp"
#include "component/Transform.hpp"

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

class App : public entityx::EntityX{
    sf::RenderWindow &window;
    //sf::Texture atlas;

  sf::Font dbgFont;
  sf::Text fpsText;
  

public:
    bool is_open = true;

    App(sf::RenderWindow &);
    void update(entityx::TimeDelta delta);
    void event(sf::Event const &event);

  void draw();
};
