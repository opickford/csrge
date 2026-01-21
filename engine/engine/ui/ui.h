#ifndef UI_H
#define UI_H


#include "font.h"
#include "text.h"

#include "core/canvas.h"

#include "common/status.h"

// TODO: Why have i done this.
#define MAX_TEXT 100

typedef struct
{
	// Global UI
	Canvas* canvas;
	Font font;

	// Specific widgets
	int text_count;
	Text text[MAX_TEXT];

} UI;

Status UI_init(UI* UI, Canvas* canvas);

void UI_draw(UI* UI, float upscaling_factor);

void UI_destroy(UI* UI);

// Functions for adding UI widgets?

#endif