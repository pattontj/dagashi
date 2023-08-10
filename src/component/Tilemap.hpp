#pragma once
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>
#include <vector>

typedef unsigned char pos_t;
typedef unsigned char tile_t;

static bool const MY_MAP[]={
    1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,1,
    1,0,0,0,1,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,1,0,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,0,0,1,1,
};

struct TilemapComponent : public entityx::Component<TilemapComponent>{
  TilemapComponent(pos_t width = 0, pos_t height = 0, sf::Vector2f tile_size = sf::Vector2f (24.f, 24.f));
       
  sf::VertexArray vertex_array;
  sf::Vector2f tile_size;
  pos_t width, height;
  std::vector<bool> solid;
  std::vector<tile_t> tile;
};
