#ifndef ENGINE_H
#define ENGINE_H

#include "scene.h"

#include "window.h"
#include "resources.h"
#include "components.h"

#include "UI/UI.h"

// TODO: These need to be refactored.
#include "renderer/renderer.h"
#include "renderer/render.h"

#include "common/status.h"

#include <cecs/ecs.h>


typedef enum input_mode
{
    INPUT_MODE_UI,
    INPUT_MODE_NOCLIP,
    INPUT_MODE_GAME,
    INPUT_MODE_INVALID
} InputMode;

typedef struct
{
    CECS* ecs;

    // TODO: Defining these in the engine struct feels awful, should be a static?
    CECS_ViewId render_view_id;
    CECS_ViewId lighting_view_id;
    CECS_ViewId physics_view_id;

    CECS_ViewId moving_collider_view_id;
    CECS_ViewId static_collider_view_id;

	// Engine components.
	Window window;
	UI UI;
	Renderer renderer;
	Resources resources; // Works fine for now, potentially something to refactor.
    Physics physics;

	// Scene data. - I don't think the engine needs to manage multiple.
    // TODO: Only manage one scene.
	Scene scene;

    // TODO: Stuff like this is private?

	// Engine settings
	int running;

	// TODO: Move these somewhere?
    InputMode input_mode;
	float upscaling_factor;

	// TODO: Allow the user to set callbacks just like the window class.

} Engine;

// Main API
Status engine_init(Engine* engine, int window_width, int window_height);

void engine_run(Engine* engine);

void engine_destroy(Engine* engine);

// Public engine events that the game should define.
void engine_on_init(Engine* engine);

void engine_before_physics(Engine* engine, float dt);
void engine_after_physics(Engine* engine, float physics_alpha);

void engine_on_keyup(Engine* engine, WPARAM wParam);

void engine_on_lmbdown(Engine* engine);

// Internal functions


// TODO: Some sort of input handler? Fine here for now.
void engine_handle_input(Engine* engine, float dt);

// Private window events.
static void engine_on_resize(void* ctx);

static void engine_process_keyup(void* ctx, WPARAM wParam);
static void engine_process_lmbdown(void* ctx); // TODO: I don't really like this naming 'lmbdown'

#endif