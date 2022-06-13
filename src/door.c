#include "common.h"

static void tick(void);
static void touch(Entity* other);
static SDL_Texture* door[4];

void initFramesD(void) {//Load frames for door opening/closing animations
	door[0] = loadTexture("assets/map/objects/doorLocked.png");
	door[1] = loadTexture("assets/map/objects/doorUnlocked0.png");
	door[2] = loadTexture("assets/map/objects/doorUnlocked1.png");
	door[3] = loadTexture("assets/map/objects/doorOpen.png");
}

void initDoor(char* line)
{
	float tempKeyX, tempKeyY;	//Temporary integers to store the x and y positions of the key

	Entity* e;	//Storing door 1 of this set as an entity

	e = malloc(sizeof(Entity));		//Allocate memory for the entity
	memset(e, 0, sizeof(Entity));	//Reset the allocated memory
	stage.entityTail->next = e;		//Add entity to the linked list of entities
	stage.entityTail = e;			//Set the enitity as the last element on the linked list

	e->health = 1;	//Set the health of the entity

	sscanf(line, "%*s %f %f %f %f %f %f", &e->x, &e->y, &e->ex, &e->ey, &tempKeyX, &tempKeyY);	//Get x and y positions for the door 1 and 2 and for the key to these doors from the given line

	e->tick = tick;		//Set the tick function for the door
	e->touch = touch;	//Set the touch function for the door
	e->type = DOOR;		//Set the type of the entity
	e->frame = 0;		//Set initial frame
	
	

	e->texture = door[0];	//Set the initial texture of the door to locked door frame
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);		//Get the width and the height values from the texture
	e->flags = EF_WEIGHTLESS;	//Set the flag of the door to weghtless as the door should not be affexted by gravity

	e->x = e->x * TILE_SIZE - e->w / 2;		//Transforming given x value to actual x position for this door (door 1)
	e->y = e->y * TILE_SIZE - e->h;			//Transforming given y value to actual y position for this door (door 1)
	e->ex = e->ex * TILE_SIZE - e->w / 2;	//Transforming given x value to actual x position for the other door (door 2)
	e->ey = e->ey * TILE_SIZE - e->h;		//Transforming given y value to actual y position for the other door (door 2)

	//The door on the other end

	Entity* o;	//Storing door 2 of this set as an entity

	o = malloc(sizeof(Entity));		//Allocate memory for the entity
	memset(o, 0, sizeof(Entity));	//Reset the allocated memory
	stage.entityTail->next = o;		//Add entity to the linked list of entities
	stage.entityTail = o;			//Set the enitity as the last element on the linked list

	o->health = 1;	//Set the health of the entity

	o->x = e->ex;	//Set the x position of door 2 to the door 2 position stored in door 1
	o->y = e->ey;	//Set the y position of door 2 to the door 2 position stored in door 1
	o->ex = e->x;	//Set the x position for the door on the other end to x position of door 1
	o->ey = e->y;	//Set the y position for the door on the other end to y position of door 1

	o->tick = tick;		//Set the tick function for the door
	o->touch = touch;	//Set the touch function for the door
	o->type = DOOR;		//Set the type of the entity
	o->frame = 0;		//Set initial frame

	o->texture = door[0];	//Set the initial texture of the door to locked door frame
	SDL_QueryTexture(e->texture, NULL, NULL, &o->w, &o->h);		//Get the width and the height values from the texture
	o->flags = EF_WEIGHTLESS;	//Set the flag of the door to weghtless as the door should not be affexted by gravity

	//Initialise the key for the doors
	initKey(tempKeyX, tempKeyY, e, o);	//Call initKey functions to initialise the key for the doors. Give the stored x, y values for the key and the initialised doors as arguments for the function called
}

static void tick(void)	//Tick function for the doors
{
	if ((abs(player->x - (self->x + self->w / 2)) < 150 && abs(player->y - (self->y + self->h / 2)) < 100)) {	//If player is near
		if (self->value == 1) {	//If the door is unlocked
			if (self->frame == 1) playSound(SND_OPEN_DOOR, 1);	//Play door opening sound on channel 1
				if (self->frame < 15) {	//Until the last frame reached
					self->frame++;							//Go to the next frame
					self->texture = door[self->frame / 5];	//Set the frame as the texture (Creates the animation for opening the door)
				}
			}
			else {		//If the player is close but the door is locked
				app.noKeyPos[0] = self->x - stage.camera.x + self->w / 2;	//Set the x position for the noKey image
				app.noKeyPos[1] = self->y - stage.camera.y - 20;			//Also set the y position for the noKey image
			}
	}
	else {	//If the player is away
		if (self->frame == 14) playSound(SND_CLOSE_DOOR, 1);	//Play door closing sound on channel 1 when frames goes down by one to 14
		if (self->frame > 0) {	//Until the first frame reached
			self->frame--;							//Go to the previous frame
			self->texture = door[self->frame / 5];	//Set the frame as the texture (Creates the animation for closing the door)
		}
	}
}

static void touch(Entity* other)	//Touch function for the doors
{
	if (other == player && (abs((player->x + player->w / 2) - (self->x + self->w / 2)) < 10 && abs((player->y + player->h) - (self->y + self->h)) < 10) && self->value == 1){	//If it is the player touching and the player is close to the centre of the door and close to the ground, and the door is unlocked
		other->x = self->ex + (self->w / 2) - (other->w / 2) + ((other->dx > 0) ? 15 : -15);	//Set player x to other door's location. If player came from the left teleport to the other door's left visa versa
		other->y = self->ey + self->h - other->h;			//Set player y to other door's location
	}
}