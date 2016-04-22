// Includes GLM

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "events.h"

////////////
// STRUCT //
////////////

typedef struct camera * Camera;

struct camera {
  
  float Phi;
  float Theta;

  glm::vec3 looking;
  glm::vec3 vertical;
  glm::vec3 normal;

  glm::vec3 position;
  glm::vec3 target;
  
};

////////////
// CREATE //
////////////

Camera
create_Camera (glm::vec3 position, glm::vec3 target, glm::vec3 vertical);

////////////
// DELETE //
////////////

void
delete_Camera (Camera cam);

////////////
// OTHERS //
////////////
void
movement_Camera (Camera cam, int dx, int dy);

void
move_Camera ( Camera cam, Events ev );

void
lookAt_Camera (Camera cam, glm::mat4 * modelview);