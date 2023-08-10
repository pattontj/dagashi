#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <entityx/entityx.h>
//#include "SFMLOrthogonalLayer.hpp"


#include "mapManager.hpp"
#include "component/Collider.hpp"
#include "component/Sprite.hpp"
#include "component/Player.hpp"
#include "component/Camera.hpp"
#include "component/Transform.hpp"
#include "component/Animation.hpp"

#include "system/Input.hpp"
#include "system/Physics.hpp"
#include "system/Render.hpp"

#include "world/Test.hpp"


//sf::Keyboard::key lastKeyPressed;
//sf::Keyboard::key currentKeyPressed;


int main() {
  sf::RenderWindow window(sf::VideoMode(800,600), "SFML window");

  window.setFramerateLimit(60);

  //window.setVerticalSyncEnabled(true);
  
  // entityx::EntityX ex;

  TestWorld testWorld(window, "resources/test2.tmx");


  // TODO(Tyler): Move font into app/global namespace
  sf::Font dbgFont;
  dbgFont.loadFromFile("resources/sansation.ttf");

  sf::Text fpsText;
  fpsText.setFont(dbgFont);
  fpsText.setPosition(window.getSize().x/2, window.getSize().y/2);
  fpsText.setCharacterSize(30);
  fpsText.setScale(0.3f, 0.3f);

  fpsText.setString("Menu");
  
  sf::Clock frameClock;


  // important init stuff
  testWorld.init();

  

  entityx::ComponentHandle<CameraComponent> cameraHandle;

  testWorld.entities.each<PlayerComponent,
			  TransformComponent,
			  CameraComponent>(
				    [&cameraHandle](entityx::Entity e,
							  PlayerComponent& pc,
							  TransformComponent& tc,
							  CameraComponent& cc) {
				      cameraHandle = e.component<CameraComponent>();
				    });
  
  bool pauseTriggered = false;
  while (window.isOpen()) {
    // Process events
    sf::Event event;
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == sf::Event::Closed)
	window.close();


      // Buffered escape code
      if (event.type == sf::Event::KeyPressed) {
	if (event.key.code == sf::Keyboard::Escape) {
	  if (!pauseTriggered) {
	    if (testWorld.isPaused == true)
	      testWorld.isPaused = false;
	    else
	      testWorld.isPaused = true;
	    pauseTriggered = true;
	  }
	}
      }
      if (event.type == sf::Event::KeyReleased) {
	if (event.key.code == sf::Keyboard::Escape) {
	  if (pauseTriggered) {
	    pauseTriggered = false;
	  }
	}
      }
    }


    
    
    if (!testWorld.isPaused) {
      // Does all update stuff
      testWorld.update();
    }
    

    // Clear screen
    window.clear();

    if (!testWorld.isPaused) {
      testWorld.draw();
    }
    else {

      testWorld.draw();
    
      // FPS is top level for rendering
      // Stuff to get FPS

      /*
	double currentFrameTime = frameClock.restart().asSeconds();
	double fps = 1.f/(currentFrameTime);
	fpsText.setString(std::to_string((int)fps));
      */


      /* https://www.sfml-dev.org/documentation/2.5.0/classsf_1_1RenderTarget.php#a2d3e9d7c4a1f5ea7e52b06f53e3011f9
	 NOTE(): Might be good to use this in the future?
       */
      
      fpsText.setPosition( cameraHandle->camera.getCenter().x,
			   cameraHandle->camera.getCenter().y-100);

      sf::RectangleShape rectangle;
      rectangle.setSize(cameraHandle->camera.getSize());
      rectangle.setFillColor(sf::Color(0, 0, 0, 160));
      auto center = cameraHandle->camera.getCenter();
      auto size = cameraHandle->camera.getSize();
      auto pos = sf::Vector2f( center.x- (size.x/2), center.y-(size.y/2) ); 
      rectangle.setPosition( pos );

      window.draw(rectangle);
      window.draw(fpsText);
    }
    
    window.display();


  }
  return 0;
}
