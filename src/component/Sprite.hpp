#pragma once
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

#include <iostream>

struct SpriteComponent : public entityx::Component<SpriteComponent> {
  sf::Sprite sprite;
  bool disabled = false;
  SpriteComponent() {
    std::cout << "Error: SpriteComponent called with no arguements, improperly initialized" << std::endl;
  }
  SpriteComponent(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture, sf::IntRect texLocation,
		  bool disable = false) : sprite(sf::Sprite(texture, texLocation)) , disabled(disable) {

    sprite.setPosition(position);
    
  };

  void draw(sf::RenderWindow& window) {
    if (!disabled)
      window.draw(sprite);
  }
};

