#include <SDL2/SDL.h>
#include <stdbool.h>

////////////
// STRUCT //
////////////

typedef struct events * Events;

struct events {
  
  SDL_Event events;
  bool keys[SDL_NUM_SCANCODES];
  bool mouse[8];
  int x;
  int y;
  int dx;
  int dy;
  bool terminate;
  
};

////////////
// CREATE //
////////////

Events
create_Events ();

////////////
// DELETE //
////////////

void
delete_Events (Events ev);

////////////
// UPDATE //
////////////

void
update_Events (Events ev);

bool
terminate_Events (Events ev);

////////////
// ACCESS //
////////////

bool
is_pressed_key_Events (Events ev, const SDL_Scancode key);

bool
is_pressed_mouse_Events (Events ev, const Uint8 mouse);

bool
has_moved_mouse_Events (Events ev);

int
get_x_Events (Events ev);

int
get_y_Events (Events ev);

int
get_dx_Events (Events ev);

int
get_dy_Events (Events ev);

void
display_cursor_Events (bool wanna_display_cursor);

void
capture_cursor_Events (bool wanna_capture_cursor);