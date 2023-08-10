#include "constants.hpp"

#include <cassert>

#include <cmath>

namespace animation {
  namespace player {
    std::size_t IDLE_LEFT = std::hash<std::string>{}(std::string("player_idle_left"));
    std::size_t IDLE_RIGHT = std::hash<std::string>{}(std::string("player_idle_right"));
    std::size_t WALK_UP = std::hash<std::string>{}(std::string("player_walk_up"));;
    std::size_t WALK_DOWN = std::hash<std::string>{}(std::string("player_walk_down"));;
    std::size_t WALK_LEFT = std::hash<std::string>{}(std::string("player_walk_left"));;
    std::size_t WALK_RIGHT = std::hash<std::string>{}(std::string("player_walk_right"));

  };
};



std::vector<sf::IntRect> animation::defHorizontalAnimFrames(sf::IntRect begin, sf::IntRect end) {
  int beginX = begin.left, beginY = begin.top;
  int endX = end.left, endY = end.top;

  std::vector<sf::IntRect> frames;
  
  for (int i = beginX; i <= endX; i+=abs(begin.width)) {
    int flipCompensation = 0;
    if (begin.width < 0)
      flipCompensation = abs(begin.width);
    
    frames.push_back( sf::IntRect(i+flipCompensation, beginY, begin.width, begin.height) );
  }
  return frames;
}
