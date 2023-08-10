#include "App.hpp"

//Flag Components
#include "component/Player.hpp"
#include "component/Interactable.hpp"

#include "component/Body.hpp"
#include "component/Sprite.hpp"
#include "component/Tilemap.hpp"
#include "component/Transform.hpp"
#include "component/Velocity.hpp"

#include "system/Input.hpp"
#include "system/Physics.hpp"

#include "SFMLOrthogonalLayer.hpp"


App::App(sf::RenderWindow &window) : window(window) {
  dbgFont.loadFromFile("resources/sansation.ttf");

  fpsText.setFont(dbgFont);
  fpsText.setPosition(window.getSize().x/2, window.getSize().y/2);
  fpsText.setCharacterSize(30);
  fpsText.setScale(0.3f, 0.3f);

  fpsText.setString("Hello, Sailor!~");
  
}

void App::update(entityx::TimeDelta delta) {

 
  
}


void App::event(sf::Event const &event) {

}

void App::draw() {
  window.draw(fpsText);
}
