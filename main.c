#include "common.h"

static void capFrameRate(long* then, float* remainder);

SDL_Texture* bg, *overlay;

int main(){
	long then;
	float remainder;

	memset(&app, 0, sizeof(App));
	app.textureTail = &app.textureHead;

	initSDL();

	atexit(cleanup);

	app.mapNo = 1;		//Set the map no to first map
	initTiles();
	initFrames();
	initFramesE();
	initFramesD();
	bg = loadTexture("assets/bg.png");
	overlay = loadTexture("assets/overlay.png");

	initGame();

	initStage();

	then = SDL_GetTicks();

	remainder = 0; 
	
	app.menu = 1;		//Set the menu flag on to start from the main menu
	SDL_ShowCursor(1);	//Show the cursor

	while (1)
	{
		prepareScene();

		doInput();

		if (app.menu == NULL){		//If the menu flag is not set
			app.delegate.logic();	//Do game logic
		}
		
		app.delegate.draw();	//Do draw

		if (app.menu == 1) {	//If menu flag is set to main menu
			blit(bg, 0, 0, 0);	//Display the background image
			drawText(SCREEN_WIDTH / 2, 100, 10, 10, 10, TEXT_CENTER, "MAIN MENU");		//Draw main menu text
			doButton();	//Do buttons
		}

		if (app.menu == 2)  {	//If menu flag is set to pause menu
			blit(overlay, 0, 0, 0);	//Display the overlay
			drawText(SCREEN_WIDTH / 2, 100, 255, 255, 255, TEXT_CENTER, "PAUSE MENU");	//Draw main menu text
			doButton();	//Do buttons
			if (app.keyboard[SDL_SCANCODE_ESCAPE]) {	//If the escape key is pressed
				app.menu = NULL;	//Reset the menu flag to continue the game
				SDL_ShowCursor(0);	//Hide the cursor
				app.keyboard[SDL_SCANCODE_ESCAPE] = 0;	//Reset keyboard input for escape key
				Tstart += clock() - Ttemp;	//Add the time elapsed while on pause menu to start time
			}
		}

		if (app.menu == 3) {	//If menu flag is set to levels menu
			blit(bg, 0, 0, 0);	//Display the background image
			drawText(SCREEN_WIDTH / 2, 100, 10, 10, 10, TEXT_CENTER, "LEVELS MENU");		//Draw levels menu text
			doButton();	//Do buttons
		}

		if (stage.pizzaFound == stage.pizzaTotal && app.menu == NULL)	//If the level is finished and the game is running
		{
			if (app.mapNo < MAX_LEVEL) {	//If it is not the last level
				app.mapNo++;	//Increase map no
				clearLevel();	//Clear the level before start playing
				initEntities();	//Reinitialise entities
				initPlayer();	//Reinitialise player
				initMap();		//Reinitialise map
				Tstart = clock();//Start the timer
				seconds = 0;	//Reset counted seconds
			}
			else {	//If the last map is played
				app.menu = 1;		//Go back to the main menu
				app.mapNo = 1;		//Set the level to the first level
				SDL_ShowCursor(1);	//Show the cursor
			}
		}

		presentScene();
		
		capFrameRate(&then, &remainder);
	}

	return 0;
}

static void capFrameRate(long* then, float* remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)* remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}
