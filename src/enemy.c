#include "common.h"

static void tick(void);

static SDL_Texture* moving_right[10];
static SDL_Texture* moving_left[10];
static SDL_Texture* attack_right[10];
static SDL_Texture* attack_left[10];

void initFramesE(void) {
	//Loading animation frames

	//Moving right
	moving_right[0] = loadTexture("assets/ninja/enemy_run__000.png");
	moving_right[1] = loadTexture("assets/ninja/enemy_run__001.png");
	moving_right[2] = loadTexture("assets/ninja/enemy_run__002.png");
	moving_right[3] = loadTexture("assets/ninja/enemy_run__003.png");
	moving_right[4] = loadTexture("assets/ninja/enemy_run__004.png");
	moving_right[5] = loadTexture("assets/ninja/enemy_run__005.png");
	moving_right[6] = loadTexture("assets/ninja/enemy_run__006.png");
	moving_right[7] = loadTexture("assets/ninja/enemy_run__007.png");
	moving_right[8] = loadTexture("assets/ninja/enemy_run__008.png");
	moving_right[9] = loadTexture("assets/ninja/enemy_run__009.png");

	//Moving left
	moving_left[0] = loadTexture("assets/ninja/enemy_moving_left__000.png");
	moving_left[1] = loadTexture("assets/ninja/enemy_moving_left__001.png");
	moving_left[2] = loadTexture("assets/ninja/enemy_moving_left__002.png");
	moving_left[3] = loadTexture("assets/ninja/enemy_moving_left__003.png");
	moving_left[4] = loadTexture("assets/ninja/enemy_moving_left__004.png");
	moving_left[5] = loadTexture("assets/ninja/enemy_moving_left__005.png");
	moving_left[6] = loadTexture("assets/ninja/enemy_moving_left__006.png");
	moving_left[7] = loadTexture("assets/ninja/enemy_moving_left__007.png");
	moving_left[8] = loadTexture("assets/ninja/enemy_moving_left__008.png");
	moving_left[9] = loadTexture("assets/ninja/enemy_moving_left__009.png");

	//Throw kunai right
	attack_right[0] = loadTexture("assets/ninja/enemy_throw__000.png");
	attack_right[1] = loadTexture("assets/ninja/enemy_throw__001.png");
	attack_right[2] = loadTexture("assets/ninja/enemy_throw__002.png");
	attack_right[3] = loadTexture("assets/ninja/enemy_throw__003.png");
	attack_right[4] = loadTexture("assets/ninja/enemy_throw__004.png");
	attack_right[5] = loadTexture("assets/ninja/enemy_throw__005.png");
	attack_right[6] = loadTexture("assets/ninja/enemy_throw__006.png");
	attack_right[7] = loadTexture("assets/ninja/enemy_throw__007.png");
	attack_right[8] = loadTexture("assets/ninja/enemy_throw__008.png");
	attack_right[9] = loadTexture("assets/ninja/enemy_throw__009.png");

	//Throw kunai left
	attack_left[0] = loadTexture("assets/ninja/enemy_throw__000_left.png");
	attack_left[1] = loadTexture("assets/ninja/enemy_throw__001_left.png");
	attack_left[2] = loadTexture("assets/ninja/enemy_throw__002_left.png");
	attack_left[3] = loadTexture("assets/ninja/enemy_throw__003_left.png");
	attack_left[4] = loadTexture("assets/ninja/enemy_throw__004_left.png");
	attack_left[5] = loadTexture("assets/ninja/enemy_throw__005_left.png");
	attack_left[6] = loadTexture("assets/ninja/enemy_throw__006_left.png");
	attack_left[7] = loadTexture("assets/ninja/enemy_throw__007_left.png");
	attack_left[8] = loadTexture("assets/ninja/enemy_throw__008_left.png");
	attack_left[9] = loadTexture("assets/ninja/enemy_throw__009_left.png");

}

void initEnemy(char* line)
{
	Entity* e;	//Storing enemies as entites

	e = malloc(sizeof(Entity));		//Allocating memory for the enemy
	memset(e, 0, sizeof(Entity));	//Reseting allocated memory
	stage.entityTail->next = e;		//Add entity to the linked list of entities
	stage.entityTail = e;			//Set the enitity as the last element on the linked list

	sscanf(line, "%*s %f %f %f", &e->sx, &e->sy, &e->ex);	//Get enemy start x, y and range from the line

	e->health = 1;		//Set enemy health

	e->x = e->sx;		//Set initial x to start x
	e->y = e->sy;		//Set initial y to enemy y

	e->tick = tick;		//Set enemy tick function
	e->type = ENEMY;	//Set entity type

	e->texture = loadTexture("assets/ninja/idle__000.png");		//Set initial texture
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);		//Get width and height from the loaded texture
	e->flags = EF_SOLID + EF_PUSH;			//Set solid and push flags as enemies should have collisions

	e->speed = ENEMY_MOVE_SPEED; //Set initial speed
	e->frame = e->facing = 0; //Set initial frame and facing

	
}

static void tick(void)	//Tick function for enemies
{
	if (self->x < (self->sx - self->ex / 2)) self->speed = ENEMY_MOVE_SPEED;		//Turns the other way when goes out of range from the left where self->ex is the range.
	else if (self->x > (self->sx + self->ex / 2)) self->speed = -ENEMY_MOVE_SPEED;	//Turns the other way when goes out of range from the right where self->ex is the range.
	self->dx = self->speed;	//Set the enemy speed to the calculated move speed
	self->frame = (self->frame + 1) % 30;	//Set the frame
	self->texture = (self->dx > 0) ? moving_right[self->frame / 3] : moving_left[self->frame / 3]; //Set the texture according to the frame and speed
	self->temp = self->inSight; //Set the state to in sight flag
	self->inSight = ((abs(player->x - self->x) < ENEMY_SIGHT) && (abs(player->y - self->y) < 30)) ? 1 : 0;	//Set the flag if the player enters the sight
	if (self->temp != self->inSight) self->frame = 0; //If the state has been changed, reset the frame as the animation will change

	self->facing = (self->dx > 0) ? 1 : 0; //Set facing flag
	
	if (self->inSight) { //If the player is in sight
		self->dx = 0;	//Stop moving
		if (self->frame == 10) {
			spawnKunai(self->x + 15, self->y + 30, (player->x - self->x > 0), 0);
		}//spawnKunai(player->x + 15, player->y + 30, (player->facing == RIGHT) ? 1 : 0, 1);}//Spawns a kunai at the centre of the enemy in the direction of the player
		self->texture = (player->x - self->x > 0) ? attack_right[self->frame / 3] : attack_left[self->frame / 3];	//Play attacking animation
	}
}