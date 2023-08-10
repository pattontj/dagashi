#include "MapManager.hpp"
#include "Utility.hpp"

#include "component/Collider.hpp"
#include "system/Physics.hpp"
#include "component/Velocity.hpp"

// #include "prefab/Player.hpp"


Level::Level(std::string path, flecs::flecs& flecs, sf::RenderWindow& window) {
  
  tmx::Map map;

  if (!map.load(path)) {
    std::cout << "Error loading map! Path=" << path << std::endl;
  }
  else {
    std::cout << "loaded map: " << path << std::endl; 
    if (map.getOrientation() != tmx::Orientation::Orthogonal) {
      std::cout << "Error loading map! Path=" << path;
      std::cout << " Is not orthogonal!"<< std::endl;
    }
    else {
      if ( map.getVersion().upper >= 1 && map.getVersion().lower > 0) {
	std::cout << "Warning: TMX ver. " << map.getVersion().upper << "." << map.getVersion().upper;
	std::cout << " greater than 1.0, some data cannot be parsed." << std::endl;
      }

      mapSize = tmxToSF(map.getTileCount());
      levelBounds = tmxToSF(map.getBounds());

      tileSize = tmxToSF(map.getTileSize());


      // Handle textures beforehand

       // If the layer has a tile with an ID in the range of a tileset,
      // then add that tileset to our active tilesets
      // For now, every tileset in theory should be active
      const auto& mapTilesets = map.getTilesets();
      for (const auto& tileset : mapTilesets) {
        activeTilesets.push_back(tileset);
      }

      for (auto& tileset : activeTilesets) {
        sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(tileset.getImagePath())) {
	  std::cout << "Error: Failed to load file '" << tileset.getImagePath()
		    << "' into sf::Texture" << std::endl;
	}
	else {
	  std::cout << "Loaded '" << tileset.getImagePath() << "' into sf::Texture" << std::endl;
	  std::cout << tileset.getName() << std::endl;
	  std::string names(tileset.getName());
	  // TODO(Tyler): Refactor to work with resource manager
	  textures.insert(std::make_pair(std::string(tileset.getName()), std::unique_ptr<sf::Texture>(texture)));
	}
      }
      



      
      // Get our layers from the map and do shit with em

      auto& layers = map.getLayers();

      for (const auto& layer : layers) {
	switch (layer->getType()) {
	case tmx::Layer::Type::Tile: {
	  const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
	  handleTileLayer(tileLayer);
          break;
	}

	case tmx::Layer::Type::Object: {
	  std::cout << "Found object layer type" << std::endl;
	  //const auto& objGroup = 
	  // handleObjectGroup(layer->getLayerAs<tmx::ObjectGroup>(), entityx, window);
	  break;
	}
	  
	case tmx::Layer::Type::Image: {
	  const auto& imageLayer = layer->getLayerAs<tmx::ImageLayer>();
	  handleImageLayer(imageLayer);
	  break;
	}
	}
      }
      
     
      uint32_t maxID = 0;
      for (const auto& tileset : activeTilesets) {
	//std::cout << tileset.getName() << " " << tileset.getImagePath() << std::endl;
	if (tileset.getLastGID() > maxID)
	  maxID = tileset.getTileCount();
      }

      textureOffsets.resize(maxID);
      
      {
        auto& tileset = activeTilesets[0];
	auto tiles = tileset.getTiles();
	for (const auto& tile : tiles) {
	  textureOffsets[tile.ID] = static_cast<sf::Vector2f>(tmxToSF(tile.imagePosition));
	  
	}
      }
      
      


      sf::Vector2f chunkCount((mapSize.x / chunkSize.x), (mapSize.y / chunkSize.y));
      std::cout << "chunkCount x: " << chunkCount.x << " y: "<< chunkCount.y << std::endl;
      chunks = std::vector<std::vector<Chunk>>(chunkCount.x, std::vector<Chunk>(chunkCount.y));

      /* ----- Set the global pixel position of all chunks ----- */
      for (int x = 0; x < chunkCount.x; x++) {
	for (int y = 0; y < chunkCount.y; y++) {
	  Chunk& chunk = chunks.at(x/chunkSize.x).at(y/chunkSize.y);
	  
	  chunk.bounds.left = x*chunkSize.x*tileSize.x;
	  chunk.bounds.top = y*chunkSize.y*tileSize.y;

	  chunk.bounds.width = chunkSize.x*tileSize.x;
	  chunk.bounds.height = chunkSize.y*tileSize.y;
	  
	  std::cout << "Setting chunk coords to: (" << chunk.bounds.left
		    << ", " << chunk.bounds.top << ")" << std::endl; 
	  
	}
      }
      
      /*
	NOTE: I'm like 99% sure that there's an issue with the way stuff is now.
	      Solution feels like I should just fill out a VA, pass by constructor to
	      Chunk, then so on so forth.

       */

      for (int x = 0; x < mapSize.x; x++) {
	for (int y = 0; y < mapSize.y; y++) {
	  auto tileLayer = tileLayers[0];
	  
	  uint32_t tileID = tileLayer[x+y*mapSize.x].ID;
	  sf::Vector2f texPos = textureOffsets[tileID-1];

	  sf::Vector2u chunkCoords(x/(float)chunkSize.x, y/(float)chunkSize.y);
	  /*
	  std::cout << "Chunk coords (" << chunkCoords.x
		    << ", " << chunkCoords.y << ")" << std::endl; 
	  */
	  
	  Chunk& chunk = chunks.at(x/chunkSize.x).at(y/chunkSize.y);
	  chunk.mapVertex.setPrimitiveType(sf::Quads);

	  
	  chunk.mapVertex.append(sf::Vertex(sf::Vector2f(x*tileSize.x,
							 y*tileSize.y),
					    texPos));
	  
	  chunk.mapVertex.append(sf::Vertex(sf::Vector2f(x*tileSize.x+tileSize.x,
							 y*tileSize.y),
					    sf::Vector2f(texPos.x+tileSize.x, texPos.y)));
	  
	  chunk.mapVertex.append(sf::Vertex(sf::Vector2f((x*tileSize.x)+tileSize.x,
							 (y*tileSize.y)+tileSize.y),
					    sf::Vector2f(texPos.x+tileSize.x, texPos.y+tileSize.y)));
	  
	  chunk.mapVertex.append(sf::Vertex(sf::Vector2f(x*tileSize.x,
							 (y*tileSize.y)+tileSize.y),
					    sf::Vector2f(texPos.x, texPos.y+tileSize.y)));

	  
	}
      }
      /////////
      

      //chunks.push_back();
      //Chunk c(vertArr);

      //chunks[0][0] = c;
      
      // TODO: convert to flecs
      // auto testLevel = flecs.entities.create();

      // testLevel.assign<LevelMapComponent>(chunks, textures["zelda"]);
      
      
      
      
    }
  }
}


// This just pushes data into  but doesn't stich anything
void Level::handleTileLayer(const tmx::TileLayer& layer) {
  const auto& tileIDs = layer.getTiles();
  std::vector<tmx::TileLayer::Tile> tiles;
  for (const auto& tile: tileIDs) {
    tmx::TileLayer::Tile t(tile);
    tiles.push_back(t);
  }

  tileLayers.push_back(tiles);
  
}


void Level::handleObjectGroup(const tmx::ObjectGroup& layer, flecs::flecs& ex, sf::RenderWindow& window) {
  // Spawn an entity for every collider
  // TODO(Tyler): Consider stitching colliders, if so write it here before entities are created
  if (layer.getName() == "Collision Layer") {

    const auto& colliders = layer.getObjects();

    for (const auto& collider : colliders) {
      collisionLayer.push_back(tmxToSF(collider.getAABB()));

      // TODO: Convert to flecs
      // flecs::Entity entity = ex.entities.create();
      // entity.assign<ColliderComponent>(tmxToSF(collider.getAABB()), CollisionLevel::WALL);
    }
  }
  // Handles entity layer, prefab factories are called here  
  else if (layer.getName() == "Entity Layer") {
    const auto& entities = layer.getObjects();

    // for entity in entities,
    // determine entity type
    // call a function that creates said entity type (factory)

    for (const auto& entity : entities) {
      if (entity.getName() == "Player") {
	auto bb = entity.getAABB();
	// TODO(Tyler): Refactor to work with resource manager
	
    // TODO: Convert to flecs
    // Factory::createPlayer(ex, window, sf::Vector2f(bb.left, bb.top), textures["zelda"]);
      }
    }
    // FACTORIES GO HERE

    // END FACTORIES
  }
  else {
    std::cout << "Layer does not have a matched engine type! NAME: " << layer.getName() << std::endl;
  }
}

/*zzzzzzzzzzzzzzzzzzzzzzzzzz*/
void Level::handleImageLayer(const tmx::ImageLayer& layer) {
}

// TODO(Tyler): Is this needed still? ANSWER: No it was for debug
//              REMOVE THIS AND DOUBLE CHECK
void Level::draw(sf::RenderWindow& window) {
  // TODO(Tyler): Refactor to work with resource manager
  window.draw(mapVertex, textures["zelda"].get());
  
}
