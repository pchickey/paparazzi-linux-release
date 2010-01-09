// ap_state.h
// pat hickey and bradley lord, 09jan10


// global definition of ap_state_t type

struct ap_state_t {
  pprz_t commands[COMMANDS_NB];
};

// ap.c provides pointer to its own ap_state, and fbw.c needs to use this to set servos.

extern struct ap_state_t* ap_state;

