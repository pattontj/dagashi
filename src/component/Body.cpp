/*#include "Body.h"


Direction vectorToDirection(sf::Vector2f vector, Direction fallback) {
  if (vector.y ==0) {
    if (vector.x == 0) {
      return fallback;
    }
    else {
      return (Direction)(std::signbit(vector.x)*2);
    }
  }
  else {
    return (Direction)(std::signbit(vector.y)*2+1);
  }
}

sf::Vector2f directionToVector(Direction dir){
  if (dir == Direction::LEN) {
    return sf::Vector2f();
  }
  else {
    int d = (int)dir;
    return sf::Vector2f((d+1)%2 * (1-d), d%2 * (2-d));
  }
}
*/
