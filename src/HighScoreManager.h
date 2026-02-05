#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

struct HighScoreEntry
{
    std::string playerName;
    int score;
    int wave;
    
    HighScoreEntry()
        : playerName(""), score(0), wave(0) {}
    
    HighScoreEntry(const std::string& name, int score, int wave)
        : playerName(name), score(score), wave(wave) {}
    
    bool operator<(const HighScoreEntry& other) const
    {
        return score > other.score;
    }
};

class HighScoreManager
{
private:
    std::vector<HighScoreEntry> highScores;
    std::string filename;
    const int maxEntries = 10;
    
public:
    HighScoreManager(const std::string& file = "highscores.txt");
    
    void loadHighScores();
    void saveHighScores();
    void addHighScore(const std::string& playerName, int score, int wave);
    bool isHighScore(int score) const;
    std::vector<HighScoreEntry> getHighScores() const;
    void clearHighScores();
};