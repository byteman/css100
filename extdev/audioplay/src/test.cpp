#include <stdio.h>
#include "audioplayer.h"
#include "Poco/Thread.h"
int main(void)
{

	
	while (1)
	{
		AudioPlayer::get().PlayAudioFile("1.wav");
		AudioPlayer::get().PlayAudioFile("2.wav");
		Poco::Thread::sleep(5000);
	}

}
