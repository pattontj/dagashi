#pragma once

#include "constants.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <unordered_map>
#include <string>

namespace engine {
  const int FPS = 60;
};

// animation holds onto hashed animation names of all entities and some utils.
namespace animation {
  const int MAX_FRAMES = 128; // 2048/16 = 128, if animations are given their own rows 

  const int MASTER_ATLAS_SIZE = 2048; // 2048x2048

  
  /* Defines a horizontal strip of animation frames. 'begin' and 'end' must be on
     the same y value. 
     NOTE: Uses the width and height of begin for calcluations 
  */
  std::vector<sf::IntRect> defHorizontalAnimFrames(sf::IntRect begin, sf::IntRect end);

  // Player animation names
  namespace player {
    extern std::size_t IDLE_LEFT;
    extern std::size_t IDLE_RIGHT;
    extern std::size_t WALK_UP;
    extern std::size_t WALK_DOWN;
    extern std::size_t WALK_LEFT;
    extern std::size_t WALK_RIGHT;
  };

  namespace ResourceManager {

    

  }

};

