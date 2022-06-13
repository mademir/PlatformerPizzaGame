#include "common.h"

static void loadSounds(void);

static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music;

void initSounds(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);

	music = NULL;

	loadSounds();
}

void loadMusic(char *filename)
{
	if (music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename);
}

void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}

static void loadSounds(void)
{
	sounds[SND_JUMP] = Mix_LoadWAV("sound/jump.ogg");				//Sound when player jumps
	if (sounds[SND_JUMP] == NULL) {
		printf("Couldn't load sound/jump.ogg\n");
	}
	else {
		printf("Loaded sound successfully\n");
	}
	sounds[SND_PIZZA] = Mix_LoadWAV("sound/pop.ogg");				//Sound when pizza collected
	sounds[SND_PIZZA_DONE] = Mix_LoadWAV("sound/win.ogg");			//Sound when all pizza collected
	sounds[SND_OPEN_DOOR] = Mix_LoadWAV("sound/openDoor.ogg");		//Sound when door is opening
	sounds[SND_CLOSE_DOOR] = Mix_LoadWAV("sound/closeDoor.ogg");	//Sound when door is closing
	sounds[SND_HEART] = Mix_LoadWAV("sound/heart.ogg");				//Sound when heart collected
	sounds[SND_KUNAI] = Mix_LoadWAV("sound/kunai.ogg");				//Sound when kunai is thrown
	sounds[SND_HIT] = Mix_LoadWAV("sound/ouch.ogg");				//Sound when kunai hits
	sounds[SND_KEY] = Mix_LoadWAV("sound/key.ogg");					//Sound when key collected
}
