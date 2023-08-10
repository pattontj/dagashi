#include "system/Render.hpp"

#include "component/Sprite.hpp"
#include "MapManager.hpp"

#include "system/Input.hpp"

#include <iostream>


void RenderSystem::configure(entityx::EventManager& eventManager) {
  eventManager.subscribe<AnimationTrigger>(*this);
}


void RenderSystem::initAnimations() {
  ex_ptr->entities.each<AnimationComponent>([this](entityx::Entity e,
						   AnimationComponent& ac){

					      // TODO(Tyler): Try the flipped ARG with the component's flag maybe
			entityx::ComponentHandle<AnimationComponent> ac_h = e.component<AnimationComponent>();
			ex_ptr->events.emit<AnimationTrigger>(ac_h, ac.currentAnimID, false, false);
					 
					    });
}

void RenderSystem::receive(const AnimationTrigger& animationTrigger) {
  auto anim_h = animationTrigger.handle;
  if (anim_h->currentAnimID != animationTrigger.animID) {
    anim_h->currentAnimID = animationTrigger.animID;

    anim_h->currentAnim = animationFrames[anim_h->currentAnimID];

    anim_h->currentFrame = 0;
  
    anim_h->sprite.setTextureRect(anim_h->currentAnim[anim_h->currentFrame]);

    anim_h->frameCount = anim_h->currentAnim.size();

    /*
    std::cout << "animID: " << anim_h->currentAnimID << std::endl;
    std::cout << "textureRect dimensions: x y w h = "
	      << anim_h->currentAnim[anim_h->currentFrame].left << " "
	      << anim_h->currentAnim[anim_h->currentFrame].top << " "
	      << anim_h->currentAnim[anim_h->currentFrame].width << " "
	      << anim_h->currentAnim[anim_h->currentFrame].height << " "
	      << std::endl;

    std::cout << "frameCount: " << anim_h->frameCount << std::endl;
    */
    anim_h->timer.restart();
  }
  
}


void RenderSystem::update(entityx::EntityManager& entities, entityx::EventManager&, entityx::TimeDelta) {

  if (!window_ptr || !ex_ptr) {
    std::cout << "Error: Window and or entityx pointer is null!" << std::endl;
  }
  else {

    entities.each<LevelMapComponent>([this](entityx::Entity entity, LevelMapComponent& level) {
	level.draw(*window_ptr, *ex_ptr);
      });
    
    
    entities.each<SpriteComponent>([this](entityx::Entity ent,
					  SpriteComponent sc) mutable {
				     sc.draw(*window_ptr);
				   });


    entities.each<AnimationComponent>([this](entityx::Entity ent,
					  AnimationComponent& ac) {
				     ac.draw(*window_ptr);
				   });
    

  }
}

RenderSystem::RenderSystem() {
  std::cout << "Error: enderSystem initialized without pointer to window!" << std::endl;
}

RenderSystem::RenderSystem(sf::RenderWindow& window, entityx::EntityX& ex) {
  window_ptr = &window;
  ex_ptr = &ex;

  animationTexture = std::make_shared<sf::Texture>();
  auto atlasPath = "resources/masterAtlas.png";
  if (!animationTexture->loadFromFile(atlasPath)) {
    std::cout << "Failed to load " << atlasPath << std::endl;
  }

  registerAnimationFrames();

  
  ex.entities.each<AnimationComponent>([&ex, this](entityx::Entity e,
					      AnimationComponent& ac){
					 if (ac.sprite.getTexture() == nullptr) {
					   //sf::Texture* t = animationTexture.get();
					   ac.sprite.setTexture(*animationTexture.get());
					 }
					 
					 ac.currentAnim = animationFrames[ac.currentAnimID];
					 ac.frameCount = ac.currentAnim.size();

					 ac.sprite.setTextureRect(ac.currentAnim[ac.currentFrame]);

			  entityx::ComponentHandle<AnimationComponent> ac_h = e.component<AnimationComponent>();
			  ex.events.emit<AnimationTrigger>(ac_h, ac.currentAnimID, true, false);
					 
				       });

}

RenderSystem::~RenderSystem() {
  if (window_ptr)
    window_ptr = nullptr;
  if (ex_ptr)
    ex_ptr = nullptr;
}

/*
void RenderSystem::debugDisplayAnimSheet(std::size_t animID) {
window_ptr->draw();
}
*/

void RenderSystem::registerAnimationFrames() {


  animationFrames.insert(std::make_pair(animation::player::IDLE_LEFT,
					animation::defHorizontalAnimFrames(sf::IntRect(0,0,-16,16),
									   sf::IntRect(144,0,-16,16)
									   )
					));
  
  // 16x10 = 160
  animationFrames.insert(std::make_pair(animation::player::IDLE_RIGHT,
					animation::defHorizontalAnimFrames(sf::IntRect(0,0,16,16),
									   sf::IntRect(144,0,16,16)
									   )
					));

  // 16x6 = 96
  animationFrames.insert(std::make_pair(animation::player::WALK_RIGHT,
					animation::defHorizontalAnimFrames(sf::IntRect(0,16,16,16),
									   sf::IntRect(80,16,16,16)
									   )
					));

  animationFrames.insert(std::make_pair(animation::player::WALK_LEFT,
					animation::defHorizontalAnimFrames(sf::IntRect(0,16,-16,16),
									   sf::IntRect(80,16,-16,16)
									   )
					));


  auto v = 	animation::defHorizontalAnimFrames(sf::IntRect(0,16,-16,16),
						   sf::IntRect(80,16,-16,16)
						   );


  for (auto f : v)
    std::cout << "x: " << f.left << " y: " << f.top << " w: " << f.width << " h: " << f.height << std::endl;
  
  std::cout << "size: " << v.size() << std::endl;
  
}
