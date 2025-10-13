#include "BossEnemy.h"

BossEnemy::BossEnemy(float pos_x, float pos_y) : 
    phase(1), 
    phaseTransitionTimer(0.f),
    specialAttackCooldown(0.f),
    specialAttackCooldownMax(3.f),
    movementPatternTime(0.f)
{
    this->shape.setPosition(pos_x, pos_y);
    this->initBossVariables();
    
    this->shape.setSize(sf::Vector2f(120.f, 120.f));
    this->shape.setFillColor(sf::Color::Red);
    this->shape.setOutlineColor(sf::Color::Yellow);
    this->shape.setOutlineThickness(3.f);
}

void BossEnemy::initBossVariables()
{
    this->hpMax = 500;
    this->hp = this->hpMax;
    this->damage = 5;
    this->points = 1000;
    this->movementSpeed = 75.f;
    
    this->phaseHealthThresholds = { 0.66f, 0.33f };
    this->movementDirection = sf::Vector2f(1.f, 0.f);
}

void BossEnemy::update(const float& dt)
{
    this->updateMovementPattern(dt);
    this->updateAttack(dt);
    this->updateBullets(dt);
}

void BossEnemy::updateMovementPattern(const float& dt)
{
    movementPatternTime += dt;
    
    float time = movementPatternTime;
    float x = std::sin(time) * 100.f * dt;
    float y = std::sin(2.f * time) * 50.f * dt;
    
    this->shape.move(x + (movementDirection.x * movementSpeed * dt), 
                     this->movementSpeed * dt * 0.3f + y);
    
    sf::FloatRect bounds = this->shape.getGlobalBounds();
    if (bounds.left < 0)
    {
        this->shape.setPosition(0, bounds.top);
        movementDirection.x = 1.f;
    }
    else if (bounds.left + bounds.width > 800)
    {
        this->shape.setPosition(800 - bounds.width, bounds.top);
        movementDirection.x = -1.f;
    }
}

void BossEnemy::updateAttack(const float& dt)
{
    Enemy::updateAttack(dt);
    
    specialAttackCooldown += dt;
    if (specialAttackCooldown >= specialAttackCooldownMax)
    {
        this->executeSpecialAttack();
        specialAttackCooldown = 0.f;
    }
}

void BossEnemy::executeSpecialAttack()
{
    switch (phase)
    {
    case 1:
        // Spread shot
        for (int i = -2; i <= 2; ++i)
        {
            this->bullets.push_back(std::make_unique<Bullet>(
                this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f,
                this->shape.getPosition().y + this->shape.getGlobalBounds().height,
                i * 0.5f, 1.f, 400.f
            ));
        }
        break;
        
    case 2:
        // Spiral shot
        for (int i = 0; i < 8; ++i)
        {
            float angle = (i / 8.f) * 2.f * 3.14159f + movementPatternTime;
            this->bullets.push_back(std::make_unique<Bullet>(
                this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f,
                this->shape.getPosition().y + this->shape.getGlobalBounds().height,
                std::cos(angle), std::sin(angle), 300.f
            ));
        }
        break;
        
    case 3:
        // Rapid fire
        for (int i = 0; i < 5; ++i)
        {
            float spread = (i - 2) * 0.2f;
            this->bullets.push_back(std::make_unique<Bullet>(
                this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f,
                this->shape.getPosition().y + this->shape.getGlobalBounds().height,
                spread, 1.f, 500.f
            ));
        }
        break;
    }
}

void BossEnemy::takeDamage(int damage)
{
    this->hp -= damage;
    
    float healthPercentage = static_cast<float>(this->hp) / this->hpMax;
    for (size_t i = 0; i < phaseHealthThresholds.size(); ++i)
    {
        if (healthPercentage < phaseHealthThresholds[i] && phase == static_cast<int>(i + 1))
        {
            phase++;
            this->changePhase();
            break;
        }
    }
}

void BossEnemy::changePhase()
{
    switch (phase)
    {
    case 2:
        this->shape.setFillColor(sf::Color(255, 165, 0));
        this->movementSpeed *= 1.5f;
        this->specialAttackCooldownMax *= 0.7f;
        break;
        
    case 3:
        this->shape.setFillColor(sf::Color::Magenta);
        this->movementSpeed *= 1.2f;
        this->specialAttackCooldownMax *= 0.5f;
        break;
    }
}