#include "sceneOpenGL.h"

 //////////////////////////////////////
 // WHEN YOU'RE NOT WORKING WITH C++ //
 //////////////////////////////////////

////////////
// CREATE //
////////////

SceneOpenGL
create_SOGL (const char* WT, int WH, int WW){
  
  SceneOpenGL scene = (SceneOpenGL) malloc( sizeof( struct sceneOpenGL ) );

  scene->window_title = WT;
  scene->window_height = WH;
  scene->window_width = WW;

  scene->events = create_Events();

  return scene;
  
}

////////////
// DELETE //
////////////

void
delete_SOGL (SceneOpenGL scene){
  
  delete_Events(scene->events);

  SDL_GL_DeleteContext(scene->context);
  SDL_DestroyWindow(scene->window);
  SDL_Quit();
  
  free(scene);
  
}

////////////////
// INITIALIZE //
////////////////

int
initialize_window_SOGL (SceneOpenGL scene){
  
  // Initialisation de la SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      printf("Erreur lors de l'initialisation de la SDL : ");
      SDL_Quit();

      return -1;
    }

  // Version d'OpenGL
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


  // Double Buffer
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


  // Création de la fenêtre
  scene->window = SDL_CreateWindow(scene->window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scene->window_width, scene->window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  if (scene->window == 0){
    printf("Erreur lors de la création de la fenêtre : ");
    SDL_Quit();

    return -1;
  }


  // Création du contexte OpenGL
  scene->context = SDL_GL_CreateContext(scene->window);

  if(scene->context == 0){
    printf("%s", SDL_GetError());
    SDL_DestroyWindow(scene->window);
    SDL_Quit();

    return -1;
  }

  return 0;
    
}

int
initialize_glew_SOGL (SceneOpenGL scene){
#ifdef WIN32

  // On initialise GLEW
  GLenum initialisationGLEW = glewInit();

  // Si l'initialisation a échoué :
  if (initialisationGLEW != GLEW_OK){
    
    // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
    fprintf(stderr, "Erreur d'initialisation de GLEW : %c\n", glewGetErrorString(initialisationGLEW));

    // On quitte la SDL
    SDL_GL_DeleteContext(scene->context);
    SDL_DestroyWindow(scene->window);
    SDL_Quit();

    return -1;
      
  }

#endif

  // Activation du Depth Buffer
  glEnable(GL_DEPTH_TEST);
  
  // Tout s'est bien passé, on retourne true
  return 0;
  
}

///////////////
// MAIN LOOP //
///////////////

void
set_main_loop_SOGL (SceneOpenGL scene, int (*function)(SceneOpenGL)){
  scene->loop = function;
}

int
main_loop_SOGL (SceneOpenGL scene){
  return (scene->loop)(scene);
}

////////////
// ACCESS //
////////////

SDL_Window*
get_window_SOGL (SceneOpenGL scene){
  return scene->window;
}

SDL_GLContext
get_context_SOGL (SceneOpenGL scene){
  return scene->context;
}

Events
get_events_SOGL (SceneOpenGL scene){
  return scene->events;
}
