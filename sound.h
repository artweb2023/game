#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

struct Sound
{
    sf::SoundBuffer gameMusicBuffer;
    sf::SoundBuffer shotSoundBuffer;
    sf::SoundBuffer hitSoundBuffer;
    sf::SoundBuffer playerDamageSoundBuffer;

    sf::Sound gameMusic;
    sf::Sound shotSound;
    sf::Sound hitSound;
    sf::Sound playerDamageSound;
};

void createSound(Sound &sound);
bool playGameMusic(Sound &sound);
bool playShotSound(Sound &sound);
bool playHitSound(Sound &sound);
bool playPlayerDamageSound(Sound &sound);
void stop(Sound &sound);
void allStop(Sound &sound);