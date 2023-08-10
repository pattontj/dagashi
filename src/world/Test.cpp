#include "world/Test.hpp"

bool TestWorld::init() {
  this->entities.each<LevelMapComponent>([](entityx::Entity entity, LevelMapComponent Level) {
					std::cout << "Added a LevelComponent! " << std::endl;
				      });


  /*
    SET UP THE CAMERA
  */
  this->entities.each<PlayerComponent,
		   SpriteComponent,
		   CameraComponent>([this](entityx::Entity e,
					      PlayerComponent pc,
					      SpriteComponent sc,
					      CameraComponent cc){
				      cc.camera.setCenter(sc.sprite.getPosition());
				      window->setView(cc.camera);
				    });

  
  
  this->systems.add<InputSystem>();
  this->systems.add<PhysicsSystem>();
  auto renderSys = this->systems.add<RenderSystem>(*window, *this);
  this->systems.configure();

  renderSys->initAnimations();

}


void TestWorld::update() {

  /* ----- RUN INPUT UPDATE ----- */
  this->systems.update<InputSystem>(0.1);

  this->entities.each<TransformComponent,
		   ColliderComponent>([](entityx::Entity e,
					 TransformComponent& tc,
					 ColliderComponent& cc) {
					if (cc.collisionLevel < CollisionLevel::WALL) {
					  cc.collider.setPosition(tc.position.x, tc.position.y);
			        	}
				      });


  /* ----- RUN PHYSICS UPDATE ----- */
  this->systems.update<PhysicsSystem>(0.1);


  this->entities.each<TransformComponent,
		   SpriteComponent>([](entityx::Entity e,
				       TransformComponent& tc,
				       SpriteComponent& sc) {
					
				      sc.sprite.setPosition(tc.position);
					
				    });

  /*  Update the animation position  */
  this->entities.each<TransformComponent,
		   AnimationComponent>([](entityx::Entity e,
					  TransformComponent& tc,
					  AnimationComponent& ac) {
					
					 ac.sprite.setPosition(tc.position);
					
				       });



    
  this->entities.each<TransformComponent,
		   ColliderComponent>([](entityx::Entity e,
					 TransformComponent& tc,
					 ColliderComponent& cc) {
					if (cc.collisionLevel < CollisionLevel::WALL) {
					  cc.collider.setPosition(tc.position.x, tc.position.y);
					  
					}
				      });


  entityx::ComponentHandle<CameraComponent> cameraHandle;
  this->entities.each<PlayerComponent,
		   TransformComponent,
		   CameraComponent>(
				    [this, &cameraHandle](entityx::Entity e,
							     PlayerComponent& pc,
							     TransformComponent& tc,
							     CameraComponent& cc) {
				      cc.camera.setCenter(tc.position);
				      window->setView(cc.camera);
				      cameraHandle = e.component<CameraComponent>();
				    });
  


  
}


void TestWorld::draw() {
  this->systems.update<RenderSystem>(0.1);
}
