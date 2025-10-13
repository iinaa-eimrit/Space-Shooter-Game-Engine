#pragma once
#include "Enemy.h"
#include <cmath>

class BossEnemy : public Enemy
{
private:
    int phase;
    float phaseTransitionTimer;
    std::vector<float> phaseHealthThresholds;
    
    float specialAttackCooldown;
    float specialAttackCooldownMax;
    
    float movementPatternTime;
    sf::Vector2f movementDirection;
    
    void initBossVariables();
    void changePhase();
    void executeSpecialAttack();
    void updateMovementPattern(const float& dt);
    
public:
    BossEnemy(float pos_x, float pos_y);
    
    void update(const float& dt) override;
    void updateAttack(const float& dt) override;
    void takeDamage(int damage) override;
};