#pragma once
#include <entityx/entityx.h>
#include "Sprite.hpp"

#include "constants.hpp"

struct PlayerComponent : public entityx::Component<PlayerComponent>{
  entityx::ComponentHandle<SpriteComponent> button_prompt;

  std::size_t animationState = animation::player::IDLE_RIGHT;  
  

  sf::Vector2f previousNonZeroVelocity;
  
  

  PlayerComponent(){
    previousNonZeroVelocity = sf::Vector2f(1.f,0.f);
  }
};
