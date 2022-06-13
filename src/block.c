#include "common.h"

void initBlock(char *line)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->health = 1;
	e->type = BLOCK;

	e->texture = loadTexture("gfx/block.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_SOLID+EF_WEIGHTLESS;
}
