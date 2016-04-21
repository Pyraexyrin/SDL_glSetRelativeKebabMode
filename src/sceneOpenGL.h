#ifdef WIN32

#include <GL/glew.h>

#else

#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>

#endif

#include "events.h"
#include <stdio.h>

////////////
// STRUCT //
////////////

typedef struct sceneOpenGL * SceneOpenGL;

struct sceneOpenGL {
  
  const char* window_title;
  int window_height;
  int window_width;
  
  SDL_Window* window;
  SDL_GLContext context;
  Events events;

  int (*loop) (SceneOpenGL);
  
};

////////////
// CREATE //
////////////

SceneOpenGL
create_SOGL (const char* WT, int WH, int WW);

////////////
// DELETE //
////////////

void
delete_SOGL (SceneOpenGL scene);

////////////////
// INITIALIZE //
////////////////

int
initialize_window_SOGL (SceneOpenGL scene);

int
initialize_glew_SOGL (SceneOpenGL scene);

///////////////
// MAIN LOOP //
///////////////

void
set_main_loop_SOGL (SceneOpenGL scene, int (*function)(SceneOpenGL));

int
main_loop_SOGL (SceneOpenGL scene);

////////////
// ACCESS //
////////////

SDL_Window*
get_window_SOGL (SceneOpenGL scene);

SDL_GLContext
get_context_SOGL (SceneOpenGL scene);

Events
get_events_SOGL (SceneOpenGL scene);
