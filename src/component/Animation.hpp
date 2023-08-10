#pragma once


#include "constants.hpp"

#include <entityx/entityx.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <cstdint>


//TODO(Tyler): Document animations better

class AnimationComponent : public entityx::Component<AnimationComponent> {
public:

  std::size_t entityName_h;
  std::size_t currentAnimID;
  
  std::vector<sf::IntRect> currentAnim;
  sf::Sprite sprite;

  int animFPS;

  sf::Clock timer;
  
  // double tick = 0.f;

  double animDT;
  
  int frameCount;
  int currentFrame;
  
  


  AnimationComponent();
  
  AnimationComponent(std::size_t animID, int fps);

  // Updates the set of animation frames
  void update(std::vector<sf::IntRect>& animFrames) {
    currentAnim = animFrames;
    frameCount = currentAnim.size();
    sprite.setTextureRect(currentAnim[0]);
    currentFrame = 0;
  }
  
  void draw(sf::RenderWindow&);

  // return true if it's time to render a new frame
  bool tick();
  
};


/*
  AnimationTrigger is used by an entity to send updated information about the entity's 
  current animation status. 
  PARSED IN: Render.cpp
*/
struct AnimationTrigger {
  entityx::ComponentHandle<AnimationComponent>& handle;
  std::size_t animID;

  bool infinite;
  bool flipped;
  
  AnimationTrigger(entityx::ComponentHandle<AnimationComponent>& h,
		   std::size_t aID,
		   bool infinite,
		   bool flip
		   ) : handle(h),
		       animID(aID),
		       infinite(infinite),
		       flipped(flip)

  {
    // if (flipped) {
    //  handle->sprite.setScale({-1, 1});
    //}
  }
  
}; 
