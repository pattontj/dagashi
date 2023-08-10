#pragma once


#include "MapManager.hpp"
#include <entityx/entityx.h>

#include <SFML/Graphics.hpp>


class Pause {
public:
  bool isPaused = false;
  Pause(bool isPaused): isPaused(isPaused) {}
};


class World : public entityx::EntityX {
public:

  sf::RenderWindow* window = nullptr;
  Level level;
  
  bool isPaused = false;
  
  virtual bool init() = 0;

  virtual void update() = 0;

  virtual void draw() = 0;

  void PauseWorld();

  void TriggerMenuState();
  
  explicit World(sf::RenderWindow& w, std::string levelName);
  
};
