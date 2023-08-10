#pragma once

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

class CameraComponent : public entityx::Component<CameraComponent> {
public:
  sf::View camera;
  CameraComponent(){}
  CameraComponent(sf::RenderWindow& window) {
    camera.zoom(2.f);
    camera.setSize(sf::Vector2f(300, 200));
    camera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    camera.setCenter(sf::Vector2f(0, 0));
    //window.setView(camera);
  }

  sf::FloatRect getPixelBounds() {
    sf::Vector2f v(camera.getCenter().x,
		   camera.getCenter().y);
    return sf::FloatRect(v, camera.getSize());
  }
};
