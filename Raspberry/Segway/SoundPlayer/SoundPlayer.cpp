#include "SoundPlayer.h"
#include <unistd.h>
#include <stdlib.h>

void SoundPlayer::Play(char* filename) {
	int pid;
	pid = fork();
	if (pid == 0)
	{
		//printf("I am the child\n");
		execlp("/usr/bin/omxplayer", " ", filename, NULL);		//Execute file: file, arguments (1 or more strings followed by NULL)
		_exit(0);
	}
	else
	{
		//printf("I am the parent\n");
		wait();
	}
}