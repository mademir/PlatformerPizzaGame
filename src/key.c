#include "common.h"

static void tick(void);
static void touch(Entity* other);


void initKey(float x, float y, Entity* d, Entity* o)
{
	Entity* e;	//Storing keys as entites

	e = malloc(sizeof(Entity));		//Allocating memory for the key
	memset(e, 0, sizeof(Entity));	//Reseting allocated memory
	stage.entityTail->next = e;		//Add entity to the linked list of entities
	stage.entityTail = e;			//Set the enitity as the last element on the linked list

	e->health = 1;	//Set key health

	e->x = x;		//Set key x to given x
	e->y = y;		//Set key y to given y
	e->target1 = d;	//Door of the key
	e->target2 = o;	//The door on the other end

	e->tick = tick;		//Set key tick function
	e->touch = touch;	//Set key touch function
	e->type = KEY;		//Set entity type

	e->texture = loadTexture("gfx/key.png");	//Set key texture
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);	//Set entity width and height of the entity from the texture
	e->flags = EF_WEIGHTLESS;	//Set flag to weightless as the keys should not be affected by gravity
}

static void tick(void)	//Creates a sin wave motion
{
	self->value += 0.1;

	self->y += sin(self->value);
}

static void touch(Entity* other)	//Touch function for the key
{
	if (self->health > 0 && other == player)	//If the key is not collected and the touching entity is the player
	{
		self->health = 0;	//Destroy the key
		self->target1->value = 1; //Unlock the door this key is for
		self->target2->value = 1; //Unlock the other door this key is for
		playSound(SND_KEY, 1);	//Play key sound on channel 1
	}
}