#include "Enemy.h"

Enemy::Enemy() : 
    hp(10), hpMax(10), damage(1), points(10), 
    movementSpeed(100.f), attackCooldown(0.f), attackCooldownMax(100.f)
{
    this->shape.setSize(sf::Vector2f(40.f, 40.f));
    this->shape.setFillColor(sf::Color::Magenta);
}

Enemy::~Enemy()
{
}

sf::FloatRect Enemy::getBounds() const
{
    return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
    return this->points;
}

const int& Enemy::getDamage() const
{
    return this->damage;
}

std::vector<std::unique_ptr<Bullet>>& Enemy::getBullets()
{
    return this->bullets;
}

void Enemy::updateAttack(const float& dt)
{
    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 60.f * dt;
    
    if (this->attackCooldown >= this->attackCooldownMax && rand() % 100 == 0)
    {
        this->shoot();
        this->attackCooldown = 0.f;
    }
}

void Enemy::updateBullets(const float& dt)
{
    for (auto it = this->bullets.begin(); it != this->bullets.end();)
    {
        (*it)->update(dt);
        
        if ((*it)->getBounds().top > 600.f) // Assuming screen height
        {
            it = this->bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Enemy::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    
    // Draw health bar if damaged
    if (this->hp < this->hpMax)
    {
        float healthPercentage = static_cast<float>(this->hp) / this->hpMax;
        
        sf::RectangleShape healthBarBackground(sf::Vector2f(this->shape.getGlobalBounds().width, 5.f));
        healthBarBackground.setFillColor(sf::Color::Red);
        healthBarBackground.setPosition(this->shape.getGlobalBounds().left, this->shape.getGlobalBounds().top - 10.f);
        
        sf::RectangleShape healthBar(sf::Vector2f(this->shape.getGlobalBounds().width * healthPercentage, 5.f));
        healthBar.setFillColor(sf::Color::Green);
        healthBar.setPosition(this->shape.getGlobalBounds().left, this->shape.getGlobalBounds().top - 10.f);
        
        target->draw(healthBarBackground);
        target->draw(healthBar);
    }
    
    for (auto& bullet : this->bullets)
    {
        bullet->render(target);
    }
}

void Enemy::takeDamage(int damage)
{
    this->hp -= damage;
    if (this->hp < 0)
        this->hp = 0;
}

bool Enemy::isDead() const
{
    return this->hp <= 0;
}

void Enemy::shoot()
{
    this->bullets.push_back(std::make_unique<Bullet>(
        this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + this->shape.getGlobalBounds().height,
        0.f, 1.f, 300.f
    ));
}