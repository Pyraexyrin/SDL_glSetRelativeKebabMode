#include "events.h"

////////////
// CREATE //
////////////

Events
create_Events () {

	Events ev = (Events) malloc( sizeof( struct events ) );

	ev->x = 0;
	ev->y = 0;
	ev->dx = 0;
	ev->dy = 0;

	for (int i = 0; i<SDL_NUM_SCANCODES; ++i)
		ev->keys[i] = false;

	for (int i = 0; i<8; ++i)
		ev->mouse[i] = false;

	ev->terminate = false;

	return ev;

}

////////////
// DELETE //
////////////

void
delete_Events (Events ev) {

	free(ev);

}

////////////
// UPDATE //
////////////

void
update_Events (Events ev) {

    // Pour éviter des mouvements fictifs de la souris, on réinitialise les coordonnées relatives
    ev->dx = 0;
    ev->dy = 0;

    // Boucle d'évènements
    while( SDL_PollEvent( &ev->events ) ) {

        // Switch sur le type d'évènement
        switch(ev->events.type) {

            // Cas d'une touche enfoncée
            case SDL_KEYDOWN:
                ev->keys[ev->events.key.keysym.scancode] = true;
            break;

            // Cas d'une touche relâchée
            case SDL_KEYUP:
                ev->keys[ev->events.key.keysym.scancode] = false;
            break;

            // Cas de pression sur un bouton de la souris
            case SDL_MOUSEBUTTONDOWN:
                ev->mouse[ev->events.button.button] = true;
            break;

            // Cas du relâchement d'un bouton de la souris
            case SDL_MOUSEBUTTONUP:
                ev->mouse[ev->events.button.button] = false;
            break;

            // Cas d'un mouvement de souris
            case SDL_MOUSEMOTION:
                ev->x = ev->events.motion.x;
                ev->y = ev->events.motion.y;
                ev->dx = ev->events.motion.xrel;
                ev->dy = ev->events.motion.yrel;
            break;

            // Cas de la fermeture de la fenêtre
            case SDL_WINDOWEVENT:
                if(ev->events.window.event == SDL_WINDOWEVENT_CLOSE)
                    ev->terminate = true;
            break;

            default:
            break;

        }

    }

}

bool
terminate_Events (Events ev) {

	return ev->terminate;

}

////////////
// ACCESS //
////////////

bool
is_pressed_key_Events (Events ev, const SDL_Scancode key) {

	return ev->keys[key];

}

bool
is_pressed_mouse_Events (Events ev, const Uint8 mouse) {

	return ev->mouse[mouse];

}

bool
has_moved_mouse_Events (Events ev) {

	return (! (ev->dx ==0 && ev->dy == 0) );

}

int
get_x_Events (Events ev) {

	return ev->x;

}

int
get_y_Events (Events ev) {

	return ev->y;

}

int
get_dx_Events (Events ev) {

	return ev->dx;

}

int
get_dy_Events (Events ev) {

	return ev->dy;

}

void
display_cursor_Events (bool wanna_display_cursor) {

	if (wanna_display_cursor)
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);

}

void
capture_cursor_Events (bool wanna_capture_cursor) {

	if (wanna_capture_cursor)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);

}