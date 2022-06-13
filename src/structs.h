typedef struct Texture Texture;
typedef struct Entity Entity;
typedef struct Button Button;	//To store a button

typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

struct Texture {
	char name[MAX_NAME_LENGTH];
	SDL_Texture *texture;
	Texture *next;
};

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
	int mouseClick;		//To store the mouse click input
	int noKeyPos[2];	//To store the x y position to display the no key image
	int menu;			//To store the type of the current menu (main menu, pause menu, no menu)
	int mapNo;			//To store the current level number
	Button* buttons[MAX_BUTTONS];		//To store the menu buttons
	Texture textureHead, *textureTail;
} App;

struct Entity {
	float x;
	float y;
	int w;
	int h;
	float ex;
	float ey;
	float sx;
	float sy;
	float dx;
	float dy;
	int health;
	int isOnGround;
	int facing;
	int type;	//Type of entity
	int speed;	//Speed of entity
	int frame;	//Frame of entity with animations
	float value;
	int inSight;	//Flag to store if the target is in sight of the entity
	int temp;		//Temporary value to store various temporary values for entities
	Entity* target1;	//To store a potential target entity
	Entity* target2;	//To store another potential target entity
	SDL_Texture *texture;
	void (*tick)(void);
	void (*touch)(Entity *other);
	long flags;
	Entity *riding;
	Entity *next;
};

struct Button {	//To store a button
	float x;	//X position of the button
	float y;	//Y position of the button
	int w;		//Width of the button
	int h;		//Height of the button
	int hovered;//Flag to store if the button is hovered
	SDL_Texture *texture;	//To store the background texture of the button
};

typedef struct {
	SDL_Point camera;
	int map[MAP_WIDTH][MAP_HEIGHT];
	Entity entityHead, *entityTail;
	int pizzaTotal, pizzaFound;
} Stage;
