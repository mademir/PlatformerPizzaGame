#include "common.h"

static void loadTiles(void);
static void loadMap(const char *filename);
int isInsideMap(int x, int y);

static SDL_Texture *tiles[MAX_TILES];
static SDL_Texture *bgtiles[20];

void initTiles(void) { loadTiles(); }

void initMap(void)
{
	memset(&stage.map, 0, sizeof(int) * MAP_WIDTH * MAP_HEIGHT);

	

	switch (app.mapNo)	//By current level
	{
	case 1:	//Level 1
		loadMap("data/map01.dat");	//Load first map
		break;
	case 2:	//Level 2
		loadMap("data/map02.dat");	//Load second map
		break;
	case 3:	//Level 3
		loadMap("data/map03.dat");	//Load third map
		break;
	default:
		break;
	}
}

void drawMap(void)
{
	int x, y, n, x1, x2, y1, y2, mx, my;

	x1 = (stage.camera.x % TILE_SIZE) * -1;
	x2 = x1 + MAP_RENDER_WIDTH * TILE_SIZE + (x1 == 0 ? 0 : TILE_SIZE);

	y1 = (stage.camera.y % TILE_SIZE) * -1;
	y2 = y1 + MAP_RENDER_HEIGHT * TILE_SIZE + (y1 == 0 ? 0 : TILE_SIZE);

	mx = stage.camera.x / TILE_SIZE;
	my = stage.camera.y / TILE_SIZE;

	for (y = y1 ; y < y2 ; y += TILE_SIZE)
	{
		for (x = x1 ; x < x2 ; x += TILE_SIZE)
		{
			if (isInsideMap(mx, my))
			{
				n = stage.map[mx][my];

				if (n > 0)	//If the tile is on the foreground (positive tile index)
				{
					blit(tiles[n], x, y, 0);	//Display the tile from the foreground tiles array
				}

				if (n < 0)	//If the tile is on the background (negative tile index)
				{
					blit(bgtiles[-n], x, y, 0);	//Display the tile from the background tiles array with inverted index to make it positive
				}
			}

			mx++;
		}

		mx = stage.camera.x / TILE_SIZE;

		my++;
	}
}

static void loadTiles(void)
{
	int i;
	char filename[MAX_FILENAME_LENGTH];

	for (i = 1 ; i <= MAX_TILES ; i++)	//For loop for the foreground tiles
	{
		sprintf(filename, "assets/map/tiles/tile (%d).png", i);	//Set the file name according to index

		tiles[i] = loadTexture(filename);	//Load the tile and add it to foreground tiles array
	}

	for (i = 1; i <= 9; i++)			//For loop for the background tiles
	{
		sprintf(filename, "assets/map/tiles/bgtile (%d).png", i);	//Set the file name according to index

		bgtiles[i] = loadTexture(filename);	//Load the tile and add it to foreground tiles array
	}
	
}

static void loadMap(const char *filename)
{
	char *data, *p;
	int x, y;

	data = readFile(filename);

	p = data;
	
	for (y = 0 ; y < MAP_HEIGHT ; y++)
	{
		for (x = 0 ; x < MAP_WIDTH ; x++)
		{
			sscanf(p, "%d", &stage.map[x][y]);

			do {p++;} while (*p != ' ' && *p != '\n');
		}
	}
	free(data);
}

int isInsideMap(int x, int y)
{
	return x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT;
}
