#include "camera.h"

#define SPEED 0.5 // Camera speed
#define SENSE 0.3f// Movement sensitivity

////////////
// CREATE //
////////////

Camera
create_Camera (glm::vec3 position, glm::vec3 target, glm::vec3 vertical) {

	Camera cam = (Camera) malloc( sizeof( struct camera ) );

	cam->position = position;
	cam->target = target;
	cam->vertical = vertical;

	cam->Phi = -35.26;
	cam->Theta = -135;

	return cam;

}

////////////
// DELETE //
////////////

void
delete_Camera (Camera cam){

	free( cam );

}

////////////
// OTHERS //
////////////

void
set_target_Camera (Camera cam, glm::vec3 target){

	// Calcul du vecteur orientation
    cam->looking = cam->target - cam->position;
    cam->looking = normalize(cam->looking);

    // Si l'axe vertical est l'axe X
    if(cam->vertical.x == 1.0)
    {
        // Calcul des angles
        cam->Phi = asin(cam->looking.x);
        cam->Theta = acos(cam->looking.y / cos(cam->Phi));

        if(cam->looking.y < 0)
            cam->Theta *= -1;
    }

    // Si c'est l'axe Y
    else if(cam->vertical.y == 1.0)
    {
        // Calcul des angles
        cam->Phi = asin(cam->looking.y);
        cam->Theta = acos(cam->looking.z / cos(cam->Phi));

        if(cam->looking.z < 0)
            cam->Theta *= -1;
    }

    // Sinon c'est l'axe Z
    else
    {
        // Calcul des angles
        cam->Phi = asin(cam->looking.x);
        cam->Theta = acos(cam->looking.z / cos(cam->Phi));

        if(cam->looking.z < 0)
            cam->Theta *= -1;
    }

    // Conversion en degrés
    cam->Phi = cam->Phi * 180 / M_PI;
    cam->Theta = cam->Theta * 180 / M_PI;

}

void
set_position_Camera (Camera cam, glm::vec3 position) {

	cam->position = position;
	cam->target = position + cam->looking;

}

void
movement_Camera (Camera cam, int dx, int dy) {

	cam->Phi -= dy * SPEED;
	cam->Theta -= dx * SPEED;

    // Limitation de l'angle phi
    if ( cam->Phi > 89.0 )
        cam->Phi = 89.0;

    else if ( cam->Phi < -89.0 )
        cam->Phi = -89.0;


    // Conversion des angles en radian
    float phiRadian = cam->Phi * M_PI / 180;
    float thetaRadian = cam->Theta * M_PI / 180;

    // Si l'axe vertical est l'axe X
    if(cam->vertical.x == 1.0)
    {
        // Calcul des coordonnées sphériques
        cam->looking.x = sin(phiRadian);
        cam->looking.y = cos(phiRadian) * cos(thetaRadian);
        cam->looking.z = cos(phiRadian) * sin(thetaRadian);
    }


    // Si c'est l'axe Y
    else if(cam->vertical.y == 1.0)
    {
        // Calcul des coordonnées sphériques
        cam->looking.x = cos(phiRadian) * sin(thetaRadian);
        cam->looking.y = sin(phiRadian);
        cam->looking.z = cos(phiRadian) * cos(thetaRadian);
    }


    // Sinon c'est l'axe Z
    else
    {
        // Calcul des coordonnées sphériques
        cam->looking.x = cos(phiRadian) * cos(thetaRadian);
        cam->looking.y = cos(phiRadian) * sin(thetaRadian);
        cam->looking.z = sin(phiRadian);
    }


    // Calcul de la normale
    cam->normal = cross(cam->vertical, cam->looking);
    cam->normal = normalize(cam->normal);


    // Calcul du point ciblé pour OpenGL
    cam->target = cam->position + cam->looking;

}

void
move_Camera ( Camera cam, Events ev ) {

	// Gestion de l'orientation
    if( has_moved_mouse_Events(ev) )
    	movement_Camera( cam, get_dx_Events(ev), get_dy_Events(ev) );

    // Avancée de la caméra
    if( is_pressed_key_Events (ev, SDL_SCANCODE_W) )
    {
        cam->position = cam->position + cam->looking * SENSE;
        cam->target = cam->position + cam->looking;
    }

    // Recul de la caméra
    if( is_pressed_key_Events (ev, SDL_SCANCODE_S) )
    {
        cam->position = cam->position - cam->looking * SENSE;
        cam->target = cam->position + cam->looking;
    }

    // Déplacement vers la gauche
    if( is_pressed_key_Events (ev, SDL_SCANCODE_A) )
    {
        cam->position = cam->position + cam->normal * SENSE;
        cam->target = cam->position + cam->looking;
    }

    // Déplacement vers la droite
    if( is_pressed_key_Events (ev, SDL_SCANCODE_D) )
    {
        cam->position = cam->position - cam->normal * SENSE;
        cam->target = cam->position + cam->looking;
    }

}

void
lookAt_Camera (Camera cam, glm::mat4 * modelview) {

	*modelview = glm::lookAt( cam->position, cam->target, cam->vertical );

}