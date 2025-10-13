#pragma once
#include "Enemy.h"

class BasicEnemy : public Enemy
{
public:
    BasicEnemy(float pos_x, float pos_y);
    void update(const float& dt) override;
};

class FastEnemy : public Enemy
{
private:
    float oscillation;
    float oscillationSpeed;
    
public:
    FastEnemy(float pos_x, float pos_y);
    void update(const float& dt) override;
};

class TankEnemy : public Enemy
{
public:
    TankEnemy(float pos_x, float pos_y);
    void update(const float& dt) override;
};

class ShooterEnemy : public Enemy
{
private:
    float shootCooldown;
    float shootCooldownMax;
    
public:
    ShooterEnemy(float pos_x, float pos_y);
    void update(const float& dt) override;
    void updateAttack(const float& dt) override;
};