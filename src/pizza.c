#include "common.h"

static void tick(void);
static void touch(Entity *other);

void initPizza(char *line)
{
	Entity *e;	//Storing pizzas as entites

	e = malloc(sizeof(Entity));		//Allocating memory for the pizza
	memset(e, 0, sizeof(Entity));	//Reseting allocated memory
	stage.entityTail->next = e;		//Add entity to the linked list of entities
	stage.entityTail = e;			//Set the enitity as the last element on the linked list

	sscanf(line, "%*s %f %f", &e->x, &e->y);	//Set the x and y position of the pizza from the given line

	e->health = 1;	//Set pizza health

	e->texture = loadTexture("gfx/pizza.png");				//Load the pizza texture
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);	//Set width and height from the texture
	e->flags = EF_WEIGHTLESS;	//Set the flag to weightless as pizzas should not be affected by gravity
	e->tick = tick;		//Set pizza tick function
	e->touch = touch;	//Set pizza touch function
	e->type = PIZZA;	//Set entity type

	stage.pizzaTotal++;	//Increase the total pizza count as a new one is now initialised
}

static void tick(void)	//Creates a sin wave motion
{
	self->value += 0.1;

	self->y += sin(self->value);
}

static void touch(Entity *other)	//Touch function for pizza
{
	if (self->health > 0 && other == player)	//If the pizza is not collected the entity touching is the player
	{
		self->health = 0;	//Destroy the pizza

		stage.pizzaFound++;	//Increase the number of pizzas found

		if (stage.pizzaFound == stage.pizzaTotal)	//If the final pizza is found
		{
			playSound(SND_PIZZA_DONE, CH_PIZZA);	//Play level complete sound
			
		}
		else
		{
			playSound(SND_PIZZA, CH_PIZZA);	//If the pizza found is not the last, play pizza found sound
		}
	}
}
