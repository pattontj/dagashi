# Dagashi

## What is Dagashi?
Dagashi (Japanese for candy) is a hobbyist custom 2D game engine built in C++, and originally made custom for a previous game project.
The engine leverages the EntityX Entity Component System (ECS) and the TileD level editor to simplify content creation and allow for faster testing and iteration. Dagashi was originally written between 2018-2019 and hosted on a previous (and now privated) github repository; all code, assets, and documentation initally commited in this repository was produced during this time period.


https://github.com/pattontj/dagashi/assets/60120527/734d8a74-9724-4883-b26f-56295c37eebc
https://github.com/pattontj/dagashi/assets/60120527/58cba96f-1de4-45ce-b058-48e48ff03419



## Engine features

- [x] Orthogonal physics 
- [x] TMX map integration 
  - [x] Tile layers
  - [x] Object layers
  - [ ] TMX image layers (Dunno if I actually need it? Maybe for the roof effect thing)
  - [ ] Multiple textures 
- [x] Chunk-based map rendering
- [x] Camera that follows the player
- [x] Chunk-based broadphase physics
- [x] Animations
  - [x] Flip animations
  - [ ] Infinite looping
  - [ ] Adding animations together (frame set A + frame set B = frame set C)
  - [ ] FPS independent animation speed
  - [ ] Speed factor (for speeding up/slowing down in general)

- [ ] Menus
  - [X] Stop sending inputs to player
  - [ ] Generic and reusable 

- [ ] Generic, game-persistent data (money, date+time, name, inventory etc.)

- [ ] Seperate update logic from the rendering code (run physics consistently so vsync can do it's thing)

- [ ] Object interaction (basically boxes/picking things up)
- [ ] Serialization (of what?)


