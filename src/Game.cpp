#include "Game.h"

// Private functions
void Game::initVariables()
{
    this->points = 0;
    this->currentWave = 0;
    this->enemiesPerWave = 5;
    this->maxEnemies = 10;
    this->waveInProgress = false;
    this->waveCooldownMax = 180.f;
    this->waveCooldown = this->waveCooldownMax;
    this->currentState = GameState::MAIN_MENU;
    this->newHighScore = false;
    this->playerName = "AAA";
    this->nameCharIndex = 0;
    this->deltaTime = 0.f;
    this->screenShakeTimer = 0.f;
    this->screenShakeIntensity = 0.f;
}

void Game::initConfig()
{
    if (!config.loadFromFile("config.ini"))
    {
        // Set default values
        config.set("window_width", 800);
        config.set("window_height", 600);
        config.set("window_title", "Space Shooter");
        config.set("max_fps", 60);
    }
}

void Game::initWindow()
{
    this->videoMode.width = config.get<int>("window_width", 800);
    this->videoMode.height = config.get<int>("window_height", 600);
    this->window = std::make_unique<sf::RenderWindow>(
        this->videoMode, 
        config.get<std::string>("window_title", "Space Shooter"), 
        sf::Style::Titlebar | sf::Style::Close
    );
    this->window->setFramerateLimit(config.get<int>("max_fps", 60));
    this->originalView = this->window->getDefaultView();
}

void Game::initFonts()
{
    if (!this->font.loadFromFile("assets/fonts/arial.ttf"))
    {
        std::cout << "WARNING::GAME::INITFONTS::Could not load font, using default!" << std::endl;
        // Create a fallback using system default
    }
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(18);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
    this->uiText.setPosition(10.f, 10.f);
    
    this->waveText.setFont(this->font);
    this->waveText.setCharacterSize(30);
    this->waveText.setFillColor(sf::Color::Yellow);
    
    this->menuText.setFont(this->font);
    this->menuText.setCharacterSize(36);
    this->menuText.setFillColor(sf::Color::Green);
    this->menuText.setString("SPACE SHOOTER\n\nPress ENTER to start\nPress ESC to quit");
    
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(28);
    this->gameOverText.setFillColor(sf::Color::Red);
}

void Game::initSounds()
{
    soundManager.loadSound("shoot", "assets/sounds/laser.wav");
    soundManager.loadSound("explosion", "assets/sounds/explosion.wav");
    soundManager.loadSound("player_hit", "assets/sounds/hit.wav");
    soundManager.loadSound("powerup", "assets/sounds/powerup.wav");
    soundManager.loadMusic("assets/sounds/background.wav");
    soundManager.setMusicVolume(50.0f);
    soundManager.playMusic();
}

void Game::initPlayer()
{
    this->player = std::make_unique<Player>();
    this->player->setPosition(
        this->window->getSize().x / 2.f - 25.f,
        this->window->getSize().y - 60.f
    );
}

void Game::initEnemies()
{
    // Enemies start empty, spawn with waves
}

void Game::initGameStates()
{
    this->currentState = GameState::MAIN_MENU;
}

void Game::initHighScores()
{
    this->newHighScore = false;
}

// Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initConfig();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initSounds();
    this->initPlayer();
    this->initEnemies();
    this->initGameStates();
    this->initHighScores();
}

Game::~Game()
{
    // Smart pointers automatically clean up!
}

// Accessors
const bool Game::isRunning() const
{
    return this->window->isOpen();
}

const bool Game::getWaveInProgress() const
{
    return this->waveInProgress;
}

// Functions
void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            switch (this->ev.key.code)
            {
            case sf::Keyboard::Escape:
                if (this->currentState == GameState::PLAYING)
                    this->currentState = GameState::MAIN_MENU;
                else
                    this->window->close();
                break;
            case sf::Keyboard::Enter:
                if (this->currentState == GameState::MAIN_MENU)
                {
                    this->currentState = GameState::PLAYING;
                    this->resetGame();
                }
                break;
            case sf::Keyboard::P:
                if (this->currentState == GameState::PLAYING)
                    this->currentState = GameState::PAUSED;
                else if (this->currentState == GameState::PAUSED)
                    this->currentState = GameState::PLAYING;
                break;
            case sf::Keyboard::R:
                if (this->currentState == GameState::GAME_OVER)
                {
                    this->currentState = GameState::PLAYING;
                    this->resetGame();
                }
                break;
            }
            break;
        }
    }
}

void Game::spawnEnemy()
{
    if (this->enemies.size() < static_cast<size_t>(this->maxEnemies))
    {
        std::unique_ptr<Enemy> newEnemy;
        int enemyType = rand() % 100;
        
        if (enemyType < 50) // 50% basic enemies
        {
            newEnemy = std::make_unique<BasicEnemy>(
                static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - 40.f)),
                -40.f
            );
        }
        else if (enemyType < 75) // 25% fast enemies
        {
            newEnemy = std::make_unique<FastEnemy>(
                static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - 30.f)),
                -30.f
            );
        }
        else if (enemyType < 90) // 15% tank enemies
        {
            newEnemy = std::make_unique<TankEnemy>(
                static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - 60.f)),
                -60.f
            );
        }
        else // 10% shooter enemies
        {
            newEnemy = std::make_unique<ShooterEnemy>(
                static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - 35.f)),
                -35.f
            );
        }
        
        this->enemies.push_back(std::move(newEnemy));
    }
}

void Game::spawnBoss()
{
    this->enemies.push_back(std::make_unique<BossEnemy>(
        this->window->getSize().x / 2.f - 60.f,
        -120.f
    ));
}

void Game::spawnPowerUp(const sf::Vector2f& position)
{
    PowerUpType type = static_cast<PowerUpType>(rand() % 4);
    this->powerUps.push_back(std::make_unique<PowerUp>(position.x, position.y, type));
}

void Game::startNewWave()
{
    this->currentWave++;
    
    // Boss every 5 waves
    if (this->currentWave % 5 == 0)
    {
        this->spawnBoss();
        this->waveInProgress = true;
        std::stringstream ss;
        ss << "BOSS BATTLE!";
        this->waveText.setString(ss.str());
    }
    else
    {
        this->enemiesPerWave = 5 + (this->currentWave * 2);
        
        for (int i = 0; i < this->enemiesPerWave; i++)
        {
            this->spawnEnemy();
        }
        
        this->waveInProgress = true;
        
        std::stringstream ss;
        ss << "WAVE " << this->currentWave;
        this->waveText.setString(ss.str());
    }
}

void Game::updateWave()
{
    if (!this->waveInProgress && this->waveCooldown <= 0.f)
    {
        this->startNewWave();
    }
    else if (!this->waveInProgress)
    {
        this->waveCooldown -= 60.f * this->deltaTime;
    }
    
    if (this->waveInProgress && this->enemies.empty())
    {
        this->waveInProgress = false;
        this->waveCooldown = this->waveCooldownMax;
    }
}

void Game::updateEnemies()
{
    for (auto it = this->enemies.begin(); it != this->enemies.end();)
    {
        (*it)->update(this->deltaTime);
        
        if ((*it)->getBounds().top > this->window->getSize().y)
        {
            it = this->enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::updateEnemyBullets()
{
    for (auto& enemy : this->enemies)
    {
        enemy->updateBullets(this->deltaTime);
    }
}

void Game::updatePowerUps()
{
    for (auto it = this->powerUps.begin(); it != this->powerUps.end();)
    {
        (*it)->update(this->deltaTime);
        
        if ((*it)->getBounds().intersects(this->player->getBounds()))
        {
            soundManager.playSound("powerup");
            
            switch ((*it)->getType())
            {
            case PowerUpType::RAPID_FIRE:
                this->player->activateRapidFire(10.f);
                break;
            case PowerUpType::SHIELD:
                this->player->activateShield(15.f);
                break;
            case PowerUpType::EXTRA_LIFE:
                this->player->addLife();
                break;
            case PowerUpType::SCORE_BOOST:
                this->points += 500;
                break;
            }
            
            it = this->powerUps.erase(it);
        }
        else if ((*it)->getBounds().top > this->window->getSize().y)
        {
            it = this->powerUps.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::updateCombat()
{
    // Player bullets vs enemies
    auto& playerBullets = this->player->getBullets();
    for (auto bulletIt = playerBullets.begin(); bulletIt != playerBullets.end();)
    {
        bool bulletHit = false;
        
        for (auto enemyIt = this->enemies.begin(); enemyIt != this->enemies.end();)
        {
            if ((*bulletIt)->getBounds().intersects((*enemyIt)->getBounds()))
            {
                (*enemyIt)->takeDamage(10);
                
                if ((*enemyIt)->isDead())
                {
                    this->points += (*enemyIt)->getPoints();
                    soundManager.playSound("explosion");
                    
                    explosionParticles.createExplosion(sf::Vector2f(
                        (*enemyIt)->getBounds().left + (*enemyIt)->getBounds().width / 2.f,
                        (*enemyIt)->getBounds().top + (*enemyIt)->getBounds().height / 2.f
                    ));
                    
                    if (rand() % 100 < 20)
                    {
                        spawnPowerUp(sf::Vector2f(
                            (*enemyIt)->getBounds().left,
                            (*enemyIt)->getBounds().top
                        ));
                    }
                    
                    enemyIt = this->enemies.erase(enemyIt);
                }
                else
                {
                    ++enemyIt;
                }
                
                bulletHit = true;
                break;
            }
            else
            {
                ++enemyIt;
            }
        }
        
        if (bulletHit)
        {
            bulletIt = playerBullets.erase(bulletIt);
        }
        else
        {
            ++bulletIt;
        }
    }
    
    // Enemy bullets vs player
    for (auto& enemy : this->enemies)
    {
        auto& enemyBullets = enemy->getBullets();
        for (auto it = enemyBullets.begin(); it != enemyBullets.end();)
        {
            if ((*it)->getBounds().intersects(this->player->getBounds()))
            {
                if (!this->player->hasShieldActive())
                {
                    this->player->takeDamage(enemy->getDamage());
                    soundManager.playSound("player_hit");
                    
                    if (this->player->getHp() <= 0)
                    {
                        this->player->loseLife();
                        if (this->player->getLives() <= 0)
                        {
                            this->currentState = GameState::GAME_OVER;
                        }
                        else
                        {
                            this->player->heal(100);
                            this->player->setPosition(
                                this->window->getSize().x / 2.f - 25.f,
                                this->window->getSize().y - 60.f
                            );
                        }
                    }
                }
                
                it = enemyBullets.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    
    // Enemy collision with player
    for (auto it = this->enemies.begin(); it != this->enemies.end();)
    {
        if ((*it)->getBounds().intersects(this->player->getBounds()))
        {
            if (!this->player->hasShieldActive())
            {
                this->player->takeDamage((*it)->getDamage());
                soundManager.playSound("player_hit");
            }
            
            it = this->enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::updateText()
{
    std::stringstream ss;
    ss << "Points: " << this->points << "\n"
       << "Wave: " << this->currentWave << "\n"
       << "Health: " << this->player->getHp() << "/" << this->player->getHpMax() << "\n"
       << "Lives: " << this->player->getLives();
    
    this->uiText.setString(ss.str());
}

void Game::updateDeltaTime()
{
    this->deltaTime = this->clock.restart().asSeconds();
}

void Game::updateHighScoreInput()
{
    // Handle name input for high scores
    // Implementation depends on specific input handling
}

void Game::updateMainMenu()
{
    // Menu doesn't need much updating
}

void Game::updatePlaying()
{
    background.update(this->deltaTime);
    
    this->player->update(this->deltaTime, this->window.get());
    
    if (this->player->hasJustShot())
    {
        soundManager.playSound("shoot");
    }
    
    this->updateWave();
    this->updateEnemies();
    this->updateEnemyBullets();
    this->updatePowerUps();
    this->updateCombat();
    this->updateText();
    
    explosionParticles.update(this->deltaTime);
    trailParticles.update(this->deltaTime);
    
    if (this->screenShakeTimer > 0.f)
    {
        this->screenShakeTimer -= this->deltaTime;
        float offsetX = (rand() % static_cast<int>(this->screenShakeIntensity * 2)) - this->screenShakeIntensity;
        float offsetY = (rand() % static_cast<int>(this->screenShakeIntensity * 2)) - this->screenShakeIntensity;
        
        sf::View shakenView = this->originalView;
        shakenView.move(offsetX, offsetY);
        this->window->setView(shakenView);
        
        if (this->screenShakeTimer <= 0.f)
        {
            this->window->setView(this->originalView);
        }
    }
}

void Game::updateGameOver()
{
    if (this->highScoreManager.isHighScore(this->points))
    {
        this->newHighScore = true;
        this->updateHighScoreInput();
    }
}

void Game::updatePaused()
{
    // Paused state
}

void Game::update()
{
    this->updateDeltaTime();
    this->pollEvents();
    
    switch (this->currentState)
    {
    case GameState::MAIN_MENU:
        this->updateMainMenu();
        break;
    case GameState::PLAYING:
        this->updatePlaying();
        break;
    case GameState::GAME_OVER:
        this->updateGameOver();
        break;
    case GameState::PAUSED:
        this->updatePaused();
        break;
    }
}

void Game::renderText(sf::RenderTarget* target)
{
    target->draw(this->uiText);
}

void Game::renderEnemies()
{
    for (auto& enemy : this->enemies)
    {
        enemy->render(this->window.get());
    }
}

void Game::renderPowerUps()
{
    for (auto& powerup : this->powerUps)
    {
        powerup->render(this->window.get());
    }
}

void Game::renderMainMenu()
{
    this->window->draw(this->menuText);
}

void Game::renderPlaying()
{
    this->player->render(this->window.get());
    this->renderEnemies();
    this->renderPowerUps();
    this->renderText(this->window.get());
    
    explosionParticles.render(*this->window);
    trailParticles.render(*this->window);
}

void Game::renderGameOver()
{
    this->window->draw(this->gameOverText);
}

void Game::renderPaused()
{
    this->renderPlaying();
    
    sf::Text pauseText;
    pauseText.setFont(this->font);
    pauseText.setCharacterSize(40);
    pauseText.setFillColor(sf::Color::Yellow);
    pauseText.setString("PAUSED\nPress P to continue");
    pauseText.setPosition(this->window->getSize().x / 2.f - 150.f, this->window->getSize().y / 2.f - 50.f);
    this->window->draw(pauseText);
}

void Game::render()
{
    this->window->clear(sf::Color::Black);
    
    background.render(*this->window);
    
    switch (this->currentState)
    {
    case GameState::MAIN_MENU:
        this->renderMainMenu();
        break;
    case GameState::PLAYING:
        this->renderPlaying();
        break;
    case GameState::GAME_OVER:
        this->renderGameOver();
        break;
    case GameState::PAUSED:
        this->renderPaused();
        break;
    }
    
    this->window->display();
}

void Game::resetGame()
{
    this->enemies.clear();
    this->powerUps.clear();
    
    this->points = 0;
    this->currentWave = 0;
    this->enemiesPerWave = 5;
    this->waveInProgress = false;
    this->waveCooldown = this->waveCooldownMax;
    
    this->player = std::make_unique<Player>();
    this->player->setPosition(
        this->window->getSize().x / 2.f - 25.f,
        this->window->getSize().y - 60.f
    );
    
    this->updateText();
}

void Game::triggerScreenShake(float intensity, float duration)
{
    this->screenShakeIntensity = intensity;
    this->screenShakeTimer = duration;
}