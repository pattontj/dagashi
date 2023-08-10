#include "Physics.hpp"

#include "component/Transform.hpp"
#include "component/Collider.hpp"
#include "component/Camera.hpp"
#include "MapManager.hpp"
#include "system/Input.hpp"

PhysicsSystem::PhysicsSystem(){}

void PhysicsSystem::update(entityx::EntityManager& ex, entityx::EventManager&, entityx::TimeDelta) {

  entityx::ComponentHandle<CameraComponent> view_h;
  entityx::ComponentHandle<LevelMapComponent> level_h;

  /*
  /* In theory this should only run once, even if N^2 runtime complexity 
  for (entityx::Entity view : ex.entities_with_components(view_h)) {
    for (entityx::Entity level : ex.entities_with_components(level_h)) {
      for (auto chunkVec : level_h->chunks) {
	for (auto chunk : chunkVec) {
	  if (view_h->camera.getPixelBounds().intersects(chunk.)) {
	    std::cout << "" << std::endl;
	  }
        }
      } 
    }
  }
  */
  entityx::ComponentHandle<ColliderComponent> left, right;
  for (entityx::Entity leftEntity : ex.entities_with_components(left)) {
    for (entityx::Entity rightEntity : ex.entities_with_components(right)) {
      if (left->collider.getGlobalBounds() != right->collider.getGlobalBounds()) {
        sf::FloatRect result;
        if ( left->collider.getGlobalBounds().intersects(right->collider.getGlobalBounds(), result) ) {
          if (left->collisionLevel < CollisionLevel::WALL) {
            auto left_t = leftEntity.component<TransformComponent>();
            if (left_t) {
              //Determine collision direction!
              Direction::Type leftFacing;
              if (result.width > result.height) {
               
                if (left->collider.getPosition().y >
                  right->collider.getPosition().y + (right->collider.getSize().y/2))
                {
                  leftFacing = Direction::UP;
                }
                else {
                  // std::cout << "Colling from TOP!" << std::endl;
                  leftFacing = Direction::DOWN;
                }
              }
              else if (result.width < result.height) {
                // std::cout << "Colliding from X axis" << std::endl;
                if (left->collider.getPosition().x > right->collider.getPosition().x+(right->collider.getSize().x/2)) {
                  // std::cout << "Colling from LEFT!" << std::endl;
                  leftFacing = Direction::LEFT;
                }
                else {
                  // std::cout << "Colling from RIGHT!" << std::endl;
                  leftFacing = Direction::RIGHT;
                }
              }
              // GET PURE INTERSECTION RECT
              sf::Vector2f dimensions((result.width-result.left), (result.height-result.top));
              sf::FloatRect pureIntersection(sf::Vector2f(0,0), dimensions);


              //left_t->position.x = result.left+1;
              //left_t->position.y = result.top+1;

              switch(leftFacing) {
              case Direction::UP:
                left_t->position.y += result.height;
                // std::cout<<"UP:  "<<left_t->position.y<<std::endl;
                break;

              case Direction::DOWN:
                left_t->position.y -= result.height;
                // std::cout<<"DOWN:"<<left_t->position.y<<std::endl;
                break;

              case Direction::LEFT:
                left_t->position.x += result.width;
                // std::cout<<"LEFT:"<<left_t->position.x<<std::endl;
                break;

              case Direction::RIGHT:
                left_t->position.x -= result.width;
                // std::cout<<"RGHT:"<<left_t->position.x<<std::endl;
                break;
              }
              left->collider.setPosition(left_t->position);
            }
          }
          else {
          }
        }
      }
    }
  }
}
