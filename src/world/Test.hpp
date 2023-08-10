#pragma once


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

#include "world/World.hpp"


class TestWorld : public World {
private:

public:

  using World::World;
  
  bool init() override;
  
  void update() override;
  
  void draw() override;
   
};
