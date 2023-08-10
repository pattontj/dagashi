#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <iostream>

#include <entityx/entityx.h>

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include <tmxlite/Layer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Object.hpp>

#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/ImageLayer.hpp>

#include "component/Camera.hpp"

#include <cstdint>
#include <cmath>

/*
  Typedefs to make the members easier on the eyes
*/
typedef std::map<std::string, std::shared_ptr<sf::Texture>> TextureMap;
typedef std::vector<std::vector<tmx::TileLayer::Tile>> TileLayers;
typedef std::vector<sf::FloatRect> CollisionLayer;

/* NOTE: hard coding chunk size is an awful idea, fix later */
const sf::Vector2u CHUNK_SIZE = sf::Vector2u(16, 16);

//typedef std::vector<ImageLayer> ImageLayers;
//typedef std::map<uint32_t, sf::Vector2f> TextureOffsets;

// Dummy class, for if I ever implement images >.<
//class ImageLayer;

struct Chunk;

class Level {
public:
  //Dimensions of the map in grid spaces
  sf::Vector2u mapSize;

  sf::Vector2u chunkSize = CHUNK_SIZE;
  
  // Dimenions of all tiles used
  sf::Vector2u tileSize;
  // Holds onto all textures used in the level
  TextureMap textures;
  // Defines the bounds the level exists inside
  sf::FloatRect levelBounds;

  // Holds onto the TMX representation of tilesets
  // QUESTION: Do we need this long term as a member?
  std::vector<tmx::Tileset> activeTilesets;

  // A vector of TMX tiles pulled from the tile layer
  TileLayers tileLayers;
  // A vector of TMX tiles pulled from the collision layer
  CollisionLayer collisionLayer;
  // NOTE: Currently we aren't supporting image layers, possibly
  //       make note of this as a printout (or implement it)
  //ImageLayers imageLayers;

  // Stores the offsets for each tile texture we use
  std::vector<sf::Vector2f> textureOffsets;
  // The vertex array we stitch our tiles together with
  sf::VertexArray mapVertex;



  std::vector<std::vector<Chunk>> chunks;
  
  
  /* METHODS */
public:
  Level() {
    std::cout << "LevelComponent passed zero args, cannot load level!" << std::endl;
  }
  Level(std::string path, entityx::EntityX&, sf::RenderWindow&);

  /*
    NOTE:
    Currently we only have one layer. When we go to implement roofs (if we do)
    we will want to create a pre and post frame draw function and tag our tile layers 
    as pre or post in Tiled.
   */
  
  void draw(sf::RenderWindow&);

private:
  void handleTileLayer(const tmx::TileLayer& layer);
  // Object group needs the RenderWindow to spawn the player
  void handleObjectGroup(const tmx::ObjectGroup& layer, entityx::EntityX&, sf::RenderWindow&);
  void handleImageLayer(const tmx::ImageLayer& layer);
  
};


class Chunk {
public:
  // Starting top-left coordinates of the chunk
  sf::Vector2u coordinates;
  // Bounds for broadphase collisions
  sf::FloatRect bounds;
  // All colliders within this layer
  CollisionLayer collision;
  // Chunk's vertex array
  sf::VertexArray mapVertex;

  Chunk(){
    mapVertex.setPrimitiveType(sf::Quads);
      
  }
  Chunk(const sf::VertexArray& vert) : mapVertex(vert){
    mapVertex.setPrimitiveType(sf::Quads);
  }
  
};


/*
  Component we use to store our level data
*/
class LevelMapComponent : public entityx::Component<LevelMapComponent> {
public:
  std::vector<std::vector<Chunk>> chunks;
  std::shared_ptr<sf::Texture> texture;

  //entityx::ComponentHandle<CameraComponent> camera;
  
  
public:
  // Zero-args constructor needed for entityx
  LevelMapComponent() {}
  LevelMapComponent(std::vector<std::vector<Chunk>> c,
		    std::shared_ptr<sf::Texture> tex): chunks(c), texture(tex) {    
    // Copies the vertex array and a shared_ptr to it's texture for rendering
  }
  void draw(sf::RenderWindow& window, entityx::EntityX& ex) {
    sf::FloatRect cameraBounds;
    
    //if (!camera) {
    ex.entities.each<CameraComponent>([&cameraBounds](entityx::Entity ent, CameraComponent& cc){
	sf::Vector2f v(cc.camera.getCenter().x-cc.camera.getSize().x/2,
		       cc.camera.getCenter().y-cc.camera.getSize().y/2);
	//	std::cout << "x: " << v.x << " y: " << v.y << std::endl;
        
	cameraBounds = sf::FloatRect(v, cc.camera.getSize());
      });
      //}
    
    for (const auto& chunkVec : chunks ) {
      for (const auto& chunk : chunkVec) {
	if (cameraBounds.intersects(chunk.mapVertex.getBounds())) {
	  window.draw(chunk.mapVertex, texture.get());
	}
      }
    }
  }
};
