#pragma once

#include <SFML/Graphics.hpp>
#include <tmxlite/Types.hpp>

#include <cstdint>

//Convert TMX vectors to SF vecs
sf::Vector2i tmxToSF(const tmx::Vector2i& vec) {
  return sf::Vector2i(vec.x, vec.y);
}


sf::Vector2f tmxToSF(const tmx::Vector2f& vec) {
  return sf::Vector2f(vec.x, vec.y);
}


sf::Vector2u tmxToSF(const tmx::Vector2u& vec) {
  return sf::Vector2u(vec.x, vec.y);
}

sf::FloatRect tmxToSF(tmx::FloatRect box) {
  return sf::FloatRect(box.left, box.top, box.width, box.height);
}

uint32_t indexInto(uint32_t x, uint32_t y, uint32_t arrWidth) {
  return x+y*arrWidth;
}
