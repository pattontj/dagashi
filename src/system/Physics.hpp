#pragma once

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>




namespace Direction {
  enum Type {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
  };
};


/*
  GHOST  = Move through everything
  ENTITY = General entity, collides with everything below
  PLAYER = player, collides with entity and below
  WALL   = Absoloute position, cannot be moved

*/
namespace CollisionLevel {
  enum Type {
    GHOST = 0,
    ENTITY,
    PLAYER,
    WALL,
  };
};


class PhysicsSystem : public entityx::System<PhysicsSystem>{
public:
  PhysicsSystem();
  void update(entityx::EntityManager &, entityx::EventManager &, entityx::TimeDelta) override;
};
