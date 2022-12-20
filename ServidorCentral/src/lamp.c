#include <lampAc.h>

#define LAMP1 0
#define LAMP2 1
#define LAMP3 2
#define LAMP4 3
#define AC1 23
#define AC2 24

State _state;

void state_init() {
  _state.lamp1 = 0;
  _state.lamp2 = 0;
  _state.lamp3 = 0;
  _state.lamp4 = 0;
  _state.ac1 = 0;
  _state.ac2 = 0;
  atualizaState(_state);
}

void sendComand(State state){
    int res = 1;
  if (state.lamp1 != _state.lamp1) {
    res = enviaDistribuido(LAMP1, state.lamp1);
    write_data_lamp_e_ac (LAMP1, state.lamp1);

  }
  if (state.lamp2 != _state.lamp2) {
    res = enviaDistribuido(LAMP2, state.lamp2);
    write_data_lamp_e_ac (LAMP2, state.lamp2);
  }
  if (state.lamp3 != _state.lamp3) {
    res = enviaDistribuido(LAMP3, state.lamp3);
    write_data_lamp_e_ac (LAMP3, state.lamp3);
  }
  if (state.lamp4 != _state.lamp4) {
    res = enviaDistribuido(LAMP4, state.lamp4);
    write_data_lamp_e_ac (LAMP4, state.lamp4);
  }
  if (state.ac1 != _state.ac1) {
    res = enviaDistribuido(AC1, state.ac1);
    write_data_lamp_e_ac (AC1, state.ac1);
  }
  if (state.ac2 != _state.ac2) {
    res = enviaDistribuido(AC2, state.ac2);
    write_data_lamp_e_ac (AC2, state.ac2);
  }

  if (res == 0) {
    _state = state;
    atualizaState(_state);
  }
}