#include "EnemyTypes.h"
#include <cmath>

// BasicEnemy
BasicEnemy::BasicEnemy(float pos_x, float pos_y)
{
    this->shape.setPosition(pos_x, pos_y);
    this->movementSpeed = 100.f;
    this->hpMax = 10;
    this->hp = this->hpMax;
    this->points = 10;
    this->damage = 1;
    
    this->shape.setSize(sf::Vector2f(40.f, 40.f));
    this->shape.setFillColor(sf::Color::Magenta);
}

void BasicEnemy::update(const float& dt)
{
    this->shape.move(0.f, this->movementSpeed * dt);
    this->updateAttack(dt);
    this->updateBullets(dt);
}

// FastEnemy
FastEnemy::FastEnemy(float pos_x, float pos_y) : oscillation(0.f), oscillationSpeed(3.f)
{
    this->shape.setPosition(pos_x, pos_y);
    this->movementSpeed = 200.f;
    this->hpMax = 5;
    this->hp = this->hpMax;
    this->points = 15;
    this->damage = 1;
    
    this->shape.setSize(sf::Vector2f(30.f, 30.f));
    this->shape.setFillColor(sf::Color::Cyan);
}

void FastEnemy::update(const float& dt)
{
    oscillation += oscillationSpeed * dt;
    float xMovement = std::sin(oscillation * 2.f) * 100.f * dt;
    this->shape.move(xMovement, this->movementSpeed * dt);
    this->updateAttack(dt);
    this->updateBullets(dt);
}

// TankEnemy
TankEnemy::TankEnemy(float pos_x, float pos_y)
{
    this->shape.setPosition(pos_x, pos_y);
    this->movementSpeed = 50.f;
    this->hpMax = 30;
    this->hp = this->hpMax;
    this->points = 50;
    this->damage = 3;
    
    this->shape.setSize(sf::Vector2f(60.f, 60.f));
    this->shape.setFillColor(sf::Color::Red);
}

void TankEnemy::update(const float& dt)
{
    this->shape.move(0.f, this->movementSpeed * dt);
    this->updateAttack(dt);
    this->updateBullets(dt);
}

// ShooterEnemy
ShooterEnemy::ShooterEnemy(float pos_x, float pos_y) : 
    shootCooldown(0.f), shootCooldownMax(60.f)
{
    this->shape.setPosition(pos_x, pos_y);
    this->movementSpeed = 75.f;
    this->hpMax = 15;
    this->hp = this->hpMax;
    this->points = 25;
    this->damage = 2;
    
    this->shape.setSize(sf::Vector2f(35.f, 35.f));
    this->shape.setFillColor(sf::Color::Green);
}

void ShooterEnemy::update(const float& dt)
{
    this->shape.move(0.f, this->movementSpeed * dt);
    this->updateAttack(dt);
    this->updateBullets(dt);
}

void ShooterEnemy::updateAttack(const float& dt)
{
    Enemy::updateAttack(dt);
    
    shootCooldown += 60.f * dt;
    if (shootCooldown >= shootCooldownMax)
    {
        this->shoot();
        shootCooldown = 0.f;
    }
}