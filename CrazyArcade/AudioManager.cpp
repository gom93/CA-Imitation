#include "pch.h"
#include "AudioManager.h"

bool AudioManager::Init()
{
	mciSendString(L"open Sound/InstallationBallon.wav alias InstallationBallon", 0, 0, 0);
	mciSendString(L"open Sound/MouseOverlap.wav alias MouseOverlap", 0, 0, 0);
	mciSendString(L"open Sound/ExplosionBallon.wav alias ExplosionBallon", 0, 0, 0);
	mciSendString(L"open Sound/PickupItem.mp3 alias PickupItem", 0, 0, 0);
	mciSendString(L"open Sound/ExplodeCharacter.mp3 alias ExplodeCharacter", 0, 0, 0);

	return true;
}

void AudioManager::PlaySoundTrack(BGM bgm)
{
	switch (bgm)
	{
	case BGM::Room:
		PlaySound(L"Sound/Crazy-Arcade-BGM-Room.wav", nullptr, SND_ASYNC | SND_LOOP);
		break;
	case BGM::Patrit:
		PlaySound(L"Sound/Crazy-Arcade-BGM-Patrit.wav", nullptr, SND_ASYNC | SND_LOOP);
		break;
	default:
		/* For debugging */
		break;
	}
}

void AudioManager::PlayEffectSound(EFFECT_SOUND sound)
{
	switch (sound)
	{
	case EFFECT_SOUND::Install:
		mciSendString(L"play InstallationBallon from 0", 0, 0, 0);
		break;
	case EFFECT_SOUND::OverlappedButton:
		mciSendString(L"play MouseOverlap from 0", 0, 0, 0);
		break;
	case EFFECT_SOUND::Explosion:
		mciSendString(L"play ExplosionBallon from 0", 0, 0, 0);
		break;
	case EFFECT_SOUND::PickupItem:
		mciSendString(L"play PickupItem from 0", 0, 0, 0);
		break;
	case EFFECT_SOUND::ExplodeCharacter:
		mciSendString(L"play ExplodeCharacter from 0", 0, 0, 0);
		break;
	}
}
