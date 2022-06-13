#include "common.h"

static void tick(void);
static void touch(Entity* other);


void spawnKunai(int sx, int sy, int direction, int from)
{
	Entity* e;						//Make an entity for the kunai

	e = malloc(sizeof(Entity));		//Allocate memory for the entity
	memset(e, 0, sizeof(Entity));	//Clear the allocated memory
	stage.entityTail->next = e;		//Add entity to linked list
	stage.entityTail = e;			//Make the entity the last item on the linked list
	
	e->health = 1;			//Set entity health

	e->sx = sx;				//Set the given start x position
	e->sy = sy;				//Set the given start y position
	e->ex = direction ? sx + THROW_RANGE : sx - THROW_RANGE;	//According to the given direction, set the limit of the kunai from the start position and the range
	e->x = e->sx;				//Set the initial x to start x
	e->y = e->sy;				//Set the initial y to start y
	e->facing = direction;		//Set the facing flag of the kunai to the given direction
	e->value = (float)from;		//Set the value flag to given "from" to represent its owner (player or enemy)

	e->tick = tick;			//Set the tick function for the kunai
	e->touch = touch;		//Set the touch function for the kunai
	e->type = KUNAI;		//Set the type of entity as kunai

	e->texture = (direction) ? loadTexture("assets/ninja/kunai.png") : loadTexture("assets/ninja/kunai_left.png");	//Load the texture according to kunai's direction
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);		//Get width and height from the loaded texture
	e->flags = EF_WEIGHTLESS;		//Set flag as weightless as kunai should not be effected by gravity

	playSound(SND_KUNAI, 1);	//Play kunai sound on channel 1
}

static void tick(void)	//Tick function for kunai
{
	if (self->facing && self->x < self->ex) self->dx = KUNAI_SPEED;			//If direction is right, set positive speed
	else if (!self->facing && self->x > self->ex) self->dx = -KUNAI_SPEED;	//If direction is left, set negative speed
	else self->health = 0;													//If kunai is out of its range, destroy the kunai
}

static void touch(Entity* other)	//Touch function for kunai
{
	if (other == player && (int)self->value != 1)	//If a kunai from the enemy is touching the player
	{
		if (self->health > 0) player->health--;	//Decrease player health
		self->health = 0;						//Destroy kunai
		playSound(SND_HIT, 1);					//Play hit sound on channel 1
		if (player->health == 0) {	//If player has no health left
			app.menu = 1;		//Go back to the main menu
			SDL_ShowCursor(1);	//Show the cursor
		}
	}
	else if (other->type == ENEMY && (int)self->value == 1) {	//If kunai from player is touching enemy
		if (self->health > 0) other->health--;	//Decrease enemy health
		self->health = 0;						//Destroy kunai
		playSound(SND_HIT, 1);					//Play hit sound on channel 1
	}
}