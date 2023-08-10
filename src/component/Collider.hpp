#pragma once

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

#include "system/Physics.hpp"

class ColliderComponent : public entityx::Component<ColliderComponent>  {
public:
  //sf::FloatRect collider;
  sf::RectangleShape collider;
  CollisionLevel::Type collisionLevel = CollisionLevel::GHOST;

  ColliderComponent() {
  }
  ColliderComponent(sf::FloatRect col, CollisionLevel::Type level) {
    collider.setPosition(col.left, col.top);
    collider.setSize(sf::Vector2f(col.width, col.height));
    
    collisionLevel = level;
  }
};
