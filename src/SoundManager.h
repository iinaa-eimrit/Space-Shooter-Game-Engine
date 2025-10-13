#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <iostream>

class SoundManager
{
private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
    sf::Music backgroundMusic;
    
    float volume;
    bool muted;
    
public:
    SoundManager();
    ~SoundManager();
    
    bool loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);
    void stopSound(const std::string& name);
    void setVolume(float volume);
    void toggleMute();
    bool isMuted() const;
    
    bool loadMusic(const std::string& filename);
    void playMusic();
    void stopMusic();
    void setMusicVolume(float volume);
};