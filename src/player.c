#include "common.h"

static SDL_Texture *idle_right[10];
static SDL_Texture *idle_left[10];
static SDL_Texture *moving_right[10];
static SDL_Texture *moving_left[10];
static SDL_Texture *jumping_right[10];
static SDL_Texture *jumping_left[10];
static SDL_Texture *attack_right[10];
static SDL_Texture *attack_left[10];
int frame, tempClick, attacking;

void initFrames(void) {
	//Load animation frames

	//Idle right frames
	idle_right[0] = loadTexture("assets/ninja/idle__000.png");
	idle_right[1] = loadTexture("assets/ninja/idle__001.png");
	idle_right[2] = loadTexture("assets/ninja/idle__002.png");
	idle_right[3] = loadTexture("assets/ninja/idle__003.png");
	idle_right[4] = loadTexture("assets/ninja/idle__004.png");
	idle_right[5] = loadTexture("assets/ninja/idle__005.png");
	idle_right[6] = loadTexture("assets/ninja/idle__006.png");
	idle_right[7] = loadTexture("assets/ninja/idle__007.png");
	idle_right[8] = loadTexture("assets/ninja/idle__008.png");
	idle_right[9] = loadTexture("assets/ninja/idle__009.png");

	//Idle left frames
	idle_left[0] = loadTexture("assets/ninja/idle__000_left.png");
	idle_left[1] = loadTexture("assets/ninja/idle__001_left.png");
	idle_left[2] = loadTexture("assets/ninja/idle__002_left.png");
	idle_left[3] = loadTexture("assets/ninja/idle__003_left.png");
	idle_left[4] = loadTexture("assets/ninja/idle__004_left.png");
	idle_left[5] = loadTexture("assets/ninja/idle__005_left.png");
	idle_left[6] = loadTexture("assets/ninja/idle__006_left.png");
	idle_left[7] = loadTexture("assets/ninja/idle__007_left.png");
	idle_left[8] = loadTexture("assets/ninja/idle__008_left.png");
	idle_left[9] = loadTexture("assets/ninja/idle__009_left.png");

	//Moving right frames
	moving_right[0] = loadTexture("assets/ninja/run__000.png");
	moving_right[1] = loadTexture("assets/ninja/run__001.png");
	moving_right[2] = loadTexture("assets/ninja/run__002.png");
	moving_right[3] = loadTexture("assets/ninja/run__003.png");
	moving_right[4] = loadTexture("assets/ninja/run__004.png");
	moving_right[5] = loadTexture("assets/ninja/run__005.png");
	moving_right[6] = loadTexture("assets/ninja/run__006.png");
	moving_right[7] = loadTexture("assets/ninja/run__007.png");
	moving_right[8] = loadTexture("assets/ninja/run__008.png");
	moving_right[9] = loadTexture("assets/ninja/run__009.png");

	//Moving left frames
	moving_left[0] = loadTexture("assets/ninja/moving_left__000.png");
	moving_left[1] = loadTexture("assets/ninja/moving_left__001.png");
	moving_left[2] = loadTexture("assets/ninja/moving_left__002.png");
	moving_left[3] = loadTexture("assets/ninja/moving_left__003.png");
	moving_left[4] = loadTexture("assets/ninja/moving_left__004.png");
	moving_left[5] = loadTexture("assets/ninja/moving_left__005.png");
	moving_left[6] = loadTexture("assets/ninja/moving_left__006.png");
	moving_left[7] = loadTexture("assets/ninja/moving_left__007.png");
	moving_left[8] = loadTexture("assets/ninja/moving_left__008.png");
	moving_left[9] = loadTexture("assets/ninja/moving_left__009.png");

	//Jumping right frames
	jumping_right[0] = loadTexture("assets/ninja/jump__000.png");
	jumping_right[1] = loadTexture("assets/ninja/jump__001.png");
	jumping_right[2] = loadTexture("assets/ninja/jump__002.png");
	jumping_right[3] = loadTexture("assets/ninja/jump__003.png");
	jumping_right[4] = loadTexture("assets/ninja/jump__004.png");
	jumping_right[5] = loadTexture("assets/ninja/jump__005.png");
	jumping_right[6] = loadTexture("assets/ninja/jump__006.png");
	jumping_right[7] = loadTexture("assets/ninja/jump__007.png");
	jumping_right[8] = loadTexture("assets/ninja/jump__008.png");
	jumping_right[9] = loadTexture("assets/ninja/jump__009.png");

	//Jumping left frames
	jumping_left[0] = loadTexture("assets/ninja/jump__000_left.png");
	jumping_left[1] = loadTexture("assets/ninja/jump__001_left.png");
	jumping_left[2] = loadTexture("assets/ninja/jump__002_left.png");
	jumping_left[3] = loadTexture("assets/ninja/jump__003_left.png");
	jumping_left[4] = loadTexture("assets/ninja/jump__004_left.png");
	jumping_left[5] = loadTexture("assets/ninja/jump__005_left.png");
	jumping_left[6] = loadTexture("assets/ninja/jump__006_left.png");
	jumping_left[7] = loadTexture("assets/ninja/jump__007_left.png");
	jumping_left[8] = loadTexture("assets/ninja/jump__008_left.png");
	jumping_left[9] = loadTexture("assets/ninja/jump__009_left.png");

	//Attacking right frames
	attack_right[0] = loadTexture("assets/ninja/throw__000.png");
	attack_right[1] = loadTexture("assets/ninja/throw__001.png");
	attack_right[2] = loadTexture("assets/ninja/throw__002.png");
	attack_right[3] = loadTexture("assets/ninja/throw__003.png");
	attack_right[4] = loadTexture("assets/ninja/throw__004.png");
	attack_right[5] = loadTexture("assets/ninja/throw__005.png");
	attack_right[6] = loadTexture("assets/ninja/throw__006.png");
	attack_right[7] = loadTexture("assets/ninja/throw__007.png");
	attack_right[8] = loadTexture("assets/ninja/throw__008.png");
	attack_right[9] = loadTexture("assets/ninja/throw__009.png");

	//Attacking left frames
	attack_left[0] = loadTexture("assets/ninja/throw__000_left.png");
	attack_left[1] = loadTexture("assets/ninja/throw__001_left.png");
	attack_left[2] = loadTexture("assets/ninja/throw__002_left.png");
	attack_left[3] = loadTexture("assets/ninja/throw__003_left.png");
	attack_left[4] = loadTexture("assets/ninja/throw__004_left.png");
	attack_left[5] = loadTexture("assets/ninja/throw__005_left.png");
	attack_left[6] = loadTexture("assets/ninja/throw__006_left.png");
	attack_left[7] = loadTexture("assets/ninja/throw__007_left.png");
	attack_left[8] = loadTexture("assets/ninja/throw__008_left.png");
	attack_left[9] = loadTexture("assets/ninja/throw__009_left.png");
}

void initPlayer(void)
{
	player = malloc(sizeof(Entity));	//Allocating memory for the player
	memset(player, 0, sizeof(Entity));	//Reseting allocated memory
	stage.entityTail->next = player;	//Add entity to the linked list of entities
	stage.entityTail = player;			//Set the enitity as the last element on the linked list

	player->health = TOTAL_HP;	//Set player health to total health points
	player->facing = RIGHT;		//Set initial facing flag to right
	player->x = 2*TILE_SIZE;			//Start x position on the grid
	player->y = 2*TILE_SIZE-player->h;	//Start y position on the grid (removing height from y position to match the tiles y)
	player->speed = 1;					//Set initial speed multiplier
	player->type = PLAYER;				//Set type to player
	player->value = TOTAL_STAMINA;		//Set stamina to total stamina
	
	

	player->texture = idle_right[0];	//Set the initial frame
	frame = 0;	//Set initial frame number

	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);	//Set width and height from the loaded texture
}

void doPlayer(void)	//Player function to run every frame
{
	player->dx = 0;	//Reset x speed
	player->speed = 1;	//Reset player speed multiplier to default

	frame = (frame + 1) % 20;	//Increase frame number (goes back to 0 when reaches 20)
	player->texture = (player->facing == RIGHT) ? idle_right[frame / 2] : idle_left[frame / 2];	//Set the idle frame according to the frame number

	if ((app.keyboard[SDL_SCANCODE_LSHIFT] || app.keyboard[SDL_SCANCODE_RSHIFT]) && player->value > 0) {	//If either shift is pressed and the player has stamina
		player->speed = 2;		//Double the player speed multiplier
		player->value -= 5;		//Decrease the stamina
	}

	if (player->speed == 1 && player->value < TOTAL_STAMINA) player->value++;	//If player has the default speed and is missing stamina, reload stamina

	if (app.keyboard[SDL_SCANCODE_A] || app.keyboard[SDL_SCANCODE_LEFT])	//If A key or the left key is pressed
	{
		
		player->dx = -PLAYER_MOVE_SPEED * player->speed;	//Set player x speed to negative player speed times the speed multiplier
		player->facing = LEFT;	//Change facing flag to left

		player->texture = moving_left[frame / 2];	//Set the moving left frame according to the frame number
	}

	if (app.keyboard[SDL_SCANCODE_D] || app.keyboard[SDL_SCANCODE_RIGHT])	//If D key or the right key is pressed
	{
		player->dx = PLAYER_MOVE_SPEED * player->speed;		//Set player x speed to positive player speed times the speed multiplier
		player->facing = RIGHT;	//Change facing flag to right

		player->texture = moving_right[frame / 2];	//Set the moving right frame according to the frame number
	}

	if ((app.keyboard[SDL_SCANCODE_SPACE] || app.keyboard[SDL_SCANCODE_W] || app.keyboard[SDL_SCANCODE_UP])&& player->isOnGround)	//If the space key, up key or W key is pressed and the player is on the ground
	{
		player->riding = NULL;	//Set riding to NULL as when jumped, player will not be riding any entity

		player->dy = -20 * player->speed;	//Give player an amount of negative y speed (to go up) times speed multiplier

		playSound(SND_JUMP, CH_PLAYER);		//Play jumping sound on player channel
	}

	if (app.keyboard[SDL_SCANCODE_ESCAPE]) {	//If the escape key is pressed
		app.menu = 2;		//Set the menu flag to pause menu
		SDL_ShowCursor(1);	//Show the cursor
		app.keyboard[SDL_SCANCODE_ESCAPE] = 0;	//Reset keyboard input for escape key
		Ttemp = clock();	//Set the temporary time to stop the timer in pause menu
	}

	
	if (tempClick != app.mouseClick && app.mouseClick == 1)	//If the state of the click changes (if mouse button clicked)
	{
		attacking = 1;	//Set attacking flag true
		frame = 0;		//Reset frame
	}

	tempClick = app.mouseClick;	//Set the temorary click flag to current mouse click to be able to detect the change in mouse click state on the next iteration

	if (player->dy < 0) player->texture = (player->facing == RIGHT) ? jumping_right[abs((int)((-1 * player->dy) / 5 - 4))] : jumping_left[abs((int)((-1 * player->dy) / 5 - 4))];	//Iterate through jumping up animation y speed is negative (according to player's direction)
	if (player->dy > 0) player->texture = (player->facing == RIGHT) ? jumping_right[(int)(player->dy / (18/4.9) + 5)] : jumping_left[(int)(player->dy / (18 / 4.9) + 5)];			//Iterate through jumping down animation y speed is positive (according to player's direction)
	
	if (attacking) {	//If attacking flag is on
		player->texture = (player->facing == RIGHT) ? attack_right[frame / 2] : attack_left[frame / 2];	//Set the correct frame according to player's direction and the frame number
		if (frame == 7) spawnKunai(player->x + 15, player->y + 30, (player->facing == RIGHT) ? 1 : 0, 1);	//Spawn a kunai at the centre of the player on the same direction as the player if on the 7th frame
		if (frame == 19) {	//On frame 19
			attacking = 0;	//Set attacking flag 0
			frame = 0;		//Reset the frame
		}
	}

	if (player->riding) {	//If player is on top of an entity
		if (player->riding->ex && !player->riding->ey) {	//If the entity is an enemy (has ex but no ey)
			player->riding->health--;	//Decrease enemy health (kills the enemy when jumped on its head)
			player->riding = NULL;		//Clear riding
			player->dy = -15;			//Give player some negative y speed to make it hop
		}
	}
}
