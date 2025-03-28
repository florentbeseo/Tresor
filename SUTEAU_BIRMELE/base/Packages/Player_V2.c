//
// Created by tanguy on 28/03/25.
//

#include "Player.h"
#include <stdbool.h>

typedef enum
{
    S_AUCISSE =0,
    S_REPOS,
    S_ACTIF,
    S_DEAD,
    NB_STATE
}state_t;

typedef enum
{
    E_UP = 0,
    E_DOWN,
    E_LEFT,
    E_RIGHT,
    E_STOP,
    NB_EVENT
}event_t;

typedef enum
{
    A_NOP = 0,
    A_GO_UP,
    A_GO_DOWN,
    A_GO_LEFT,
    A_GO_RIGHT,
}action_t;

typedef struct
{
    state_t destination;
    action_t action;
}transition_t;

static const transition_t transition_table[NB_STATE][NB_EVENT] =
{
    [S_REPOS][E_UP] = {S_REPOS,A_GO_UP},
    [S_REPOS][E_DOWN] = {S_REPOS,A_GO_DOWN},
    [S_REPOS][E_LEFT] = {S_REPOS,A_GO_LEFT},
    [S_REPOS][E_RIGHT] = {S_REPOS,A_GO_RIGHT},
    [S_REPOS][E_STOP] = {S_DEAD,A_NOP}
};

static void run(event_t);

struct Player_s{
    int position_x;
    int position_y;
    state_t state;
};

static Player player;


extern void Player_init(void){
    player.position_x = 0;
    player.position_y = 0;
    player.state = S_DEAD;
};

extern Coordinates Player_get_pos(void){
    Coordinates pos;
    pos.x = player.position_x;
    pos.y = player.position_y;
    return pos;
}


extern void Player_start(void){
  assert(player.state == S_DEAD);
  player.state = S_REPOS;
}

extern void Player_stop(void){
  run(E_STOP);
}

extern bool Player_movement(direction_t dir){
    bool moved = false;
    switch(dir){
        case DEP_UP:
            if(!(player.position_y <= 0)){
                run(E_UP);
                moved = true;
            }
        break;
        case DEP_DOWN:
            if(!(player.position_y >= HEIGHT_MAP-1)){
                run(E_DOWN);
                moved = true;
            }
        break;
        case DEP_LEFT:
            if(!(player.position_x <= 0)){
                run(E_LEFT);
                moved = true;
            }
        break;
        case DEP_RIGHT:
            if(!(player.position_x >= WIDTH_MAP-1)){
                run(E_RIGHT);
                moved = true;
            }
        break;
        default:
            assert(0);
        break;
    }
    return moved;
}



static void run(event_t event)
{
    assert(this->state != S_DEAD);

    state_t destination = transition_table[player.state][event].destination;

    action_t todo_action = transition_table[player.state][event].action;

    switch(todo_action)
    {
        case A_NOP: break;
        case A_GO_UP :
          player.position_y--;
          break;
        case A_GO_DOWN :
          player.position_y++;
          break;
        case A_GO_LEFT :
          player.position_x--;
          break;
        case A_GO_RIGHT :
          player.position_x++;
          break;
        default:
          assert(0);
          break;
    }

    if(destination != S_AUCISSE)
    {
        player.state =  destination;
    }
}



