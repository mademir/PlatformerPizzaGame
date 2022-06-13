#include "common.h"

static void tick(void);
SDL_Texture* button_default;
SDL_Texture* button_hovered;

void initButton(int button, float x, float y) {
	Button *b;	//Create a button pointer

	b = malloc(sizeof(Button));		//Allocate memory for the button
	memset(b, 0, sizeof(Button));	//Reset the allocated memory

	b->x = x;	//Set button x position
	b->y = y;	//Set button y position

	button_default = loadTexture("gfx/button.png");	//Load default button image
	button_hovered = loadTexture("gfx/button_hovered.png");	//Load hovered button image

	b->texture = button_default;	//Set the initial image to default button

	SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);	//Set w and h of the button from the image

	app.buttons[button] = b;	//Assign the button in app buttons
}

void doButton(void) {	//Iterates through the buttons and takes specific actions for each button if hovered or clicked. Also draws the buttons
	for (int i = 0; i < MAX_BUTTONS; i++) {	//For each button
		app.buttons[i]->hovered = 0;	//Reset hovered flagolor blue
		app.buttons[i]->texture = button_default;	//Reset button image to default

		int x, y;	//To store the x, y positions of the mouse currently
		SDL_GetMouseState(&x, &y);	//Get current mouse position and store it inside x, y

		if (x >= app.buttons[i]->x - app.buttons[i]->w / 2 && x <= app.buttons[i]->x + app.buttons[i]->w / 2 && y >= app.buttons[i]->y - app.buttons[i]->h / 2 && y <= app.buttons[i]->y + app.buttons[i]->h / 2) {	//If the cursor is inside the button

			app.buttons[i]->texture = button_hovered;	//Set the button image to hovered button image

			if (app.mouseClick) {	//If the mouse is clicked
				if (app.menu == 3) {	//If on the level select menu
					app.mapNo = i + 1;	//Set map no to clicked button no (plus 1 as the button no starts from 0 and map no starts from 1)
					clearLevel();	//Clear the level before start playing
					initEntities();	//Reinitialise entities
					initPlayer();	//Reinitialise player
					initMap();		//Reinitialise map
					app.menu = NULL;	//Reset the menu flag
					SDL_ShowCursor(0);	//Hide the cursor
					app.mouseClick = 0;	//Reset mouse click
					Tstart = clock();//Start the timer
					seconds = 0;	//Reset counted seconds
					continue;
				}

				switch (i)	//Switch statement for the button types
				{
				case PLAY_BTN:			//If the button is the play button
					if (app.menu == 1) {//If on the main menu
						clearLevel();	//Clear the level before start playing
						initEntities();	//Reinitialise entities
						initPlayer();	//Reinitialise player
						initMap();		//Reinitialise map
						Tstart = clock();//Start the timer
						seconds = 0;	//Reset counted seconds
					}
					if (app.menu == 2) Tstart += clock() - Ttemp;	//Add the time elapsed while on pause menu to start time if this is the pause menu
					app.menu = NULL;	//Reset the menu flag
					SDL_ShowCursor(0);	//Hide the cursor
					app.mouseClick = 0;	//Reset mouse click
					break;

				case LEVELS_BTN:	//If the button is levels button
					app.menu = 3;	//Set the menu to level select menu
					app.mouseClick = 0;	//Reset mouse click
					break;

				case EXIT_BTN:			//If the button is the exit button
					if (app.menu == 2) {	//If the menu is the pause menu
						app.menu = 1;		//Go to main menu instead of exiting
						app.mouseClick = 0;	//Reset the mouse input
						break;
					}
					exit(1);			//Exit the game
					break;

				default:
					break;
				}
			}
		}

		//Drawing the button

		blit(app.buttons[i]->texture, app.buttons[i]->x, app.buttons[i]->y, 1);	//Display the button image

		char text[100];	//To store the button text

		switch (i)	//By the index of the button
		{
		case PLAY_BTN:				//If the button is the play button
			strcpy(text, "PLAY");	//Set the button text accordingly
			if (app.menu == 2) strcpy(text, "CONTINUE");	//If the menu is the pause menu, overwrite the text accordingly
			if (app.menu == 3) strcpy(text, "LEVEL 1");		//If the menu is the levels menu, overwrite the text accordingly
			break;

		case LEVELS_BTN:			//If the button is the levels button
			strcpy(text, "LEVELS");	//Set the button text accordingly
			if (app.menu == 3) strcpy(text, "LEVEL 2");		//If the menu is the levels menu, overwrite the text accordingly
			break;

		case EXIT_BTN:				//If the button is the exit button
			strcpy(text, "EXIT");	//Set the button text accordingly
			if (app.menu == 2) strcpy(text, "MAIN MENU");	//If the menu is the pause menu, overwrite the text accordingly
			if (app.menu == 3) strcpy(text, "LEVEL 3");		//If the menu is the levels menu, overwrite the text accordingly
			break;

		default:
			break;
		}

		drawText(app.buttons[i]->x, app.buttons[i]->y - 10, 20, 20, 200, TEXT_CENTER, "%s", text);	//Draw text on the button
	}
}