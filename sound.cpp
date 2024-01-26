#include "sound.h"

void createSound(Sound &sound)
{
    sound.gameMusicBuffer.loadFromFile("sound/game.wav");
    sound.shotSoundBuffer.loadFromFile("sound/plasma.wav");
    sound.hitSoundBuffer.loadFromFile("sound/mobv.wav");
    sound.playerDamageSoundBuffer.loadFromFile("sound/hit1.wav");
    sound.gameMusic.setBuffer(sound.gameMusicBuffer);
    sound.gameMusic.setVolume(50);
    sound.shotSound.setBuffer(sound.shotSoundBuffer);
    sound.hitSound.setBuffer(sound.hitSoundBuffer);
    sound.playerDamageSound.setBuffer(sound.playerDamageSoundBuffer);
}

bool playGameMusic(Sound &sound)
{
    if (sound.gameMusic.getStatus() != sf::Sound::Playing)
    {
        sound.gameMusic.play();
        return true;
    }
    return false;
}

bool playShotSound(Sound &sound)
{
    if (sound.shotSound.getStatus() != sf::Sound::Playing)
    {
        sound.shotSound.play();
        return true;
    }
    return false;
}

bool playHitSound(Sound &sound)
{
    if (sound.hitSound.getStatus() != sf::Sound::Playing)
    {
        sound.hitSound.play();
        return true;
    }
    return false;
}

bool playPlayerDamageSound(Sound &sound)
{
    if (sound.playerDamageSound.getStatus() != sf::Sound::Playing)
    {
        sound.playerDamageSound.play();
        return true;
    }
    return false;
}

void stop(Sound &sound)
{
    sound.gameMusic.stop();
    sound.shotSound.stop();
    sound.hitSound.stop();
    sound.playerDamageSound.stop();
}

void allStop(Sound &sound)
{
    sound.gameMusic.stop();
    sound.shotSound.stop();
    sound.hitSound.stop();
    sound.playerDamageSound.stop();
}
