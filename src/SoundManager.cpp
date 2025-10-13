#include "SoundManager.h"

SoundManager::SoundManager() : volume(100.0f), muted(false)
{
}

SoundManager::~SoundManager()
{
}

bool SoundManager::loadSound(const std::string& name, const std::string& filename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename))
    {
        std::cout << "Failed to load sound: " << filename << std::endl;
        return false;
    }
    
    soundBuffers[name] = buffer;
    sounds[name].setBuffer(soundBuffers[name]);
    
    return true;
}

void SoundManager::playSound(const std::string& name)
{
    if (!muted && sounds.find(name) != sounds.end())
    {
        sounds[name].play();
    }
}

void SoundManager::stopSound(const std::string& name)
{
    if (sounds.find(name) != sounds.end())
    {
        sounds[name].stop();
    }
}

void SoundManager::setVolume(float volume)
{
    this->volume = volume;
    for (auto& sound : sounds)
    {
        sound.second.setVolume(volume);
    }
}

void SoundManager::toggleMute()
{
    muted = !muted;
    if (muted)
    {
        for (auto& sound : sounds)
        {
            sound.second.setVolume(0);
        }
        backgroundMusic.setVolume(0);
    }
    else
    {
        for (auto& sound : sounds)
        {
            sound.second.setVolume(volume);
        }
        backgroundMusic.setVolume(volume);
    }
}

bool SoundManager::isMuted() const
{
    return muted;
}

bool SoundManager::loadMusic(const std::string& filename)
{
    if (!backgroundMusic.openFromFile(filename))
    {
        std::cout << "Failed to load music: " << filename << std::endl;
        return false;
    }
    backgroundMusic.setLoop(true);
    return true;
}

void SoundManager::playMusic()
{
    if (!muted)
    {
        backgroundMusic.play();
    }
}

void SoundManager::stopMusic()
{
    backgroundMusic.stop();
}

void SoundManager::setMusicVolume(float volume)
{
    if (!muted)
    {
        backgroundMusic.setVolume(volume);
    }
}