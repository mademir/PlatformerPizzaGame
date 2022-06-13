#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'

#define PLATFORM_SPEED 4
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

#define MAX_TILES    15

#define TILE_SIZE    64

#define MAP_WIDTH    40
#define MAP_HEIGHT   20

#define MAP_RENDER_WIDTH    20
#define MAP_RENDER_HEIGHT   12

#define PLAYER_MOVE_SPEED 10

#define TOTAL_HP 10			//Total health of the player
#define TOTAL_STAMINA 1000	//Total stamina of the player (10x)

#define ENEMY_MOVE_SPEED 3	//Move speed of enemies
#define ENEMY_SIGHT 200		//Range of sight where enemies start to see the player

#define THROW_RANGE 220		//Range of kunai
#define KUNAI_SPEED 10		//Speed of kunai

#define MAX_LEVEL 3			//Maximum number of levels to play

#define MAX_NAME_LENGTH        32
#define MAX_LINE_LENGTH        1024
#define MAX_FILENAME_LENGTH    1024

#define MAX_KEYBOARD_KEYS 350

#define MAX_SND_CHANNELS 16

#define EF_NONE       0
#define EF_WEIGHTLESS (2 << 0)
#define EF_SOLID      (2 << 1)
#define EF_PUSH       (2 << 2)

#define GLYPH_WIDTH  18
#define GLYPH_HEIGHT 29

enum
{
	TEXT_LEFT,
	TEXT_CENTER,
	TEXT_RIGHT
};

enum
{
	SND_JUMP,
	SND_PIZZA,
	SND_PIZZA_DONE,
	SND_OPEN_DOOR,	//Door opening sound
	SND_CLOSE_DOOR,	//Door closing sound
	SND_HEART,		//Heart collecting sound
	SND_KEY,		//Key collecting sound
	SND_HIT,		//Getting hit by a kunai sound
	SND_KUNAI,		//Sound of kunai being thrown
	SND_MAX			//Maximum number of sounds
};

enum
{
	CH_PLAYER,
	CH_PIZZA
};

//Enum for directions
enum
{
	RIGHT,
	LEFT
};

//Enum for entity types
enum
{
	PLAYER,
	PIZZA,
	HEART,
	PLATFORM,
	BLOCK,
	KUNAI,
	ENEMY,
	DOOR,
	KEY
};

//Enum for buttons
enum
{
	PLAY_BTN,		//First button on the menu to play the game
	LEVELS_BTN,		//Second button on the menu to go to levels menu
	EXIT_BTN,		//Third exit button on the menu to exit the game
	MAX_BUTTONS,	//Represents the maximum number of buttons
};