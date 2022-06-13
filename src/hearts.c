#include "common.h"

static void tick(void);
static void touch(Entity *other);

void initHeart(char *line)
{
	Entity *e;	//Storing hearts as entites

	e = malloc(sizeof(Entity));		//Allocating memory for the heart
	memset(e, 0, sizeof(Entity));	//Reseting allocated memory
	stage.entityTail->next = e;		//Add entity to the linked list of entities
	stage.entityTail = e;			//Set the enitity as the last element on the linked list

	sscanf(line, "%*s %f %f", &e->x, &e->y);	//Set the x and y positions of the entity from the line

	e->health = 1;		//Set entity health
	e->type = HEART;	//Set entity type

	e->texture = loadTexture("gfx/heart.png");		//Load heart texture
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);	//Set width and height from the texture
	e->flags = EF_WEIGHTLESS;	//Set the weightless flag as hearts should not be affected by gravity
	e->tick = tick;		//Set tick function for the heart
	e->touch = touch;	//Set touch function for the entity
}

static void tick(void)	//Creates a sin wave motion
{
	self->value += 0.1;

	self->y += sin(self->value);
}

static void touch(Entity *other)	//Touch function for the heart
{
	if (self->health > 0 && other == player && player->health < TOTAL_HP) //If player has missing health
	{
		self->health = 0;	//Destroy the heart
		player->health++;	//Increase player health
		playSound(SND_HEART, 1);	//Play heart sound on channel 1
	}
}
