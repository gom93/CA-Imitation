#pragma once

class AudioManager
{
	DECLARE_SINGLETON(AudioManager);

public:
	bool Init();

	void PlaySoundTrack(BGM bgm);
	void PlayEffectSound(EFFECT_SOUND sound);
};

