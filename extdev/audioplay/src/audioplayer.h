#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <iostream>

class AudioPlayer
{
public:
	static AudioPlayer& get();
	int PlayAudioFile(std::string audioFile);
	AudioPlayer();
	~AudioPlayer();
};
#endif
