#pragma once

#include "constants.hpp"

#include "component/Animation.hpp"

#include <entityx/entityx.h>

#include <SFML/Graphics.hpp>



class RenderSystem : public entityx::System<RenderSystem>, public entityx::Receiver<RenderSystem>{
public:
  sf::RenderWindow* window_ptr = nullptr;
  entityx::EntityX* ex_ptr = nullptr;

  // Have the system hold all the textures here
  std::shared_ptr<sf::Texture> animationTexture;

  // Hashed strings are keys, all hashes exist #define'd in constants
  std::unordered_map<std::size_t, std::vector<sf::IntRect>> animationFrames;
  
  
  RenderSystem();
  RenderSystem(sf::RenderWindow& window, entityx::EntityX& ex);
  ~RenderSystem();  

  void configure(entityx::EventManager& eventManager) override;

  // Init animations gets called after configure, and emits a trigger to start the animations
  void initAnimations();
  
  void receive(const AnimationTrigger& animationTrigger);

  
  void update(entityx::EntityManager &ex, entityx::EventManager &events, entityx::TimeDelta dt) override;

  // All animation frames are defined here
  void registerAnimationFrames();

};
