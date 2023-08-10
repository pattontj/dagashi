#include "system/Input.hpp"

#include "component/Player.hpp"
#include "component/Velocity.hpp"
#include "component/Transform.hpp"
#include "component/Animation.hpp"

#include <entityx/entityx.h>


InputSystem::InputSystem(){}

void InputSystem::update(entityx::EntityManager &entities, entityx::EventManager& events, entityx::TimeDelta dt) {
  sf::Vector2f v;
  v.x = (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    - (sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
  v.y = (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    - (sf::Keyboard::isKeyPressed(sf::Keyboard::Up));

  v*=PLAYER_SPEED*(float)dt;
    
  entities.each<PlayerComponent, VelocityComponent>(
			   [v](entityx::Entity, PlayerComponent &, VelocityComponent &velocity) {
			       velocity.velocity = v; });

  entities.each<PlayerComponent,
		VelocityComponent,
		TransformComponent,
		AnimationComponent>(
				    [&events](entityx::Entity e,
					      PlayerComponent& pc,
					      VelocityComponent& vc,
					      TransformComponent& tc,
					      AnimationComponent& ac) {

				      tc.position += vc.velocity;
				  
				      auto anim_h = e.component<AnimationComponent>();

				  
				      if (vc.velocity.x > 0) {
					events.emit<AnimationTrigger>(anim_h,
								      animation::player::WALK_RIGHT,
								      false,
								      false
								      );
				      }
				      else if (vc.velocity.x < 0) {
					events.emit<AnimationTrigger>(anim_h,
								      animation::player::WALK_LEFT,
								      false,
								      true
								      );
				      }
				      else {

					// TODO(Tyler): Handle vertical movement animation
					
					if (pc.previousNonZeroVelocity.x > 0) {
					  events.emit<AnimationTrigger>(anim_h,
									animation::player::IDLE_RIGHT,
									false,
									true
									);
					}
					else if (pc.previousNonZeroVelocity.x < 0) {
					  events.emit<AnimationTrigger>(anim_h,
									animation::player::IDLE_LEFT,
									false,
									true
									);
					}


 
				      }

				      if (vc.velocity.x != 0) {
					pc.previousNonZeroVelocity = vc.velocity; 
				      }
				    });

}
				    
				    
