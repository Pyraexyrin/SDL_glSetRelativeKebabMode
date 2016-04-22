#include <stdlib.h>
#include <stdbool.h>
#include "sceneOpenGL.h"
#include "cube.h"
#include "camera.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

  // Je m'excuse d'avance pour cette chose ignoble : du C++ dans du C.
  // Cependant, c'est le seul moyen de faire fonctionner tout ça.
  // OpenGL semble vraiment fait pour du C++.

using namespace glm;

///////////////
// MAIN LOOP //
///////////////

int
main_loop (SceneOpenGL scene){

  unsigned int framerate = 1000/50; // 1000/fps (Frame Per Second)
  Uint32 start_loop, end_loop;

  // Matrices
  mat4 projection;
  mat4 modelview;
  mat4 modelview_backup;

  // Initialisation
  projection = perspective(70.0, (double) WINDOW_WIDTH / WINDOW_HEIGHT, 1.0, 100.0);
  modelview = mat4(1.0);
  
  Camera cam = create_Camera(vec3(0.0, 3.0, 3.0), vec3(0, 0, 0), vec3(0, 1, 0));

  // create_Cube(size, x, y, z, vert, frag)
  Cube cube1 = create_Cube( 1.0, -1.5, 0.0, 0.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag" );
  Cube cube2 = create_Cube( 1.0, 0.5, 0.0, 0.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag" );
  
  float angle_x = 0.0f;
  float angle_y = 0.0f;
  float angle_z = 0.0f;
  float scale = 1.0f;

  Events events = get_events_SOGL( scene );
  display_cursor_Events(false);
  capture_cursor_Events(true);

  while( !terminate_Events( events ) ) {

    // Starting routine
    start_loop = SDL_GetTicks();

    update_Events( events );

    if (is_pressed_key_Events( events, SDL_SCANCODE_ESCAPE ))
      // Quit
      break;

    if (is_pressed_key_Events( events, SDL_SCANCODE_O )) // ATTENTION, CLAVIER QWERTY !
      angle_x -= 0.02f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_L ))
      angle_x += 0.02f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_K ))
      angle_y -= 0.02f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_SEMICOLON ))
      angle_y += 0.02f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_P ))
      angle_z -= 0.02f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_I ))
      angle_z += 0.02f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_LSHIFT )
      || is_pressed_key_Events( events, SDL_SCANCODE_RSHIFT))
      scale -= 0.01f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_SPACE ))
      scale += 0.01f;

    move_Camera(cam, events);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // User //

    modelview_backup = modelview;

      modelview = translate(modelview, vec3(-1.0, 0.5, 0.5));
      modelview = rotate(modelview, angle_x, vec3(1.0, 0.0, 0.0));
      modelview = rotate(modelview, angle_y, vec3(0.0, 1.0, 0.0));
      modelview = rotate(modelview, angle_z, vec3(0.0, 0.0, 1.0));
      modelview = glm::scale(modelview, vec3(scale, scale, scale));
      modelview = translate(modelview, vec3(1.0, -0.5, -0.5));

      display_Cube(cube1, projection, modelview);

    modelview = modelview_backup;

      modelview = translate(modelview, vec3(1.0, 0.5, 0.5));
      modelview = rotate(modelview, angle_x, vec3(1.0, 0.0, 0.0));
      modelview = rotate(modelview, angle_y, vec3(0.0, 1.0, 0.0));
      modelview = rotate(modelview, angle_z, vec3(0.0, 0.0, 1.0));
      modelview = glm::scale(modelview, vec3(scale, scale, scale));
      modelview = translate(modelview, vec3(-1.0, -0.5, -0.5));

      display_Cube(cube2, projection, modelview);

    modelview = modelview_backup;

    lookAt_Camera(cam, &modelview);



    // Ending routine
    SDL_GL_SwapWindow( get_window_SOGL(scene) );
    
    end_loop = SDL_GetTicks() - start_loop;
    if (end_loop < framerate)
      SDL_Delay( framerate - end_loop );

  }

  return 0;
}

//////////
// MAIN //
//////////

int
main(int argc, char **argv) {
  
  // Notre scène
  SceneOpenGL scene = create_SOGL( "OpenGL : Quand le C++ viole de force le C", WINDOW_HEIGHT, WINDOW_WIDTH );

  if ( initialize_window_SOGL(scene) != 0 ) {
    fprintf(stderr, "Something went wrong while initializing the window.\n");
    return -1;
  }
  if ( initialize_glew_SOGL(scene) != 0 ) {
    fprintf(stderr, "Something went wrong while initializing GLEW.\n");
    return -1;
  }
  
  set_main_loop_SOGL( scene, main_loop );

  main_loop_SOGL( scene );

  // On quitte
  delete_SOGL(scene);

  return 0;
}
