#pragma once

#include <SFML/Graphics.hpp>

#include <entityx/entityx.h>

/*
typedef entityx::ComponentHandle<TransformComponent> child_t;
typedef std::vector<child_t> children_t;
//children_t children;
*/

class TransformComponent : public entityx::Component<TransformComponent> {
 private:
  bool m_isChild = false;
  bool m_hasChild = false;

 public:
  sf::Vector2f position;
  double rotation = 0.f;

  TransformComponent() {
    std::cout << "Error with TransformComponent: Default constructor called!" << std::endl;
  }
  TransformComponent(bool child): m_isChild(child) {}
  TransformComponent(sf::Vector2f pos, bool child): position(pos), m_isChild(child) {}
  TransformComponent(sf::Vector2f pos, double rot, bool child): position(pos),rotation(rot), m_isChild(child){}
  

  
  bool isChild() {
    return m_isChild;
  }
  bool hasChild() {
    return m_hasChild;
  }
  
};

/*
  
  FOR CHILD STUFF:
  
  HAVE A SYSTEM IN PLACE THAT DOES THE FOLLOWING
  
  > LOOP ALL TRANSFORM COMPONENTS
  > IF !m_isChild AND m_hasChild THEN
      > WALK DOWN A LINKED LIST OF CHILDREN AND UPDATE ACCORDINGLY


  IF TRANSFORM REGAINS AUTONOMY, m_isChild == false 

*/
