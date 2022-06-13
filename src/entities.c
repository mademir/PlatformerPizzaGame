#include "common.h"

static void move(Entity *e);
static void push(Entity *e, float dx, float dy);
static void moveToWorld(Entity *e, float dx, float dy);
static void moveToEntities(Entity *e, float dx, float dy);
static void loadEnts(const char *filename);
static void addEntFromLine(char *line);

void initEntities(void)
{
	switch (app.mapNo)
	{
	case 1:
		loadEnts("data/ents01.dat");
		break;
	case 2:
		loadEnts("data/ents02.dat");
		break;
	case 3:
		loadEnts("data/ents03.dat");
		break;
	default:
		break;
	}
}

void doEntities(void)
{
	Entity *e, *prev;

	prev = &stage.entityHead;

	for (e = stage.entityHead.next ; e != NULL ; e = e->next)
	{
		self = e;

		if (e->tick)
		{
			e->tick();
		}

		move(e);

		if (e->health <= 0)
		{
			if (e == stage.entityTail)
			{
				stage.entityTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}

	for (e = stage.entityHead.next ; e != NULL ; e = e->next)
	{
		if (e->riding != NULL)
		{
			e->x += e->riding->dx;

			push(e, e->riding->dx, 0);
		}

		e->x = MIN(MAX(e->x, 0), MAP_WIDTH * TILE_SIZE);
		e->y = MIN(MAX(e->y, 0), MAP_HEIGHT * TILE_SIZE);
	}
}

static void move(Entity *e)
{
	if (!(e->flags & EF_WEIGHTLESS))
	{
		e->dy += 1.5;
		e->dy = MAX(MIN(e->dy, 18), -999);
	}

	if (e->riding != NULL && e->riding->dy > 0)
	{
		e->dy = e->riding->dy + 1;
	}

	e->riding = NULL;

	e->isOnGround = 0;

	e->x += e->dx;
	push(e, e->dx, 0);

	e->y += e->dy;
	push(e, 0, e->dy);
}

static void push(Entity *e, float dx, float dy)
{
	moveToWorld(e, dx, dy);

	moveToEntities(e, dx, dy);
}

static void moveToWorld(Entity *e, float dx, float dy)
{
	int mx, my, hit, adj;

	if (dx != 0)
	{
		mx = dx > 0 ? (e->x + e->w) : e->x;
		mx /= TILE_SIZE;

		my = (e->y / TILE_SIZE);

		hit = 0;

		if (!isInsideMap(mx, my) || stage.map[mx][my] > 0)	//When the map tile is positive (on the foreground) (background tiles have negative values)
		{
			hit = 1;
		}

		my = (e->y + e->h - 1) / TILE_SIZE;

		if (!isInsideMap(mx, my) || stage.map[mx][my] > 0)	//When the map tile is positive (on the foreground) (background tiles have negative values)
		{
			hit = 1;
		}

		if (hit)
		{
			adj = dx > 0 ? -e->w : TILE_SIZE;

			e->x = (mx * TILE_SIZE) + adj;

			e->dx = 0;
		}
	}

	if (dy != 0)
	{
		my = dy > 0 ? (e->y + e->h) : e->y;
		my /= TILE_SIZE;

		mx = e->x / TILE_SIZE;

		hit = 0;

		if (!isInsideMap(mx, my) || stage.map[mx][my] > 0) 	//When the map tile is positive (on the foreground) (background tiles have negative values)
		{
			hit = 1;
		}

		mx = (e->x + e->w - 1) / TILE_SIZE;

		if (!isInsideMap(mx, my) || stage.map[mx][my] > 0) 	//When the map tile is positive (on the foreground) (background tiles have negative values)
		{
			hit = 1;
		}

		if (hit)
		{
			adj = dy > 0 ? -e->h : TILE_SIZE;

			e->y = (my * TILE_SIZE) + adj;

			e->dy = 0;

			e->isOnGround = dy > 0;
		}
	}
}

static void moveToEntities(Entity *e, float dx, float dy)
{
	Entity *other;
	int adj;

	for (other = stage.entityHead.next ; other != NULL ; other = other->next)
	{
		if (other != e && collision(e->x, e->y, e->w, e->h, other->x, other->y, other->w, other->h))
		{
			if (other->flags & EF_SOLID && !other->sx) //If the entity is solid and is not a platform.
			{
				if (dy != 0)
				{
					adj = dy > 0 ? -e->h : other->h;

					e->y = other->y + adj;

					e->dy = 0;

					if (dy > 0)
					{
						e->isOnGround = 1;

						e->riding = other;
					}
				}

				if (dx != 0)
				{
					adj = dx > 0 ? -e->w : other->w;

					e->x = other->x + adj;

					e->dx = 0;
				}
			}
			if (other->flags & EF_SOLID && e==player && collision(e->x, e->y+e->h, e->w, e->h, other->x, other->y, other->w, other->h) && dy > 0 && other->sx)	//If the entity is solid, e is the player, player's feet touches collides with the platform, player is falling on the platform, and the entity is a platform.
			{
				adj = dy > 0 ? -e->h : other->h;

				e->y = other->y + adj;

				e->dy = 0;

				if (dy > 0)
				{
					e->isOnGround = 1;

					e->riding = other;
				}

				if (dx != 0)
				{
					adj = dx > 0 ? -e->w : other->w;

					e->x = other->x + adj;

					e->dx = 0;
				}
			}
			else if (e->flags & EF_PUSH && other->riding==player)
			{
				if (e->dy>0) other->x += e->dx; //Changed it so it adds the speed of the entity to the other entity's x only if this entity is going down. (It already adds the speed if it is going up)

				other->y += e->dy;
			}
			if (e->touch && e->type != KUNAI) e->touch(other);	//Default touch call. If the entity has a touch function and is not a kunai, calls its touch function
		}

		if (collision(e->x + e->w - 1, e->y, 1, e->h, other->x + 15, other->y, other->w - 15, other->h) && (other == player || other->type == ENEMY) && e->touch && e->type == KUNAI) e->touch(other); //Custom collission condition for kunai touch calls. Call entitiy's touch function if it is colliding with other's centre, other is the player or an enemy and this is a kunai.
	}
}

void drawEntities(void)
{
	Entity *e;

	for (e = stage.entityHead.next ; e != NULL ; e = e->next)
	{
		blit(e->texture, e->x - stage.camera.x, e->y - stage.camera.y, 0);
	}
}

static void loadEnts(const char *filename)
{
	char line[MAX_LINE_LENGTH];
	char *data, *p;
	int n;

	data = readFile(filename);

	p = data;

	n = 0;

	memset(line, '\0', MAX_LINE_LENGTH);

	while (*p)
	{
		if (*p == '\n')
		{
			addEntFromLine(line);
			memset(line, '\0', MAX_LINE_LENGTH);
			n = 0;
		}
		else
		{
			line[n++] = *p;
		}

		p++;
	}

	free(data);
}

static void addEntFromLine(char *line)
{
	char name[MAX_NAME_LENGTH];

	sscanf(line, "%s", name);

	if (strcmp(name, "BLOCK") == 0)
	{
		initBlock(line);
	}
	else if (strcmp(name, "PLATFORM") == 0)
	{
		initPlatform(line);
	}
	else if (strcmp(name, "PIZZA") == 0)
	{
		initPizza(line);
	}
	else if (strcmp(name, "ENEMY") == 0)	//If enemy is read from the entities file
	{
		initEnemy(line);	//Initialise enemy from the line
	}
	else if (strcmp(name, "HEART") == 0)	//If enemy is read from the entities file
	{
		initHeart(line);	//Initialise heart from the line
	}
	else if (strcmp(name, "DOOR") == 0)	//If enemy is read from the entities file
	{
		initDoor(line);		//Initialise door from the line
	}
	else
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Unknown entity '%s'", line);
	}
}
