#pragma once
#include "config.hpp"
#include "component/Velocity.hpp"


#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>


const float PLAYER_SPEED = 8.f;

class InputSystem : public entityx::System<InputSystem>{
  frame_t frame = 0;
public:
  InputSystem();

  // Takes keyboard input for player movement + other things eventually
  void update(entityx::EntityManager &, entityx::EventManager &, entityx::TimeDelta) override;
};
