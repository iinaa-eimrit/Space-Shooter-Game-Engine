#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Bullet.h"

class Enemy
{
protected:
    sf::RectangleShape shape;
    int hp;
    int hpMax;
    int damage;
    int points;
    float movementSpeed;
    float attackCooldown;
    float attackCooldownMax;
    std::vector<std::unique_ptr<Bullet>> bullets;
    
public:
    Enemy();
    virtual ~Enemy();
    
    virtual sf::FloatRect getBounds() const;
    const int& getPoints() const;
    const int& getDamage() const;
    std::vector<std::unique_ptr<Bullet>>& getBullets();
    
    virtual void update(const float& dt) = 0;
    virtual void updateAttack(const float& dt);
    virtual void updateBullets(const float& dt);
    virtual void render(sf::RenderTarget* target);
    
    virtual void takeDamage(int damage);
    virtual bool isDead() const;
    virtual void shoot();
};