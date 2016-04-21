#include <stdlib.h>
#include <stdbool.h>
#include "sceneOpenGL.h"
#include "cube.h"

//#define GLEW_STATIC
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

  // Je m'excuse d'avance pour cette chose ignoble : du C++ dans du C.
  // Cependant, c'est le seul moyen de faire fonctionner tout ça.
  // OpenGL semble vraiment fait pour du C++. Sans le namespace, je devrais
  // mettre les glm:: partout, c'est moins moche comme ça.

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
  
  // Transformations
  // rotate en radians !
  //modelview = translate(modelview, vec3(0.4, 0.0, 0.0));
  //modelview = rotate(modelview, 3.1416f, vec3(0.0, 0.0, 1.0));
  //modelview = scale(modelview, vec3(1.0/2, 1.0/2, 1.0));

  // create_Cube(size, x, y, z, vert, frag)
  Cube cube1 = create_Cube( 1.0, -1.5, 0.0, 0.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag" );
  Cube cube2 = create_Cube( 1.0, 0.5, 0.0, 0.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag" );
  
  float angle_x = 0.0f;
  float angle_y = 0.0f;
  float angle_z = 0.0f;

  Events events = get_events_SOGL( scene );

  while( !terminate_Events( events ) ) {

    // Starting routine
    start_loop = SDL_GetTicks();





    update_Events( events );

    //if (is_pressed_key_Events( events, SDL_SCANCODE_ESCAPE ))
      // Quit

    if (is_pressed_key_Events( events, SDL_SCANCODE_W )) // ATTENTION, CLAVIER QWERTY !
      angle_x -= 0.02f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_S ))
      angle_x += 0.02f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_A ))
      angle_y -= 0.02f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_D ))
      angle_y += 0.02f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_Q ))
      angle_z -= 0.02f;

    if (is_pressed_key_Events( events, SDL_SCANCODE_E ))
      angle_z += 0.02f;



    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // User //

    modelview_backup = modelview;

      modelview = translate(modelview, vec3(-1.0, 0.5, 0.5));
      modelview = rotate(modelview, angle_x, vec3(1.0, 0.0, 0.0));
      modelview = rotate(modelview, angle_y, vec3(0.0, 1.0, 0.0));
      modelview = rotate(modelview, angle_z, vec3(0.0, 0.0, 1.0));
      modelview = translate(modelview, vec3(1.0, -0.5, -0.5));

      display_Cube(cube1, projection, modelview);

    modelview = modelview_backup;

      modelview = translate(modelview, vec3(1.0, 0.5, 0.5));
      modelview = rotate(modelview, angle_x, vec3(1.0, 0.0, 0.0));
      modelview = rotate(modelview, angle_y, vec3(0.0, 1.0, 0.0));
      modelview = rotate(modelview, angle_z, vec3(0.0, 0.0, 1.0));
      modelview = translate(modelview, vec3(-1.0, -0.5, -0.5));

      display_Cube(cube2, projection, modelview);

    modelview = modelview_backup;

    modelview = lookAt(vec3(0.0, 3.0, 3.0), vec3(0, 0, 0), vec3(0, 1, 0));
    



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
