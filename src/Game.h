#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "EnemyTypes.h"
#include "BossEnemy.h"
#include "PowerUp.h"
#include "ParticleSystem.h"
#include "Background.h"
#include "SoundManager.h"
#include "Config.h"
#include "HighScoreManager.h"
#include "GameState.h"

class Game
{
private:
    // Window
    std::unique_ptr<sf::RenderWindow> window;
    sf::VideoMode videoMode;
    sf::Event ev;
    
    // Game objects - using smart pointers
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<PowerUp>> powerUps;
    
    // Systems
    ParticleSystem explosionParticles;
    ParticleSystem trailParticles;
    Background background;
    SoundManager soundManager;
    Config config;
    HighScoreManager highScoreManager;
    
    // Game logic
    int points;
    int currentWave;
    int enemiesPerWave;
    int maxEnemies;
    bool waveInProgress;
    float waveCooldown;
    float waveCooldownMax;
    
    // Game state
    GameState currentState;
    bool newHighScore;
    std::string playerName;
    int nameCharIndex;
    
    // Text
    sf::Font font;
    sf::Text uiText;
    sf::Text waveText;
    sf::Text menuText;
    sf::Text gameOverText;
    
    // Delta time for frame-independent movement
    sf::Clock clock;
    float deltaTime;
    
    // Screen shake
    sf::View originalView;
    float screenShakeTimer;
    float screenShakeIntensity;
    
    // Private functions
    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initSounds();
    void initPlayer();
    void initEnemies();
    void initGameStates();
    void initConfig();
    void initHighScores();
    
public:
    // Constructors / Destructors
    Game();
    virtual ~Game();
    
    // Accessors
    const bool isRunning() const;
    const bool getWaveInProgress() const;
    
    // Functions
    void pollEvents();
    void spawnEnemy();
    void spawnBoss();
    void spawnPowerUp(const sf::Vector2f& position);
    void startNewWave();
    void updateWave();
    void updateEnemies();
    void updateEnemyBullets();
    void updatePowerUps();
    void updateCombat();
    void updateText();
    void updateDeltaTime();
    void updateHighScoreInput();
    void update();
    
    // State functions
    void updateMainMenu();
    void updatePlaying();
    void updateGameOver();
    void updatePaused();
    
    void renderText(sf::RenderTarget* target);
    void renderEnemies();
    void renderPowerUps();
    void renderMainMenu();
    void renderPlaying();
    void renderGameOver();
    void renderPaused();
    void render();
    
    void resetGame();
    void triggerScreenShake(float intensity = 5.f, float duration = 0.2f);
};