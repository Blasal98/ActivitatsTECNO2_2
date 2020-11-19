#include <SDL_mixer.h> 
#include <map>

class Aud_Renderer {

private:
	std::map<std::string, Mix_Music*> themes;
public:
	Aud_Renderer() {
		//-->SDL_Mix
		const Uint8 audFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
		if (!(Mix_Init(audFlags) & audFlags)) throw "Error: SDL_mixer init";

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
			throw "No es pot inicialitzar SDL_Mixer";
	}
	~Aud_Renderer() {
		Mix_CloseAudio();
		Mix_Quit();
	}
	void resumeMusic() {
		Mix_ResumeMusic();
	}
	void pauseMusic() {
		Mix_PauseMusic();
	}
	void setVolume(int vol) {
		Mix_VolumeMusic(MIX_MAX_VOLUME);
	}
	void playTheme(std::string id, int repeat) {
		Mix_PlayMusic(themes[id], repeat);
	}
	void addTheme(std::string id, std::string path) {
		Mix_Music *soundTrack{ Mix_LoadMUS(path.c_str()) };
		if (soundTrack == nullptr) throw "Error: soundTrack load";

		themes.insert(std::pair<std::string, Mix_Music*>(id,soundTrack));
	}

};