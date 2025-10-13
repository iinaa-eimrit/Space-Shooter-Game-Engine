#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Bullet.h"

class Player
{
private:
    sf::RectangleShape shape;
    float movementSpeed;
    
    std::vector<std::unique_ptr<Bullet>> bullets;
    float attackCooldown;
    float attackCooldownMax;
    
    int hp;
    int hpMax;
    int lives;
    
    bool hasShield;
    float shieldTime;
    float shieldTimeMax;
    
    bool rapidFire;
    float rapidFireTime;
    float rapidFireTimeMax;
    
    bool justShot;
    
    void initVariables();
    void initShape();
    void initPowerUps();
    
public:
    Player(float x = 0.f, float y = 0.f);
    virtual ~Player();
    
    sf::FloatRect getBounds() const;
    std::vector<std::unique_ptr<Bullet>>& getBullets();
    const int& getHp() const;
    const int& getHpMax() const;
    const int& getLives() const;
    bool hasShieldActive() const;
    bool hasJustShot() const;
    
    void setPosition(float x, float y);
    void takeDamage(int damage);
    void loseLife();
    void addLife();
    void heal(int amount);
    
    void activateShield(float duration = 10.f);
    void activateRapidFire(float duration = 5.f);
    void updatePowerUps(const float& dt);
    
    void updateInput(const float& dt);
    void updateWindowBoundsCollision(const sf::RenderTarget* target);
    void updateBullets(const float& dt);
    void updateAttack(const float& dt);
    void update(const float& dt, const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
    
    void shoot();
};