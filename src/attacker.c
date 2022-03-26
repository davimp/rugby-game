// Standard headers
#include <stdio.h>
#include <stdlib.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS                             */
/*----------------------------------------------------------------------------*/

// Utils

bool down(position_t attacker, position_t threat) {
  return threat.i > attacker.i;
}

/*----------------------------------------------------------------------------*/

direction_t avoid_threat_and_go_right(position_t attacker, position_t threat){
  if(equal_positions(attacker, threat)){
   return DIR_DOWN;
  }
  else if(down(attacker, threat)){
   return DIR_UP_RIGHT;
  }
  return DIR_DOWN_RIGHT;
}

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {
  static int round = 0;
  static position_t threat_position = {100, 100};
  double random_chance;

  round++;
  random_chance = (double)random()/ (double)RAND_MAX;

  if(round == 10) {
    threat_position = get_spy_position(defender_spy);
  }

  if(random_chance < 0.2) {
    return DIR_UP;
  }
  else if(random_chance < 0.4) {
    return DIR_DOWN;
  }

  return avoid_threat_and_go_right(attacker_position, threat_position);
}

/*----------------------------------------------------------------------------*/
