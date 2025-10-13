#include "HighScoreManager.h"
#include <iostream>

HighScoreManager::HighScoreManager(const std::string& file) : filename(file)
{
    loadHighScores();
}

void HighScoreManager::loadHighScores()
{
    highScores.clear();
    
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "No high score file found. Creating new one." << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string name;
        int score, wave;
        
        if (std::getline(iss, name, ',') && (iss >> score))
        {
            iss.ignore();
            iss >> wave;
            highScores.emplace_back(name, score, wave);
        }
    }
    
    file.close();
    
    std::sort(highScores.begin(), highScores.end());
    
    if (highScores.size() > static_cast<size_t>(maxEntries))
    {
        highScores.resize(maxEntries);
    }
}

void HighScoreManager::saveHighScores()
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to save high scores!" << std::endl;
        return;
    }
    
    for (const auto& entry : highScores)
    {
        file << entry.playerName << "," << entry.score << "," << entry.wave << std::endl;
    }
    
    file.close();
}

void HighScoreManager::addHighScore(const std::string& playerName, int score, int wave)
{
    highScores.emplace_back(playerName, score, wave);
    std::sort(highScores.begin(), highScores.end());
    
    if (highScores.size() > static_cast<size_t>(maxEntries))
    {
        highScores.resize(maxEntries);
    }
    
    saveHighScores();
}

bool HighScoreManager::isHighScore(int score) const
{
    return highScores.size() < static_cast<size_t>(maxEntries) || score > highScores.back().score;
}

std::vector<HighScoreEntry> HighScoreManager::getHighScores() const
{
    return highScores;
}

void HighScoreManager::clearHighScores()
{
    highScores.clear();
    saveHighScores();
}