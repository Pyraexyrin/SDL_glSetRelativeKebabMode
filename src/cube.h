#ifdef WIN32

#include <GL/glew.h>

#else

#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>

#endif

#include <stdio.h>

// Includes GLM

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

////////////
// STRUCT //
////////////

typedef struct cube * Cube;

struct cube {
  
  GLuint shader;
  float vertices[108];
  float colors[108];
  
};

////////////
// CREATE //
////////////

Cube
create_Cube (float size, float x, float y, float z, const char * VERT, const char * FRAG);

////////////
// DELETE //
////////////

void
delete_SOGL (Cube cube);

////////////
// ACCESS //
////////////

GLuint
get_shader_Cube (Cube cube);

float*
get_vertices_Cube (Cube cube);

float*
get_colors_Cube (Cube cube);

// Accurate only if vertices untouched
float
get_size_Cube (Cube cube);

void
display_Cube (Cube cube, mat4 projection, mat4 modelview);
