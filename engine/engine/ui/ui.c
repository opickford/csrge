#include "UI.h"

Status UI_init(UI* UI, Canvas* canvas)
{
	Status status = font_init(&UI->font);
	if (STATUS_OK != status)
	{
		return status;
	}

	UI->canvas = canvas;

	return STATUS_OK;
}

void UI_draw(UI* UI, float upscaling_factor)
{
	for (int i = 0; i < UI->text_count; ++i)
	{
		// TODO: Text needs to be scaled. Or how do I do it not scaled.
		text_draw(UI->canvas, &UI->text[i], &UI->font, upscaling_factor);
	}
}

void UI_destroy(UI* UI)
{

}
