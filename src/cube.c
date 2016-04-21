#include "cube.h"

/////////////////////
// SHADER-USE ONLY //
/////////////////////

GLuint shaderProg;
GLuint positionBufferObject;
GLuint coordBuffer, colorBuffer;
GLint  attributeColor;

char* readFile(const char* fname) {
  FILE *f;
  char *content = NULL;
  int count = 0;
  if (fname != NULL) {
    f = fopen(fname,"rt");

    if (f != NULL) {
      fseek(f, 0, SEEK_END);  
      count = ftell(f);
      rewind(f);

      if (count > 0) {
	content = (char *)malloc(sizeof(char) * (count+1));
	count = fread(content,sizeof(char),count,f);
	content[count] = '\0';
      }
      fclose(f);
    }
  }
  return content;
}

GLuint setShaders( const char * VERT, const char * FRAG ) {

  /* CREATE THE SHADERS */
  //1 - create objects which will act as shader containers.
  // (vertex and fragment shader)
  GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
  
  GLchar* vertexSource = (GLchar*)readFile( VERT );
  GLchar* fragmentSource = (GLchar*)readFile( FRAG );
 
	
  // 2 - associate shader and source
  glShaderSource( vshader, 1, (const GLchar**)(&vertexSource), NULL );
  glShaderSource( fshader, 1, (const GLchar**)(&fragmentSource), NULL );

  // 3 - Compile vertex and fragment shader
  glCompileShader(vshader);
  glCompileShader(fshader);

  /* CREATE THE PROGRAM */
  //1 - create the object which will act as a program container.
  GLuint shaderProgram = glCreateProgram();

  /* /\* // 2 - attach shader to the program *\/ */
  glAttachShader(shaderProgram,vshader);
  glAttachShader(shaderProgram,fshader);

  /* // 3 - link the program. For this step, the shaders must be compiled. */
  glLinkProgram(shaderProgram); 

  /* // 4 - Load and use the program */
  glUseProgram(shaderProgram); 

  /* //FREE  */
  free(vertexSource);
  free(fragmentSource);
  return shaderProgram;
}

////////////
// CREATE //
////////////

Cube
create_Cube (float size, float x, float y, float z, const char * VERT, const char * FRAG){

  Cube cube = (Cube) malloc( sizeof( struct cube ) );
  
  // 3 infos (x, y, z) par vertex (point)
  // Notation des faces FB-UD-LR
  float vertT[108] = {x, y, z,         x+size, y, z,         x+size, y+size, z,
		      x, y, z,         x, y+size, z,         x+size, y+size, z,      // Face B
		      x, y, z+size,    x+size, y, z+size,    x+size, y+size, z+size,
		      x, y, z+size,    x, y+size, z+size,    x+size, y+size, z+size, // Face F
		      x, y+size, z,    x+size, y+size, z,    x+size, y+size, z+size,
		      x, y+size, z,    x, y+size, z+size,    x+size, y+size, z+size, // Face U
		      x, y, z,         x+size, y, z,         x+size, y, z+size,
		      x, y, z,         x, y, z+size,         x+size, y, z+size,      // Face D
		      x, y, z,         x, y, z+size,         x, y+size, z+size,
		      x, y, z,         x, y+size, z,         x, y+size, z+size,      // Face L
		      x+size, y, z,    x+size, y, z+size,    x+size, y+size, z+size,
		      x+size, y, z,    x+size, y+size, z,    x+size, y+size, z+size};// Face R

  // 3 infos (RGB) par vertex
  float cT[108] =  {1.0, 0.0, 0.0,     1.0, 0.0, 0.0,      1.0, 0.0, 0.0,
		    1.0, 0.0, 0.0,     1.0, 0.0, 0.0,      1.0, 0.0, 0.0, // Face B
		    1.0, 0.0, 0.0,     1.0, 0.0, 0.0,      1.0, 0.0, 0.0,
		    1.0, 0.0, 0.0,     1.0, 0.0, 0.0,      1.0, 0.0, 0.0, // Face F
		    0.0, 1.0, 0.0,     0.0, 1.0, 0.0,      0.0, 1.0, 0.0,
		    0.0, 1.0, 0.0,     0.0, 1.0, 0.0,      0.0, 1.0, 0.0, // Face U
		    0.0, 1.0, 0.0,     0.0, 1.0, 0.0,      0.0, 1.0, 0.0,
		    0.0, 1.0, 0.0,     0.0, 1.0, 0.0,      0.0, 1.0, 0.0, // Face D
		    0.0, 0.0, 1.0,     0.0, 0.0, 1.0,      0.0, 0.0, 1.0,
		    0.0, 0.0, 1.0,     0.0, 0.0, 1.0,      0.0, 0.0, 1.0, // Face L
		    0.0, 0.0, 1.0,     0.0, 0.0, 1.0,      0.0, 0.0, 1.0,
		    0.0, 0.0, 1.0,     0.0, 0.0, 1.0,      0.0, 0.0, 1.0};// Face R

  for (int i = 0; i<108; ++i){
    cube->vertices[i] = vertT[i];
    cube->colors[i] = cT[i];
  }
  
  // Shaders
  cube->shader = setShaders(VERT, FRAG);

  return cube;
  
}

////////////
// DELETE //
////////////

void
delete_Cube (Cube cube){

  free( cube->vertices );
  free( cube->colors );
  free( cube );
  
}

////////////
// ACCESS //
////////////

// Permettent l'édition directe

GLuint
get_shader_Cube (Cube cube) {

  return cube->shader;

}

float*
get_vertices_Cube (Cube cube) {

  return cube->vertices;

}

float*
get_colors_Cube (Cube cube) {

  return cube->colors;

}

// Accurate only if vertices untouched
float
get_size_Cube (Cube cube) {

  return cube->vertices[3] - cube->vertices[0];
  
}

void
display_Cube (Cube cube, mat4 projection, mat4 modelview) {

  // CHARGER LE SHADER
  glUseProgram( cube->shader );
    
  // ACTIVER LES ARRAYS
  // (id, nb_données_par_vertex, type, bool, *p, tab)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, cube->vertices);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, cube->colors);
  glEnableVertexAttribArray(1);

  // On envoie les matrices au shader
  glUniformMatrix4fv(glGetUniformLocation( cube->shader, "modelview"), 1, GL_FALSE, value_ptr(modelview) );
  glUniformMatrix4fv(glGetUniformLocation( cube->shader, "projection"), 1, GL_FALSE, value_ptr(projection) );

  // On affiche les triangles associés à l'array 0, 12 triangles de 3 vertex
  glDrawArrays(GL_TRIANGLES, 0, 12*3);
    
  // On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
  glDisableVertexAttribArray(0);

  glUseProgram(0);

}
