#include "world/World.hpp"


World::World(sf::RenderWindow& w, std::string levelName) {
  window = &w;
  level = Level(levelName, *this, w);
}



void World::TriggerMenuState() {
  
}
