#ifndef WINDOW_H
#define WINDOW_H

#include "canvas.h"

#include "common/status.h"

#include <Windows.h>

#define CSRGE_WND_CLASS "CSRGE_WND_CLASS"
#define CSRGE_WND_TITLE "csrge"

// TODO: Should this be abstracted to some input file/functionality?
#define CSRGE_WND_KEYDOWN 0x80
#define CSRGE_KEYDOWN(k) ((k) & CSRGE_WND_KEYDOWN)


// TODO: Is all of this really necessary.

// TODO: Top of file comments.

// Window message handling.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int window_process_messages();

typedef struct
{
	Canvas* canvas;
	
	HWND hwnd;
	HDC hdc;
	BITMAPINFO bitmap;

	int width;
	int height;

	// Event callbacks
	void* ctx; // Set to Engine* so we can use it in the callbacks.
	void (*on_resize)(void*);
	void (*on_keyup)(void*, WPARAM);
	void (*on_lmbdown)(void*);
	
	// Relative mouse movement from raw input.
	int mouse_dx, mouse_dy;

    // Keyboard state
    BYTE keys[256];
	
} Window;

Status window_init(Window* window, Canvas* canvas, void* ctx, int width, int height);

void window_display(Window* window);

void window_destroy(Window* window);


#endif