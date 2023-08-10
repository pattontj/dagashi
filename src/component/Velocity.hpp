#pragma once
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

#include <iostream>

struct VelocityComponent : public entityx::Component<VelocityComponent>{
public:
  sf::Vector2f velocity;
  VelocityComponent() {
    //std::cout << "Error: VelocityComponent " << std::endl;
  }
  VelocityComponent(sf::Vector2f velocity);
  
};
