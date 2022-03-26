// Standard headers
#include <stdio.h>
#include <stdlib.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter


/*----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS                             */
/*----------------------------------------------------------------------------*/

// Utils

bool right(position_t defender, position_t target) {
  return target.i == defender.i && target.j > defender.j;
}

bool left(position_t defender, position_t target) {
  return target.i == defender.i && target.j < defender.j;
}

bool up(position_t defender, position_t target) {
  return target.i < defender.i && target.j == defender.j;
}

bool up_right(position_t defender, position_t target) {
  return target.i < defender.i && target.j > defender.j;
}

bool up_left(position_t defender, position_t target) {
  return target.i < defender.i && target.j < defender.j;
}

// bool down(position_t defender, position_t target) {
//   return target.i > defender.i && target.j == defender.j;
// }

bool down_right(position_t defender, position_t target) {
  return target.i > defender.i && target.j > defender.j;
}

bool down_left(position_t defender, position_t target) {
  return target.i > defender.i && target.j < defender.j;
}

/*----------------------------------------------------------------------------*/

direction_t follow_target(position_t defender, position_t target){
  if(right(defender, target)){
    return DIR_RIGHT;
  }
  else if(left(defender, target)){
   return DIR_LEFT;
  }
  else if(up(defender, target)){
   return DIR_UP;
  }
  else if(up_right(defender, target)){
   return DIR_UP_RIGHT;
  }
  else if(up_left(defender, target)){
   return DIR_UP_LEFT;
  }
  else if(down_right(defender, target)){
   return DIR_DOWN_RIGHT;
  }
  else if(down_left(defender, target)){
   return DIR_DOWN_LEFT;
  }
  return DIR_DOWN;
}

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {
  static int round = 0;
  static position_t target_position = {0, 0};
  double random_chance;

  round++;
  random_chance = (double)random()/ (double)RAND_MAX;

  if(round == 10) {
    target_position = get_spy_position(attacker_spy);
  }

  if(random_chance < 0.2) {
    return DIR_UP;
  }
  else if(random_chance < 0.4) {
    return DIR_DOWN;
  }
  
  return follow_target(defender_position, target_position);
}

/*----------------------------------------------------------------------------*/
