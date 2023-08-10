#pragma once

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

#include "component/Sprite.hpp"
#include "component/Transform.hpp"
#include "component/Velocity.hpp"
#include "component/Player.hpp"
#include "component/Camera.hpp"
#include "component/Collider.hpp"
#include "component/Animation.hpp"

#include "system/Physics.hpp"

#include "constants.hpp"

#include <iostream>


namespace Factory {
  void createPlayer(entityx::EntityX& ex, sf::RenderWindow& window, sf::Vector2f position,
		    std::shared_ptr<sf::Texture> tex, bool startInvisible = false) {
    auto player = ex.entities.create();

    player.assign<TransformComponent>(position, false);
    player.assign<VelocityComponent>();

    // final bool is to start invisible
    player.assign<SpriteComponent>(position, sf::Vector2f(16.f,16.f),
				   *tex.get(), sf::IntRect(0, 0, 16, 16), true);

    

    
    std::cout << "test" << std::endl;
    player.assign<AnimationComponent>(animation::player::IDLE_RIGHT, 12);
    
    player.assign<PlayerComponent>();
    

    player.assign<CameraComponent>(window);
    player.assign<ColliderComponent>(sf::FloatRect(position, sf::Vector2f(16,16)),
				     CollisionLevel::PLAYER);

    ex.entities.each<PlayerComponent,
		     TransformComponent,
		     CameraComponent>(
				      [](entityx::Entity e,
					 PlayerComponent& pc,
					 TransformComponent& tc,
					 CameraComponent& cc){
					//cc.camera.setSize(600, 400);
					//cc.camera.zoom(5.f);
					cc.camera.setCenter(tc.position);
					
					std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
				      });
    
    
  }
}
