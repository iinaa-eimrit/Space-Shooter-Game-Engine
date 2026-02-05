#include "Player.h"

void Player::initVariables()
{
    this->movementSpeed = 300.f; // pixels per second
    this->attackCooldownMax = 10.f;
    this->attackCooldown = this->attackCooldownMax;
    this->hpMax = 100;
    this->hp = this->hpMax;
    this->lives = 3;
    this->justShot = false;
}

void Player::initShape()
{
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

void Player::initPowerUps()
{
    hasShield = false;
    shieldTime = 0.f;
    shieldTimeMax = 0.f;
    
    rapidFire = false;
    rapidFireTime = 0.f;
    rapidFireTimeMax = 0.f;
}

Player::Player(float x, float y)
{
    this->shape.setPosition(x, y);
    this->initVariables();
    this->initShape();
    this->initPowerUps();
}

Player::~Player()
{
}

sf::FloatRect Player::getBounds() const
{
    return this->shape.getGlobalBounds();
}

std::vector<std::unique_ptr<Bullet>>& Player::getBullets()
{
    return this->bullets;
}

const int& Player::getHp() const
{
    return this->hp;
}

const int& Player::getHpMax() const
{
    return this->hpMax;
}

const int& Player::getLives() const
{
    return this->lives;
}

bool Player::hasShieldActive() const
{
    return hasShield;
}

bool Player::hasJustShot() const
{
    return justShot;
}

void Player::setPosition(float x, float y)
{
    this->shape.setPosition(x, y);
}

void Player::takeDamage(int damage)
{
    this->hp -= damage;
    if (this->hp < 0)
        this->hp = 0;
}

void Player::loseLife()
{
    this->lives--;
    if (this->lives < 0)
        this->lives = 0;
}

void Player::addLife()
{
    this->lives++;
}

void Player::heal(int amount)
{
    this->hp += amount;
    if (this->hp > this->hpMax)
        this->hp = this->hpMax;
}

void Player::activateShield(float duration)
{
    hasShield = true;
    shieldTime = 0.f;
    shieldTimeMax = duration;
    shape.setOutlineColor(sf::Color::Cyan);
    shape.setOutlineThickness(3.f);
}

void Player::activateRapidFire(float duration)
{
    rapidFire = true;
    rapidFireTime = 0.f;
    rapidFireTimeMax = duration;
    attackCooldownMax = 3.f;
}

void Player::updatePowerUps(const float& dt)
{
    if (hasShield)
    {
        shieldTime += dt;
        if (shieldTime >= shieldTimeMax)
        {
            hasShield = false;
            shape.setOutlineThickness(0.f);
        }
    }
    
    if (rapidFire)
    {
        rapidFireTime += dt;
        if (rapidFireTime >= rapidFireTimeMax)
        {
            rapidFire = false;
            attackCooldownMax = 10.f;
        }
    }
}

void Player::updateInput(const float& dt)
{
    justShot = false;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->shape.move(-this->movementSpeed * dt, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || 
             sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->shape.move(this->movementSpeed * dt, 0.f);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->shape.move(0.f, -this->movementSpeed * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || 
             sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->shape.move(0.f, this->movementSpeed * dt);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->attackCooldown >= this->attackCooldownMax)
    {
        this->shoot();
        this->attackCooldown = 0.f;
        justShot = true;
    }
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
    if (this->shape.getGlobalBounds().left <= 0.f)
        this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
    
    if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, 
                              this->shape.getGlobalBounds().top);
    
    if (this->shape.getGlobalBounds().top <= 0.f)
        this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
    
    if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
        this->shape.setPosition(this->shape.getGlobalBounds().left, 
                              target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::updateBullets(const float& dt)
{
    for (auto it = this->bullets.begin(); it != this->bullets.end();)
    {
        (*it)->update(dt);
        
        if ((*it)->getBounds().top + (*it)->getBounds().height < 0.f)
        {
            it = this->bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Player::updateAttack(const float& dt)
{
    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 60.f * dt;
}

void Player::update(const float& dt, const sf::RenderTarget* target)
{
    this->updateInput(dt);
    this->updateWindowBoundsCollision(target);
    this->updateBullets(dt);
    this->updateAttack(dt);
    this->updatePowerUps(dt);
}

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    
    for (auto& bullet : this->bullets)
    {
        bullet->render(target);
    }
}

void Player::shoot()
{
    this->bullets.push_back(std::make_unique<Bullet>(
        this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y,
        0.f, -1.f, 500.f
    ));
}