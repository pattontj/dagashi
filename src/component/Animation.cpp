#include "component/Animation.hpp"


AnimationComponent::AnimationComponent() {}

AnimationComponent::AnimationComponent(std::size_t animID, int fps) {

  currentAnimID = animID;
  
  //animFrames(framePositions);
  //currentAnim = animFrames[0];
  //frameCount = currentAnim.size();
  animFPS = fps;
  animDT = 1.f/(double)animFPS; // 24 over 
  //sprite.setTextureRect(currentAnim[0]);
  timer.restart();

  currentFrame = 0;

  //update();
  
  std::cout << /* "frameCount: " << frameCount << */ " FPS: " << engine::FPS << std::endl;
 
}




void AnimationComponent::draw(sf::RenderWindow& window) {
  //std::cout << "timer: " << timer.getElapsedTime().asSeconds() << std::endl;
  window.draw(sprite);
  tick();

  // This calls every update, so it's working
  //std::cout << "drawing animationComponent" << std::endl;
      
}

// return true if it's time to render a new frame
bool AnimationComponent::tick() {
  //std::cout << "timer: " << timer.getElapsedTime().asSeconds() << std::endl;
  
   if (timer.getElapsedTime().asSeconds() > animDT) {
     timer.restart();

     currentFrame++;

     //std::cout << "currentFrame: " << currentFrame << std::endl;
     
     if (currentFrame >= frameCount)
       currentFrame = 0;

     sprite.setTextureRect(currentAnim[currentFrame]);
   }
}
 
