#include "audioplayer.h"
#include "sndfile.h"
#include "portaudio.h"
#include "Poco/Thread.h"
#include "Poco/SingletonHolder.h"
#include "Poco/Event.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"

#include <queue>
using Poco::FastMutex;

static Poco::FastMutex gMutex;
static const int FRAME_PER_BUFFER = 64;
static const int MAX_PLAY_NUM = 16;

class AudioFile
{
public:
	AudioFile():
	  audio_file(NULL),
	  audio_buff(NULL),
	  num_frames_read(0)
	{
		
	}
	 ~AudioFile()
	 {
		 if (audio_buff != NULL)
		 {
			 delete audio_buff;
			 audio_buff = NULL;
		 }
	 }

	AudioFile& operator = (const AudioFile& file)
	{
		return *this;
	}

	SF_INFO  audio_info;
	SNDFILE* audio_file;
	char*	 audio_buff;
	sf_count_t num_frames_read;

	bool load(std::string &fileName)
	{
		audio_file = sf_open(fileName.c_str(), SFM_READ, &audio_info);
		if (audio_file == NULL)
		{
			printf("%s\n",sf_strerror(audio_file));
			return false;
		}

		audio_buff = (char*)malloc(audio_info.frames * audio_info.channels * sizeof(short)); // TODO: is this correct?
		
		num_frames_read = sf_readf_short(audio_file, (short*)audio_buff, audio_info.frames); // request all the frames

		sf_close(audio_file);
		audio_file = NULL;
		
		if(num_frames_read != audio_info.frames) return false;
		
		return true;
	}
};

class AudioPlayWorker{
public:
	AudioPlayWorker()
	{
		m_active = false;
		m_current= 0;
	}
	
	void playAudio(std::string &fileName)
	{
		AudioFile file;
		
		if(!file.load(fileName)) return;
		if(initDevice(file)) 	 return;
		
		run(file);
	}
	int run(AudioFile& file)
	{
		int frame = 0;
		m_current = 0;
		
		while( 1 )
		{
			//* - 此函数为同步函数，它一直等待到buffer中的数据全部写入声卡驱动才返回
			//* - 缓冲去长度为FRAMES_PER_BUFFER，指的是一个声道上的数据大小
			err = Pa_WriteStream( stream, (short*)file.audio_buff + m_current, FRAME_PER_BUFFER );

			m_current += (FRAME_PER_BUFFER * file.audio_info.channels) ;
			frame+=FRAME_PER_BUFFER;
			if(frame > file.audio_info.frames)
			{
				break;
			}
			if( err ) 
			{
				printf("Pa_WriteStream error\n");
				break;
			}

		}
		err = Pa_CloseStream(stream);
		err = Pa_Terminate();
		return err;
	}

private:

	int initDevice(AudioFile& file)
	{
#if 1
		err = Pa_Initialize();
		if( err != paNoError ) goto error;

		outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
		outputParameters.channelCount = file.audio_info.channels; //音频文件的通道数;
		outputParameters.sampleFormat = paInt16;	//音频文件采样的格式
		outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultHighOutputLatency;
		outputParameters.hostApiSpecificStreamInfo = NULL;

		/* Open an audio I/O stream. */
		err = Pa_OpenStream( &stream,
			0,          /* no input channels */
			&outputParameters,          /* stereo output */
			file.audio_info.samplerate,
			FRAME_PER_BUFFER,        /* frames per buffer */
			paClipOff,
			NULL,
			NULL );
		if( err != paNoError ) goto error;

		err = Pa_StartStream( stream );
		if( err != paNoError ) goto error;

		return 0;
error:
		Pa_Terminate();
		fprintf( stderr, "An error occured while using the portaudio stream\n" );
		fprintf( stderr, "Error number: %d\n", err );
		fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );

		return err;
#endif	
	}

private:
	PaStream *stream;
	PaError err;
	PaStreamParameters outputParameters;
	bool m_active;
	int  m_current;

};

class AudioDispatcher:public Poco::Runnable{
public:
	AudioDispatcher():
	  quit(false)
	{

	}
	bool start()
	{
		thread.start(*this);
		return evt_ready.tryWait(1000);
	}
	bool stop()
	{
		quit = true;
		evt_active.set();
		
		return evt_quit.tryWait(1000);
	}

	void run()
	{

		evt_ready.set();
		while (!quit)
		{

			num = get_count();

			if (num == 0)
			{

				evt_active.wait();
			}
			else
			{
				std::string playItem = popHead();
				worker.playAudio(playItem);
			}
			
		}

		evt_quit.set();
	}
	size_t get_count(void)
	{
		//这里不能加锁，否则会造成死锁
		return playlist.size();
	}
	void pushTail(std::string file)
	{

		FastMutex::ScopedLock lock(gMutex);

		if (playlist.size() > MAX_PLAY_NUM )
		{
			return;
		}
		playlist.push(file);
		evt_active.set();
		printf("play num=%d\n",get_count());

	}
	std::string popHead()
	{
		FastMutex::ScopedLock lock(gMutex);
		std::string item = playlist.front();
		playlist.pop();
		return item;
	}
private:
	size_t		    num;
	Poco::Event		evt_ready;
	Poco::Event		evt_active;
	Poco::Event		evt_quit;
	bool			quit;
	Poco::Thread	thread;
	AudioPlayWorker worker;
	std::queue<std::string> playlist;
};
static AudioDispatcher gAudioDisp;
AudioPlayer::AudioPlayer()
{
	gAudioDisp.start();
}
AudioPlayer& AudioPlayer::get()
{
	static Poco::SingletonHolder<AudioPlayer> sh;
	return *sh.get();
}
int AudioPlayer::PlayAudioFile(std::string audioFile)
{
	gAudioDisp.pushTail(audioFile);
	return 0;
}
AudioPlayer::~AudioPlayer()
{
	gAudioDisp.stop();
}
