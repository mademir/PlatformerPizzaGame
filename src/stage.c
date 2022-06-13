#include "common.h"

static void logic(void);
static void draw(void);
static void drawHud(void);
float HBx, HBy;
SDL_Color HPColor;
SDL_Texture* noKey, *tutorial;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	noKey = loadTexture("gfx/noKey.png");	//Load the image to be displayed when the near door is locked and player does not have the key
	tutorial = loadTexture("assets/tutorial.png");

	memset(&stage, 0, sizeof(Stage));

	stage.entityTail = &stage.entityHead;

	initEntities();

	initPlayer();

	initMap();

	initButton(PLAY_BTN, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100);		//Initialise play button
	initButton(LEVELS_BTN, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);			//Initialise levels button
	initButton(EXIT_BTN, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100);		//Initialise exit button
}

void clearLevel(void) {
	Entity* e, * prev;

	prev = &stage.entityHead;	//Set previous to entity head

	for (e = stage.entityHead.next; e != NULL; e = e->next) {	//Iterate through the entities
		prev->next = e->next;	//Set the next of the previous to next of the current entity
		free(e);				//Free the current entity
		e = prev;				//Set the previous entity as the current entity
	}

	stage.entityTail = &stage.entityHead;		//Redefine the entity tail

	stage.pizzaFound = stage.pizzaTotal = 0;	//Reset the pizza counts
}

static void logic(void)
{
	doPlayer();

	app.noKeyPos[0] = app.noKeyPos[1] = NULL; //Resetting noKey image position before it is possibly set in doEntities

	doEntities();

	doCamera();
}

static void draw(void)
{
	SDL_RenderFillRect(app.renderer, NULL);
	blit(bg, 0, 0, 0);	//Display the background image

	drawMap();

	if (app.mapNo == 1) blit(tutorial, -stage.camera.x, -stage.camera.y, 0);	//If first level is playing, show tutorial messages

	drawEntities();

	drawHud();

	if (app.noKeyPos[0] != NULL && app.noKeyPos[1] != NULL) blit(noKey, app.noKeyPos[0], app.noKeyPos[1], 1); //If the position is set for displaying noKey image, display the image at the given position
}

static void drawHud(void)
{
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = 35;

	//Calculating health bar position on the screen
	if (stage.camera.x > 0 && stage.camera.x < SCREEN_WIDTH) { //If the camera is in range 0 to maximum camera x 
		HBx = (SCREEN_WIDTH / 2) - 30;	//Set the health bar x to the centre of the screen
	}
	else if (stage.camera.x == 0) {	//If the camera is all the way left
		HBx = player->x - 8;	//Set the helth bar x to be player's x
	}
	else HBx = (SCREEN_WIDTH / 2) - 30 + player->x - 1900; //If the camera is all the way right, set health bar x to centre of th screen plus player x and substract the x position where camera stopped moving

	if (stage.camera.y > 0 && stage.camera.y < 560) { //If the camera is in range 0 to maximum camera y
		HBy = (SCREEN_HEIGHT / 2) - 10 - (player->h / 2);	//Set the health bar y to the centre of the screen
	}
	else if (stage.camera.y == 0) {	//If the camera is all the way up
		HBy = player->y - 10;	//Set the helth bar y to be player's y
	}
	else HBy = (SCREEN_HEIGHT / 2)  + player->y - 930; //If the camera is all the way down, set health bar y to centre of the screen plus player y and substract the y position where camera stopped moving

	SDL_Rect healthBarBg;	//Health bar background rectangle
	healthBarBg.x = HBx - 1;	//Set x to calculated x with offset
	healthBarBg.y = HBy - 11;	//Set y to calculated y with offset
	healthBarBg.w = 62;		//Custom width
	healthBarBg.h = 7;		//Custom height

	SDL_Rect healthBar;	//Health bar health rectangle
	healthBar.x = HBx;	//Set x to calculated x
	healthBar.y = HBy - 10;	//Set y to calculated y with offset
	healthBar.w = (60 * player->health) / TOTAL_HP;	//Sets the width of the health according to the percentage of player's health
	healthBar.h = 5;		//Custom height
	HPColor.g = (200 * player->health) / TOTAL_HP;				//Remove green from the health bar color as health goes down
	HPColor.r = abs(((150 * player->health) / TOTAL_HP) - 255);	//Add red to the health bar color if as health goes down

	SDL_Rect staminaBarBg;	//Stamina bar background rectangle
	staminaBarBg.x = HBx - 1;	//Set x to calculated x with offset
	staminaBarBg.y = HBy - 1;	//Set y to calculated y with offset
	staminaBarBg.w = 62;		//Custom width
	staminaBarBg.h = 7;			//Custom height

	SDL_Rect staminaBar;	//Stamina bar health rectangle
	staminaBar.x = HBx;		//Set x to calculated x
	staminaBar.y = HBy;		//Set y to calculated y
	staminaBar.w = (60 * player->value) / TOTAL_STAMINA;	//Sets the width of the stamina according to the percentage of player's stamina
	staminaBar.h = 5;		//Custom height

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);

	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
	SDL_RenderFillRect(app.renderer, &r);

	SDL_SetRenderDrawColor(app.renderer, 20, 20, 20, 255);
	SDL_RenderFillRect(app.renderer, &healthBarBg);			//Draw health bar background

	SDL_SetRenderDrawColor(app.renderer, HPColor.r, HPColor.g, 0, 255);
	SDL_RenderFillRect(app.renderer, &healthBar);			//Draw health bar

	SDL_SetRenderDrawColor(app.renderer, 20, 20, 20, 255);
	SDL_RenderFillRect(app.renderer, &staminaBarBg);		//Draw stamina bar background

	SDL_SetRenderDrawColor(app.renderer, 0, 100, 255, 255);	//Set stamina bar color to light blue
	SDL_RenderFillRect(app.renderer, &staminaBar);			//Draw blue stamina bar

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

	seconds = app.menu == 2 ? (Ttemp - Tstart) / CLOCKS_PER_SEC : (clock() - Tstart) / CLOCKS_PER_SEC;	//If in the pause menu, set the seconds to difference between the time start to temporary time set when pause menu was opened, else to difference between current time and start time (dividing by clocks per seconds to compare clocks to seconds)
	if (seconds < 0) seconds = 0;	//If by any fault seconds is negative, set it to 0
	drawText(10, 5, 150, 150, 150, TEXT_LEFT, "LEVEL %d", app.mapNo);	//Draw the level number
	drawText(SCREEN_WIDTH - 670, 5, 150, 150, 150, TEXT_RIGHT, "TIME:%.2d:%.2d", seconds / 60, seconds % 60);	//Draw timer with the time elapsed
	drawText(SCREEN_WIDTH - 500, 5, 255, 100, 100, TEXT_RIGHT, "HP:%d/%d", player->health, TOTAL_HP);	//Draw health information on HUD
	drawText(SCREEN_WIDTH - 210, 5, 150, 150, 255, TEXT_RIGHT, "STAMINA:%d/%d", (int)(player->value / 10), TOTAL_STAMINA / 10);	//Draw stamina information on HUD
	drawText(SCREEN_WIDTH - 5, 5, 255, 255, 100, TEXT_RIGHT, "PIZZA:%d/%d", stage.pizzaFound, stage.pizzaTotal);
}
